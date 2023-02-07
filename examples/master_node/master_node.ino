#include <CanFestival86.h>

extern "C"{
#include "MyMaster.h"
}

#define NODEID 0x01
#define BAUDRATE 1000000UL

UNS32 val = 0;
unsigned long oldtime = 0;

class CanFestival86 node;

void slaveBootupCallback(CO_Data*, UNS8){
  Serial.println("slave boot up!");  
  // set heartbeat period of slave node id 2 to produce heartbeat once per second.
  UNS16 data = 1000;
  node.sdoWriteAsync(2, 0x1017, 0x00, 2, &data);
}

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Open serial monitor to start!
  Serial.println("Hello CanFestival!");

  if(!node.begin(&MyMaster_Data, BAUDRATE)){
    Serial.println("Node Begin Failed, please reboot!");
    while(1);
  }
  node.set86NodeId(NODEID);
  node.set86State(Initialisation);
  node.setVerbose(true);
  Serial.println("Master Node Begin!");

  MyMaster_Data.post_SlaveBootup = &slaveBootupCallback;
}

void loop() {  
  if(Serial.available() > 0 ){
    int ch = Serial.read();
    switch (ch)
    {
    case 'i':
      Serial.println("Switch to Initialization State");
      node.set86State(Initialisation);
    break;

    case 'p':
      Serial.println("Switch to Pre-Operational State");
      node.set86State(Pre_operational);
    break;

    case 'o':
      Serial.println("Switch to Operational State");
      node.set86State(Operational);
      break;

    case 's':
      Serial.println("Switch to Stop State");
      node.set86State(Stopped);
      break;

    default:
      break;
    }    
  }
  node.dumpRuntimeInfo();
  io_DisableINT();
  UNS32 tmp = counter_from_slave;
  io_RestoreINT();
  unsigned long nowtime = millis();
  if(val!=tmp && (nowtime-oldtime > 1000)){
    val = tmp;
    oldtime = nowtime;
    Serial.print("get counter from slave through PDO channel:");
    Serial.println(val);  
  }  
}
