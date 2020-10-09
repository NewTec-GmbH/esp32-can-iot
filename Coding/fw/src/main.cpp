#include <Arduino.h>
#include <Lawicel.h>
#include <SerialAdapter.h>
#include <CANAdapter.h>
#include <NVMAdapter.h>

SerialAdapter serialAdapter;
CANAdapter sja1000Adapter;
NVMAdapter flashAdapter;
Lawicel protocolLawicel(&serialAdapter, &sja1000Adapter, &flashAdapter);
char help[100];

void setup()
{
  protocolLawicel.begin();
}

void loop()
{
  if(!protocolLawicel.handler()){
    strcpy(help,"Error");
    serialAdapter.send(help);
  }
}