#ifndef CANFESTIVAL86_H
#define CANFESTIVAL86_H

#include <Arduino.h>
#include "canfestival.h"

void sdoWriteDefaultCallback(CO_Data *d, uint8_t nodeId);

class CanFestival86 {

public:
    bool begin(CO_Data *node_data, unsigned long baudrate);
    bool set86NodeId(UNS8 nodeid);
    bool set86State(e_nodeState state);

    void setVerbose(bool is_verbose);
    void dumpRuntimeInfo(); // need to setVerbose to true
    bool sdoWrite(UNS8 nodeId, UNS16 index, UNS8 subIndex, UNS32 size, void *data, UNS32 timeout_ms = 1000);    
    bool sdoWriteAsync(UNS8 nodeId, UNS16 index, UNS8 subIndex, UNS32 size, void *data, SDOCallback_t Callback = &sdoWriteDefaultCallback);     
    bool sdoRead(UNS8 nodeId, UNS16 index, UNS8 subIndex, UNS32 *size, void *data, UNS32 timeout_ms = 1000);
    bool sdoReadAsync(UNS8 nodeId, UNS16 index, UNS8 subIndex, SDOCallback_t Callback);        
private:
    CO_Data *_CO_Data = NULL;    
    bool _verbosity = false;    
};



#endif
