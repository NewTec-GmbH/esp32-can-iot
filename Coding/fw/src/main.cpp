#include <Arduino.h>
#include <Lawicel.h>
#include <SerialAdapter.h>
#include <CANAdapter.h>
#include <NVMAdapter.h>


void setup()
{
  CANAdapter sja1000Adapter;
  SerialAdapter serialAdapter;
  NVMAdapter flashAdapter;

  Lawicel protocolLawicel(&serialAdapter, &sja1000Adapter, &flashAdapter);

  protocolLawicel.begin();
}

void loop()
{

}