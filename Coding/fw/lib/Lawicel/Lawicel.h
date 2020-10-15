/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Lawicel
@{
@file       Lawicel.h

Driver for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef LAWICEL_H_
#define LAWICEL_H_

/* INCLUDES ***************************************************************************************/
#include <Arduino.h>
#include <string.h>
#include <CANInterface.h>
#include <SerialInterface.h>
#include <NVMInterface.h>

#define MAX_TIMESTAMP 0xEA5F    /**< Maximum value of a Timestamp, representing 1 Minute. */
#define X_VERSION "V0101"       /**< Hardware and Software Version. */
#define X_SERIAL_NUMBER "NNT32" /**< Hardware Serial Number. */
#define CR 13                   /**< CR Character as OK Line Terminator */
#define BELL 7                  /**< BEL Character as ERROR Line Terminator */

/**
* Key Definition (Adresses) to be read by NVM Adapter for initialization
*/
#define INIT_SERIAL_BAUD "SerialBaud"
#define INIT_TIMESTAMP "ToggleTime"
#define INIT_AUTO_START "AutoStart"
#define INIT_CAN_BAUD "CanBaud"
#define INIT_FILTER_MODE "FilterMode"
#define INIT_FILTER_ACN "FilterACn"
#define INIT_FILTER_AMN "FilterAMn"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

class Lawicel
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
    * Constructor
    */
    Lawicel(SerialInterface *_serialInt, CANInterface *_canInt, NVMInterface *_nvmInt) : m_selectedSerial(_serialInt),
                                                                                         m_selectedCAN(_canInt),
                                                                                         m_selectedNVM(_nvmInt)
    {
    }

    /**
     *  Default Destructor
     */
    ~Lawicel()
    {
    }

    bool handler(); /**< Handles the Serial Messages */
    void begin();   /**< Initializes Module */
    void end();     /**< Terminates Module */

private:
    /**
     * Enum of Possible Lawicel Commands to be received via Serial Adapter
     */
    enum ASCII_COMMANDS : char
    {
        SET_BAUDRATE = 'S',     /**< Setup with standard CAN bit-rates */
        SET_BTR = 's',          /**< Setup with modified BTR0/BTR1 Registers for different bit-rates */
        OPEN_NORMAL = 'O',      /**< Open CAN Channel in normal mode */
        OPEN_LISTEN_ONLY = 'L', /**< Open CAN Channel in listen-only mode */
        CLOSE = 'C',            /**< Close CAN Channel */
        TX_STD = 't',           /**< Transmits standard CAN Frame (11-bit ID) */
        TX_EXT = 'T',           /**< Transmits extended CAN Frame (29-bit ID) */
        TX_STD_RTR = 'r',       /**< Transmits standard RTR CAN Frame (11-bit ID) */
        TX_EXT_RTR = 'R',       /**< Transmits extended RTR CAN Frame (29-bit ID) */
        POLL_SINGLE = 'P',      /**< Single Poll for incoming CAN Frames */
        POLL_ALL = 'A',         /**< Poll for all pending CAN Frames */
        POLL_AUTO = 'X',        /**< Auto-Poll/Send ON/OFF for received Frames */
        STATUS_FLAGS = 'F',     /**< Read Status Flags */
        FILTER_MODE = 'W',      /**< Filter mode Setting */
        ACN_REGISTER = 'M',     /**< Sets Acceptance Code Register */
        AMN_REGISTER = 'm',     /**< Sets Acceptance Mask Register */
        SERIAL_BAUDRATE = 'U',  /**< Setup Serial Communication Baudrate */
        VERSION = 'V',          /**< Gets Version of Software and Hardware */
        SERIAL_NUMBER = 'N',    /**< Gets Serial Number of the Hardware */
        TOGGLE_TIMESTAMP = 'Z', /**< Sets Time Stamp ON/OFF */
        AUTO_START = 'Q'        /**< Auto-Startup with CAN Channel open and filters */
    };

    uint8_t charToByte(char MSB, char LSB); /**< Translates char symbols of a Byte into hex values */
    uint8_t charToInt(char symbol);         /**< Translates char symbols of numbers into int values */
    uint32_t IdDecode(bool extended);       /**< Translates char ID into value */

    uint8_t receiveCommand();          /**< Receives and Interprets Buffer with Serial Command */
    uint8_t CMD_Set_Baudrate();        /**< Sets Baudrate through presets */
    uint8_t CMD_Set_BTR();             /**< Sets Baudrate through Registers */
    uint8_t CMD_Open_Normal();         /**< Opens CAN Channel in Normal Mode */
    uint8_t CMD_Open_Listen_Only();    /**< Opens CAN Channel in Listen-Only Mode */
    uint8_t CMD_Close();               /**< Closes CAN Channel */
    uint8_t CMD_Tx_Std();              /**< Transmits standard CAN Frame (11-bit ID) */
    uint8_t CMD_Tx_Ext();              /**< Transmits extended CAN Frame (29-bit ID) */
    uint8_t CMD_Tx_Std_RTR();          /**< Transmits standard RTR CAN Frame (11-bit ID) */
    uint8_t CMD_Tx_Ext_RTR();          /**< Transmits extended RTR CAN Frame (29-bit ID) */
    uint8_t CMD_Poll_Single();         /**< Poll incomming FIFO for CAN frames (single poll) */
    uint8_t CMD_Poll_All();            /**< Polls incomming FIFO for CAN frames (all pending frames) */
    uint8_t CMD_Poll_Auto();           /**< Toggles Auto Poll for inconming Frames */
    uint8_t CMD_Flags();               /**< Read Status Flags */
    uint8_t CMD_Set_Filter_Mode();     /**< Sets Filter Mode 0 = Dual-Filter, 1 = Single-Filter */
    uint8_t CMD_Set_ACn();             /**< Sets Acceptance Code Register */
    uint8_t CMD_Set_AMn();             /**< Sets Acceptance Mask Register */
    uint8_t CMD_Set_Serial_Baudrate(); /**< Sets UART Baudrate (and saves setting on EEPROM) */
    uint8_t CMD_Version();             /**< Sends Hardware and Software Version */
    uint8_t CMD_Serial_Number();       /**< Sends Serial Number of Hardware */
    uint8_t CMD_Timestamp();           /**< Toggles Timestamp (and saves setting on EEPROM) */
    uint8_t CMD_Auto_Start();          /**< Auto Startup feature (from power on) */

    uint8_t Autopoll(); /**< Frame Polling without any extra tags */
    uint32_t getTimestamp(); /**< Returns Timestamp */

    bool m_timestamp = false;   /**< Toggle timestamp */
    bool m_autoPolling = true;  /**< Toggle Auto-Polling */
    String m_serialInput;       /**< Input String for Serial-Message */
    String m_serialReturn = ""; /**< String sent back to SerialAdapter */
    uint8_t m_length = 0;       /**< Length of Serial-Message */
    uint8_t m_autostart = 0;    /**< Sets Auto Start Mode */

    SerialInterface *m_selectedSerial; /**< Active Serial Adapter */
    CANInterface *m_selectedCAN;       /**< Active CAN Adapter */
    NVMInterface *m_selectedNVM;       /**< Active NVM Adapter */

    /**
     *  Preventing copying, assigning and using an empty constructor
     */
    Lawicel();
    Lawicel(const Lawicel &prot);
    Lawicel &operator=(const Lawicel &prot);
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* LAWICEL_H */