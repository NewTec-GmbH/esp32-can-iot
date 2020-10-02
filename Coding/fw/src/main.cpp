#include <Arduino.h>
#include <Lawicel.h>

Lawicel ESPCAN;

void receiver()
{
  // try to parse packet
  int packetSize = ESPCAN.SJA1000.parsePacket();

  if (packetSize)
  {
    // received a packet
    Serial.print("Received ");

    if (ESPCAN.SJA1000.packetExtended())
    {
      Serial.print("extended ");
    }

    if (ESPCAN.SJA1000.packetRtr())
    {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(ESPCAN.SJA1000.packetId(), HEX);


    if (ESPCAN.SJA1000.packetRtr())
    {
      Serial.print(" and requested length ");
      Serial.println(ESPCAN.SJA1000.packetDlc());
    }
    else
    {
      Serial.print(" and length ");
      Serial.println(packetSize);
      Serial.println();
    }
    Serial.println();
  }
}

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
  if(ESPCAN.readSerial()){
    Serial.println("Error");
  }


  if (ESPCAN.getState() == 1 || ESPCAN.getState() == 2)
  {
    receiver();
  }
}