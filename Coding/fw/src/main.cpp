#include <Arduino.h>
#include <Lawicel.h>
#include <SerialAdapter.h>
#include <CANAdapter.h>


void setup()
{
  CANAdapter sja1000Adapter;
  SerialAdapter serialAdapter;
  NVMInterface* nvmIf = nullptr;

  Lawicel protocolLawicel(&serialAdapter, &sja1000Adapter, nvmIf);
}

void loop()
{

}