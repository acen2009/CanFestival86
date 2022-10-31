#include "canfestival.h"

// CAN_HANDLE can_hdl = NULL;

void initTimer(){
    TimerInit();
}

UNS8 canReceive(CAN_HANDLE hd, Message *m){
    return DLL_CALL(canReceive)(hd, m);
}


UNS8 canSend(CAN_HANDLE hd, Message *m){
    return DLL_CALL(canSend)(hd, m);
}

CAN_HANDLE canOpen(s_BOARD *board, CO_Data * d){
    d->canHandle = DLL_CALL(canOpen)(board);
    return d->canHandle;
}

int canClose(CAN_HANDLE hd, CO_Data * d){
    if(hd)
        DLL_CALL(canClose)(hd);
    return 0;
}

UNS8 canChangeBaudRate(CAN_HANDLE hd, char* baud){
// UNS8 DLL_CALL(canChangeBaudRate)(CAN_HANDLE, char *)FCT_PTR_INIT;    
}






