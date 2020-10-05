#ifndef LAWICEL_H_
#define LAWICEL_H_
#include <Arduino.h>

class CANInterface;

class Lawicel
{
    /* ------------------------------------------------------------------------------*/
public:
    enum BUS_STATE : int
    {
        CLOSED,
        NORMAL,
        LISTEN_ONLY,
        UNDEFINED = -1
    };

    struct Frame
    {
        uint32_t ID;         //CAN ID
        bool RTR;            //Identifies a RTR Frame
        bool Extended;       //Identifies an Extended Frame
        uint8_t DLC;         //Data Length
        uint8_t *Data; //Data of the Frame

        Frame() : ID(0U),
                  RTR(false),
                  Extended(false),
                  DLC(0U),
                  Data(nullptr)
        {
        }
    };

    struct CANCommand
    {
        BUS_STATE State;      //Sets Channel State
        long Baudrate;        //Sets Baudrate
        uint8_t BTR0; //Sets BTR registers
        uint8_t BTR1;
        bool FilterMode;      //Sets Filter Mode 0 = Dual-Filter, 1 = Single-Filter
        uint32_t ACn;   //Sets Acceptance Code Register
        uint32_t AMn;   //Sets Acceptance Mask Register

        CANCommand() 
        {
            State=(UNDEFINED);
            Baudrate = 0;
            BTR0 = 0;
            BTR1 = 0;
            FilterMode = false;
            ACn = 0U;
            AMn = 0U;
        }
    };

    struct SerialCommand
    {
        long Baudrate;  //Sets Serial Baudrate
        bool Timestamp; //Toggles Timestamp
    };

    uint8_t readSerial(); //Read Serial input and calls receiveCommand()
    uint8_t getState();   //Returns State of the CAN Channel

    /* ------------------------------------------------------------------------------*/
private: //Private Variables
    enum ASCII_COMMANDS : char
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
        AUTO_START = 'Q'        //Auto-Startup with CAN Channel open and filters
    };

    BUS_STATE _channelState = CLOSED; //Channel State
    char buffer[32];                  //Buffer for Serial-Message
    int _length = 0;                  //Length of Serial-Message
    const char CR = 13;               //Serial-Message Termination
    const char BEL = 7;               //Warning Response
    /* ------------------------------------------------------------------------------*/
private:                                    //Private Functions
    uint8_t charToByte(char MSB, char LSB); //Translates char symbols into hex values
    uint8_t charToInt(char symbol);         //Translates char symbols of numbers into int values
    uint32_t IdDecode(bool extended);       //Translates char std ID int value
    uint8_t receiveCommand();               //Receives and Interprets Buffer with Serial Command
    uint8_t CMD_Set_Baudrate();             //Sets Baudrate through presets
    uint8_t CMD_Set_BTR();                  //Sets Baudrate through Registers
    uint8_t CMD_Open_Normal();              //Opens CAN Channel in Normal Mode
    uint8_t CMD_Open_Listen_Only();         //Opens CAN Channel in Listen-Only Mode
    uint8_t CMD_Close();                    //Closes CAN Channel
    uint8_t CMD_Tx_Std();                   //Transmits standard CAN Frame (11-bit ID)
    uint8_t CMD_Tx_Ext();                   //Transmits extended CAN Frame (29-bit ID)

    CANInterface *m_selectedCAN;
};

class CANInterface
{
public:
    virtual void send(Lawicel::Frame &Frame) = 0;
    virtual void send(Lawicel::CANCommand &CANCommand) = 0;

private:
};

#endif