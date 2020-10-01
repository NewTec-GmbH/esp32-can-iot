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

void Lawicel::readSerial()
{
    memset(buffer, '0', 32);

    
    if(Serial.available())
    {
        int availableBytes = Serial.available();
        Serial.println(availableBytes);
        for (int i = 0; i < availableBytes; i++)
        {
            buffer[i] = Serial.read();
            buffer[i + 1] = '\n';
        }
        for (int i = 0; i < availableBytes; i++)
        {
            Serial.printf("%c", buffer[i]);
        }
        Serial.println("");

        this->receiveCommand(buffer, availableBytes);

        Serial.println("");
    }
}