#ifndef LAWICEL_H_
#define LAWICEL_H_
#include <Arduino.h>
#include <CANInterface.h>
#include <SerialInterface.h>

#define MAX_CANS 2U
#define MAX_SERIALS 2U
#define MAX_TIMESTAMP 0xEA5F
#define X_VERSION "V0101"
#define X_SERIAL_NUMBER "NNT32"
#define CR 13
#define BELL 7

class Lawicel
{
public:
    bool registerCANInterface(CANInterface *_can);
    void unregisterCANInterface(CANInterface *_can);
    bool selectCANInterface(const String &name);

    bool registerSerialInterface(SerialInterface *_serial);
    void unregisterSerialInterface(SerialInterface *_serial);
    bool selectSerialinterface(const String &name);

private:
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
        TOGGLE_TIMESTAMP = 'Z', //Sets Time Stamp ON/OFF
        AUTO_START = 'Q'        //Auto-Startup with CAN Channel open and filters
    };

    uint8_t charToByte(char MSB, char LSB); //Translates char symbols into hex values
    uint8_t charToInt(char symbol);         //Translates char symbols of numbers into int values
    uint32_t IdDecode(bool extended);       //Translates char ID into value
    int getTimestamp();
    
    uint8_t receiveCommand(); //Receives and Interprets Buffer with Serial Command#

    uint8_t CMD_Set_Baudrate();        //Sets Baudrate through presets
    uint8_t CMD_Set_BTR();             //Sets Baudrate through Registers
    uint8_t CMD_Open_Normal();         //Opens CAN Channel in Normal Mode
    uint8_t CMD_Open_Listen_Only();    //Opens CAN Channel in Listen-Only Mode
    uint8_t CMD_Close();               //Closes CAN Channel
    uint8_t CMD_Tx_Std();              //Transmits standard CAN Frame (11-bit ID)
    uint8_t CMD_Tx_Ext();              //Transmits extended CAN Frame (29-bit ID)
    uint8_t CMD_Tx_Std_RTR();          //Transmits standard RTR CAN Frame (11-bit ID)
    uint8_t CMD_Tx_Ext_RTR();          //Transmits extended RTR CAN Frame (29-bit ID)
    uint8_t CMD_Poll_Single();         //Poll incomming FIFO for CAN frames (single poll)
    uint8_t CMD_Poll_All();            //Polls incomming FIFO for CAN frames (all pending frames)
    uint8_t CMD_Poll_Auto();           //Toggles Auto Poll for inconming Frames
    uint8_t CMD_Flags();               //Read Status Flags
    uint8_t CMD_Set_Filter_Mode();     //Sets Filter Mode 0 = Dual-Filter, 1 = Single-Filter
    uint8_t CMD_Set_ACn();             //Sets Acceptance Code Register
    uint8_t CMD_Set_AMn();             //Sets Acceptance Mask Register
    uint8_t CMD_Set_Serial_Baudrate(); //Sets UART Baudrate (and saves setting on EEPROM)
    uint8_t CMD_Version();             //Sends Hardware and Software Version
    uint8_t CMD_Serial_Number();       //Sends Serial Number of Hardware
    uint8_t CMD_Timestamp();           //Toggles Timestamp (and saves setting on EEPROM)
    uint8_t CMD_Auto_Start();          //Auto Startup feature (from power on)

    bool SerialHandler(uint8_t CMD); //Handles the Serial Messages

    char buffer[32];         //Input Buffer for Serial-Message
    uint8_t _length = 0;     //Length of Serial-Message
    bool _timestamp = false; //Toggle timestamp
    uint8_t _autostart;
    bool autoPolling = true;

    CANInterface *m_CANInterfaces[MAX_CANS];
    CANInterface *m_selectedCAN;

    SerialInterface *m_SerialInterfaces[MAX_SERIALS];
    SerialInterface *m_selectedSerial;
};

#endif