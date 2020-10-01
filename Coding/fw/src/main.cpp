#include <Arduino.h>
#include <Lawicel.h>

Lawicel ESPCAN;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop()
{
  // put your main code here, to run repeatedly:
  ESPCAN.readSerial();
}