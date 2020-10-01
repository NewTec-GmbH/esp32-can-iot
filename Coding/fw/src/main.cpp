#include <Arduino.h>
#include <Lawicel.h>

Lawicel ESPCAN;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Welcome to NT ESP32 CAN Analyzer");
  Serial.println("Initializing...");
}

void loop()
{
  // put your main code here, to run repeatedly:
  ESPCAN.readSerial();
}