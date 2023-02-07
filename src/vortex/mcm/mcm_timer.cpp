#include "stdio.h"
#include "stdlib.h"
// #include "io.h"
#include "io.h"

#include "vortex/mcm/mcm_timer.h"

#include "mcm.h"
#include "err.h"

#if defined (__86DUINO_EX) || defined (__DMP_EX_EVB)
#define TIMER_MC 3
#define TIMER_MD 2
#elif defined (__86DUINO_EX2) || defined (__DMP_EX2_EVB)
#define TIMER_MC 11
#define TIMER_MD 2
#else
#error device not recognized, please define the system you're using
#endif

#define MICRO_TO_10NANO 100L

/* reasonable minimum timeout interval */
#define MIN_INTV_10NS 100L //1us
/* transform unit from 1us to 10ns, and prevent it from a too small value */
#define TRANSFORM(val) (val*MICRO_TO_10NANO < MIN_INTV_10NS)? (MIN_INTV_10NS) : (val*MICRO_TO_10NANO)

#ifdef __cplusplus
extern "C"{
#endif
    #include "irq.h"
#ifdef __cplusplus
}
#endif

static int mcint_offset[3] = {0, 8, 16};
static void clear_INTSTATUS(int mc, int md, unsigned long used_int) {
    mc_outp(mc, 0x04, used_int << mcint_offset[md]);
}

static void disable_MCINT(int mc, int md, unsigned long used_int) {
    mc_outp(mc, 0x00, mc_inp(mc, 0x00) & ~(used_int << mcint_offset[md]));  // disable mc interrupt
    mc_outp(MC_GENERAL, 0x38, mc_inp(MC_GENERAL, 0x38, mc/4) | (1L << (mc%4)), mc/4);
}

static void enable_MCINT(int mc, int md, unsigned long used_int) {
	mc_outp(MC_GENERAL, 0x38, mc_inp(MC_GENERAL, 0x38, mc/4) & ~(1L << (mc%4)), mc/4);
	mc_outp(mc, 0x00, mc_inp(mc, 0x00) | (used_int << mcint_offset[md]));
}

static void pwmInit(int mcn, int mdn) {
	mcpwm_ReloadPWM(mcn, mdn, MCPWM_RELOAD_CANCEL);

	mcpwm_SetOutMask(mcn, mdn, MCPWM_HMASK_NONE + MCPWM_LMASK_NONE);
	mcpwm_SetOutPolarity(mcn, mdn, MCPWM_HPOL_NORMAL + MCPWM_LPOL_NORMAL);
	mcpwm_SetDeadband(mcn, mdn, 0L);
	mcpwm_ReloadOUT_Unsafe(mcn, mdn, MCPWM_RELOAD_NOW);
	
	mcpwm_SetWaveform(mcn, mdn, MCPWM_EDGE_A0I1);    

	mcpwm_SetSamplCycle(mcn, mdn, MIN_INTV_10NS-1L);
    /* set period width to 0 means only 1 clock per period which is 10ns long */
    mcpwm_SetWidth(TIMER_MC, TIMER_MD, 1-1L, 0L);
}

static bool isTimerEnable(){
    //is pwm module enable
    return mc_ReadEnableREG1(TIMER_MC) & (1 << (TIMER_MC%4 * 3 + TIMER_MD));
}

static unsigned long MCPWM_modOffset[3] = {0x08L, 0x08L + 0x2cL, 0x08L + 2L*0x2cL};
// MC PWM Registers
#define MCPWM_PERREG        (0x00L)
#define MCPWM_P0REG         (0x04L)
#define MCPWM_CTRLREG       (0x08L)
#define MCPWM_STATREG1      (0x0cL)
#define MCPWM_STATREG2      (0x10L)
#define MCPWM_EVTREG1       (0x14L)
#define MCPWM_EVTREG2       (0x18L)
#define MCPWM_OUTCTRLREG    (0x1cL)
#define MCPWM_FOUTREG       (0x24L)
#define MCPWM_LDREG         (0x28L)


void (*timer_callback)() = NULL;

unsigned long tm_cnt = 0;
unsigned long tm_cnt2 = 0;
static int timer_isr_handler(int irq, void* data) {
    tm_cnt ++;
    
    /* if sc-end INT has not happened */
    if ((mc_inp(TIMER_MC, 0x04) & (SC_END_INT << mcint_offset[TIMER_MD])) == 0) 
        return ISR_NONE;
    /* write 1 to clear sc-end INT status */
    tm_cnt2 ++;
    mc_outp(TIMER_MC, 0x04, (SC_END_INT << mcint_offset[TIMER_MD]));
    
    // io_DisableINT(); //no need
    if(timer_callback)
        (*timer_callback)();
    // io_RestoreINT();
    return ISR_HANDLED;
}

void initMCMTimer(){

    set_MMIO();
    if(mcmInit() != 0){
        err_print("mcmInit error\n");
    }

    mc_SetMode(TIMER_MC, MCMODE_PWM);
    int mcm_irq = GetMCIRQ(TIMER_MC/4);
    printf("PIC trigger mode is: %d\n", io_inpb(0x4D1));
    if(mcm_irq <= 7){
        // io_outpb(0x4D0, io_inpb(0x4D0) | 0x01 << mcm_irq);
    }
    else{
        // io_outpb(0x4D1, io_inpb(0x4D1) | 0x01 << (mcm_irq & 0x07) );
    }
    if(irq_Setting(mcm_irq, IRQ_LEVEL_TRIGGER + IRQ_DISABLE_INTR) == false){
        printf("MCM IRQ Setting fail\n");
        return;
    }
    else{
        printf("MCM IRQ No: %d\n", mcm_irq);
    }
    Set_MCIRQ(mcm_irq, TIMER_MC/4);

    mcpwm_Disable(TIMER_MC, TIMER_MD);

    pwmInit(TIMER_MC, TIMER_MD);

    disable_MCINT(TIMER_MC, TIMER_MD, SC_END_INT);
	clear_INTSTATUS(TIMER_MC, TIMER_MD, SC_END_INT);
    irq_InstallISR(GetMCIRQ(TIMER_MC/4), timer_isr_handler, NULL);
    enable_MCINT(TIMER_MC, TIMER_MD, SC_END_INT);

    /* let sc reset along with pwm reload simultaneously */
    mcpwm_SetSCRESET(TIMER_MC, TIMER_MD);

}

void attachTimerCb(void(*cb)(void)){
    timer_callback = cb;
}


void startTimer(unsigned long interval_us){
    
    io_DisableINT();
    //one shot timer : set sc_last to disable pwm module at the last period of sc
    mcpwm_SetSCLAST(TIMER_MC, TIMER_MD);
    
/*Debug only, can be removed
    // unsigned long t = timer_NowTime();
    // while(1){ //try to make a delay
    //     if(timer_NowTime() - t > 1000) break;
    // }
    // printf("val: %lu, after transform: %lu\n", interval_us, TRANSFORM(interval_us)-1L);
    // timer_Delay(1000);
*/
    unsigned long sc_reg;    
    unsigned long max_us = 0x51EB85; // the number approximate to (((2^29 - 1) + 1) / 100) in binary.

    if(interval_us == 0)
        sc_reg = 0; // trigger right away: will timeout after 1 mcm clock time, which is 10ns.
    else{
        if(interval_us > max_us) 
            sc_reg = 0x1FFFFFFF; // set to maximum available value of sc_reg : 2^29 - 1
        else 
            sc_reg = interval_us * 100 - 1; // less than 2^29 - 1
    }

    mcpwm_SetSamplCycle(TIMER_MC, TIMER_MD, sc_reg);
    // mcpwm_SetSamplCycle(TIMER_MC, TIMER_MD, TRANSFORM(interval_us)-1L);
    
    if(!isTimerEnable()){
        mcpwm_Enable(TIMER_MC, TIMER_MD);
    }
    else{
        mcpwm_ReloadPWM(TIMER_MC, TIMER_MD, MCPWM_RELOAD_NOW);
    }
    io_RestoreINT();
}

void releaseMCMTimer(){
    disable_MCINT(TIMER_MC, TIMER_MD, SC_END_INT);
    irq_UninstallISR(GetMCIRQ(TIMER_MC/4), NULL);
    mcpwm_Disable(TIMER_MC, TIMER_MD);    
}

