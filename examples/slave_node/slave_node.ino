#include <CanFestival86.h>

extern "C"{
#include "MySlave.h"
}

#define NODEID 0x02
#define BAUDRATE 1000000UL

class CanFestival86 node;

void setup() {  
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Open serial monitor to start!
  Serial.println("Hello CanFestival!");

  if(!node.begin(&MySlave_Data, BAUDRATE)){
    Serial.println("Node Begin Failed, please reboot!");
    while(1);
  }
  node.set86NodeId(NODEID);
  node.set86State(Initialisation);
  node.setVerbose(true);
  Serial.println("Slave Node Begin!");
}

void loop() {  
  node.dumpRuntimeInfo();
  app_counter++;
}