#include <Lawicel.h>

void Lawicel::getBegin(){
    if(!SJA1000.begin(_baudrate)){
        Serial.println("Failed! Restarting...");
        delay(5000);
        ESP.restart();
    }
    else
    {
        Serial.println("CAN Ready!");
    }
}