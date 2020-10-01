#ifndef LAWICEL_H_
#define LAWICEL_H_

#include <CAN.h>

class Lawicel
{
public:
    void getBegin();

private:
    ESP32SJA1000Class SJA1000;
    long _baudrate = 500E3;       //Standard Baudrate 500Kbps
};

#endif