#ifndef __MCM_TIMER__
#define __MCM_TIMER__

#ifdef __cplusplus
extern "C"{
#endif

void initMCMTimer();
void attachTimerCb(void(*cb)(void));
void startTimer(unsigned long interval_us);
void releaseMCMTimer();

#ifdef __cplusplus
}
#endif

#endif