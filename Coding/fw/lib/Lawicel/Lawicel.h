#ifndef LAWICEL_H_
#define LAWICEL_H_

#include <CAN.h>

class Lawicel
{
    /* ------------------------------------------------------------------------------*/
public:
    void readSerial();         //Read Serial input and calls receiveCommand()
    uint8_t receiveCommand(const char buffer[], const int length);

    /* ------------------------------------------------------------------------------*/
private:                       //Private Variables
    ESP32SJA1000Class SJA1000; //CAN Controller

    long _baudrate = 500E3;    //Standard Baudrate 500Kbps
    char buffer[32];           //Buffer for Serial Messages
    /* ------------------------------------------------------------------------------*/

private: //Private Functions
    void getBegin();
};

#endif