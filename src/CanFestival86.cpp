#include <CanFestival86.h>

#include <Arduino.h>

#include "io.h"
#include "irq.h"
#include "err.h"
#include "vortex/mcm/mcm_timer.h"
#include "mcm.h"

s_BOARD can_board;
CAN_HANDLE can_handle = NULL;

void initcb(CO_Data* d, UNS32 id){
    
}

void canReceiveAlarm (CO_Data * d, UNS32 id){
    Message msg;
    if(canReceive(d->canHandle, &msg)){
        canDispatch(d, &msg);        
    }
}

bool CanFestival86::begin(CO_Data *node_data, unsigned long baudrate){
        
    #if defined (__86DUINO_ONE) || defined (__DMP_EX_EVB) || defined (__DMP_EX2_EVB)
    #else
    #error can not run CanFestival86 on this device!
    #endif

    io_Init();

    set_MMIO();
    if(mcmInit() != 0){
        Serial.println("mcmInit error");
        return false;
    }
    
    if(irq_Init() == false){
        Serial.println("MCM IRQ init failed");
        return false;
    }

    if(err_Init(NULL) == false){
        Serial.println("err_init failed!");
    }
    
    initTimer();

    if(node_data == NULL){
        Serial.println("invalid node data");
        return false;
    }
    _CO_Data = node_data;
    
    can_board.busname = 0;
    can_board.baudrate = baudrate;

    can_handle = canOpen(&can_board, _CO_Data);
    
    if(!can_handle){
        Serial.println("can port init failed!");
        return false;
    }

    StartTimerLoop(&initcb);  
    SetAlarm (_CO_Data, 0, &canReceiveAlarm, 1000, 1000); // in every 1000us  

    return true;
}

bool CanFestival86::set86NodeId(UNS8 nodeid){
    if(_CO_Data == NULL){
        Serial.println("CanFestival is not ready, please call begin() to start!");
        return false;
    }
    setNodeId(_CO_Data, nodeid);
    return true;
}

bool CanFestival86::set86State(e_nodeState state){    
    if(_CO_Data == NULL){
        Serial.println("CanFestival is not ready, please call begin() to start!");
        return false;
    }
    if(setState(_CO_Data, state) == 0xFF){
        Serial.println("request rejected!");
        return false;
    }
    return true;
}

void CanFestival86::setVerbose(bool is_verbose){
    _verbosity = is_verbose;
}

void CanFestival86::dumpRuntimeInfo(){
    if(!_verbosity){
        return;
    }

    bool has_next_msg = false;
    char buf[256] = "";
    do{
        has_next_msg = err_Dump2Buf(buf);
        Serial.print(buf);
    }while(has_next_msg);        
}
bool CanFestival86::sdoWrite(UNS8 nodeId, UNS16 index, UNS8 subIndex, UNS32 size, void *data, UNS32 timeout_ms){
    if(_CO_Data == NULL){
        return false;
    }
    if(writeNetworkDict(_CO_Data, nodeId, index, subIndex, size, 0, data, 0) != 0){
        Serial.println("Something wrong while sending a SDO write request");
        return false;
    }

    UNS32 abortCode;
    unsigned long starttime = millis();
    while(getWriteResultNetworkDict(_CO_Data, nodeId, &abortCode) != SDO_FINISHED){
        if((millis()-starttime > timeout_ms)){
            Serial.println("SDO Write Timeout!");
            closeSDOtransfer(_CO_Data, nodeId, SDO_CLIENT);
            return false;
        }
    }
    return true;
}

bool CanFestival86::sdoWriteAsync(UNS8 nodeId, UNS16 index, UNS8 subIndex, UNS32 size, void *data, SDOCallback_t Callback){
    if(_CO_Data == NULL){
        return false;
    }
    if(writeNetworkDictCallBack(_CO_Data, nodeId, index, subIndex, size, 0, data, Callback, 0) != 0){
        Serial.println("Something wrong while sending a SDO write request");
        return false;
    }
    return true;
}

bool CanFestival86::sdoRead(UNS8 nodeId, UNS16 index, UNS8 subIndex, UNS32 *size, void *data, UNS32 timeout_ms){
    if(_CO_Data == NULL){
        return false;
    }    
    if(readNetworkDict(_CO_Data, nodeId, index, subIndex, 0, 0) != 0){
        Serial.println("Something wrong while sending a SDO read request");        
        return false;
    }

    UNS32 abortCode;
    unsigned long starttime = millis();    
    while(getReadResultNetworkDict(_CO_Data, nodeId, data, size, &abortCode) != SDO_FINISHED){        
        if((millis()-starttime > timeout_ms)){
            Serial.println("SDO Read Timeout!");
            closeSDOtransfer(_CO_Data, nodeId, SDO_CLIENT);
            return false;
        }
    }
    return true;
}

bool CanFestival86::sdoReadAsync(UNS8 nodeId, UNS16 index, UNS8 subIndex, SDOCallback_t Callback){
    if(_CO_Data == NULL){
        return false;
    }
    if(readNetworkDictCallback(_CO_Data, nodeId, index, subIndex, 0, Callback, 0) != 0){
        Serial.println("Something wrong while sending a SDO read request");
        return false;
    }
    return true;
}

void sdoWriteDefaultCallback(CO_Data *d, uint8_t nodeId){
    UNS32 abortCode;
    if(getWriteResultNetworkDict (d, nodeId, &abortCode) != SDO_FINISHED){        
        err_print("SDO Write Failed\n");
    }
    else{        
        err_print("SDO Write Succeeded\n");
    }
    closeSDOtransfer(d, nodeId, SDO_CLIENT);
}