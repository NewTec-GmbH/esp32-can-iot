#include <Arduino.h>
#include <Lawicel.h>
#include <SerialAdapter.h>
#include <CANAdapter.h>


Lawicel ESPCAN;

void setup()
{
  CANAdapter CANChannel(String("SJA1000"), 500E3);

}

void loop()
{

}