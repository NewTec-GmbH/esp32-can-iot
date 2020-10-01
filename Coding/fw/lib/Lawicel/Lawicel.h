#ifndef LAWICEL_H_
#define LAWICEL_H_

#include <CAN.h>

#define BELL 7

class Lawicel
{
    /* ------------------------------------------------------------------------------*/
public:
    void readSerial(); //Read Serial input and calls receiveCommand()
    uint8_t receiveCommand(const char buffer[], const int length);

    /* ------------------------------------------------------------------------------*/
private:                        //Private Variables
    ESP32SJA1000Class SJA1000;  //CAN Controller

    enum ASCII_Commands : char
    {
        SET_BAUDRATE = 'S',     //Setup with standard CAN bit-rates
        SET_BTR = 's',          //Setup with modified BTR0/BTR1 Registers for different bit-rates
        OPEN_NORMAL = 'O',      //Open CAN Channel in normal mode
        OPEN_LISTEN_ONLY = 'L', //Open CAN Channel in listen-only mode
        CLOSE = 'C',            //Close CAN Channel
        TX_STD = 't',           //Transmits standard CAN Frame (11-bit ID)
        TX_EXT = 'T',           //Transmits extended CAN Frame (29-bit ID)
        TX_STD_RTR = 'r',       //Transmits standard RTR CAN Frame (11-bit ID)
        TX_EXT_RTR = 'R',       //Transmits extended RTR CAN Frame (29-bit ID)
        POLL_SINGLE = 'P',      //Single Poll for incoming CAN Frames (Disabled)
        POLL_ALL = 'A',         //Poll for all pending CAN Frames (Disabled)
        POLL_AUTO = 'X',        //Auto-Poll/Send ON/OFF for received Frames
        STATUS_FLAGS = 'F',     //Read Status Flags
        FILTER_MODE = 'W',      //Filter mode Setting
        ACN_REGISTER = 'M',     //Sets Acceptance Code Register
        AMN_REGISTER = 'm',     //Sets Acceptance Mask Register
        SERIAL_BAUDRATE = 'U',  //Setup Serial Communication Baudrate
        VERSION = 'V',          //Gets Version of Software and Hardware
        SERIAL_NUMBER = 'N',    //Gets Serial Number of the Hardware
        SET_TIMESTAMP = 'Z',    //Sets Time Stamp ON/OFF
        AUTO_START = 'Q'       //Auto-Startup with CAN Channel open and filters
    };

    enum State : int
    {
        CLOSED,
        NORMAL,
        LISTEN_ONLY
    };

    long _baudrate = 500E3;    //Standard Baudrate 500Kbps
    char buffer[32];           //Buffer for Serial Messages
    int channelState = CLOSED; //Channel State
    const char CR = 13;
    const char BEL = 7;
    /* ------------------------------------------------------------------------------*/
private: //Private Functions
    void getBegin();
};

#endif