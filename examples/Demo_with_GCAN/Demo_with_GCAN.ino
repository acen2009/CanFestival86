#include <CanFestival86.h>

extern "C"{
#include "MyMaster.h"
}

#define NODEID 0x01
#define BAUDRATE 1000000UL

unsigned long oldtime = 0;
static bool led_state = false;

class CanFestival86 node;

void slaveBootupCallback(CO_Data*, UNS8 SlaveID){
  Serial.println("slave boot up!");    
}

void slaveStateChangeCallback(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState){
  String s = "state of slave ";
  s+=nodeId;
  s+=" is change!";
  Serial.println(s);
  
  if(nodeId == 2){
    // set heartbeat period of slave node id 2 to produce heartbeat once per second.
    UNS16 data = 3000;
    node.sdoWriteAsync(2, 0x1017, 0x00, 2, &data);
  }
}

void LEDLight (CO_Data * d, UNS32 id){  
  OUTPUT_TO_GCAN++;
}

/* stepper */
#include "Motion86.h"
Machine machine(0);

int target = 0;
int current = 0;

void motorRun(){
  io_DisableINT();
  UNS8 tmp = INPUT_FROM_GCAN;    
  io_RestoreINT();
  target = tmp;

  int delta = 0;
  int diff = target - current;
  if(diff == 0) return;

  delta = (abs(diff)>8)? ((diff>0)? diff-16 : diff+16):diff;
  machine.line(delta, 0, 0);
  current = (current + delta)%16;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Open serial monitor to start!
  Serial.println("Hello CanFestival!");

  machine.config_PPU(AXIS_X, 100.0);
  machine.machineOn();
  machine.setDefaultFeedrate(3000);
  machine.setRelative();
  
  if(!node.begin(&MyMaster_Data, BAUDRATE)){
    Serial.println("Node Begin Failed, please reboot!");
    while(1);
  }
  MyMaster_Data.post_SlaveBootup = &slaveBootupCallback;
  MyMaster_Data.preOperational = &_preOperational;
  MyMaster_Data.post_SlaveStateChange = &slaveStateChangeCallback;
  node.set86NodeId(NODEID);
  node.set86State(Initialisation);
  node.setVerbose(false);
  SetAlarm (&MyMaster_Data, 0, &LEDLight, 200000, 200000); // in every 200ms
  node.set86State(Operational);
  Serial.println("Master Node Begin!");
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
    case 'r':
      Serial.println("Reset all node");
      masterSendNMTstateChange (&MyMaster_Data, 0, NMT_Reset_Node);
      break;
    case 'R':
      Serial.println("Reset all communication");
      masterSendNMTstateChange (&MyMaster_Data, 0, NMT_Reset_Comunication);
      break;
    default:
      break;
    }
  }

  node.dumpRuntimeInfo();  
  
  motorRun();

  unsigned long nowtime = millis();
  if((nowtime-oldtime > 1000)){
    oldtime = nowtime;
    led_state = !led_state;
    digitalWrite(LED_BUILTIN, led_state);
  }
}