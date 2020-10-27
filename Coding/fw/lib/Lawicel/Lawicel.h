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

/**
* Key Definition (Adresses) to be read by NVM Adapter for initialization
*/

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/*
* Lawicel Class contains the protocol to communicate between a Serial connection and a CAN Controller using ASCII symbols.
*/
class Lawicel
{
public:
    /* CONSTANTS ******************************************************************************/
    static const uint16_t MAX_TIMESTAMP; /**< Maximum value of a Timestamp, representing 1 Minute. */
    static const String X_VERSION;       /**< Hardware and Software Version. */
    static const String X_SERIAL_NUMBER; /**< Hardware Serial Number. */
    static const char CR;                /**< CR Character as OK Line Terminator */
    static const char BELL;              /**< BEL Character as ERROR Line Terminator */

    /**
    * Key Definition (Addresses) to be read by NVM Adapter for initialization
    */
    static const String INIT_SERIAL_BAUD; /**< Initial Serial Baudrate*/
    static const String INIT_TIMESTAMP;   /**< Initial State of Timestamp*/
    static const String INIT_AUTO_START;  /**< Initial State of Autostart*/
    static const String INIT_CAN_BAUD;    /**< Initial CAN Baudrate*/
    static const String INIT_FILTER_MODE; /**< Initial Filter Mode*/
    static const String INIT_FILTER_ACN;  /**< Initial Filter Address*/
    static const String INIT_FILTER_AMN;  /**< Initial Filter Mask*/

    /* TYPES **********************************************************************************/

    /**
    * Default Constructor for a Lawicel Instance. This is the only Constructor available. 
    * @ref http://www.can232.com/docs/can232_v3.pdf
    * @param serialInt             Serial Adapter (from abstract class SerialInterface) that 
    *                              connects the Serial capabilities of the board to the protocol.
    * @param canInt                CAN Adapter (from abstract class CANInterface) that
    *                              connects the CAN Controller of the board to the protocol.
    * @param nvmint                Non-Volatile Memory Adapter (from abstract class NVMInterface) that
    *                              connects the NVM capability of the board to the protocol.
    */
    Lawicel(SerialInterface &serialInt, CANInterface &canInt, NVMInterface &nvmInt) : m_selectedSerial(&serialInt),
                                                                                      m_selectedCAN(&canInt),
                                                                                      m_selectedNVM(&nvmInt)
    {
    }

    /**
     *  Default destructor deletes instance of the class.
     */
    ~Lawicel()
    {
    }

    uint8_t executeCycle(); /**< Handles the Serial Messages */
    void begin();           /**< Initializes Module */
    void end();             /**< Terminates Module */

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

    enum CMD_STATE : int
    {
        OK = 0,       /**< Command processed with no Errors*/
        ERROR,        /**< Error. Command not processed*/
        END_OF_BUFFER /**< No Error. End of CAN Frame Receiving Buffer */
    };

    bool charToByte(char msb, char lsb, uint8_t &result);                     /**< Translates char symbols of a Byte into hex values */
    bool charToInt(char symbol, uint8_t &result);                             /**< Translates char symbols of numbers into int values */
    bool IdDecode(bool extended, const String &lawicelCMD, uint32_t &result); /**< Translates char ID into value */

    uint8_t receiveCommand(const String &lawicelCMD);       /**< Receives and Interprets Buffer with Serial Command */
    uint8_t setBaudrateCmd(const String &lawicelCMD);       /**< Sets Baudrate through presets */
    uint8_t setBTRCmd(const String &lawicelCMD);            /**< Sets Baudrate through Registers */
    uint8_t openNormalCmd(const String &lawicelCMD);        /**< Opens CAN Channel in Normal Mode */
    uint8_t openListenOnlyCmd(const String &lawicelCMD);    /**< Opens CAN Channel in Listen-Only Mode */
    uint8_t closeCmd(const String &lawicelCMD);             /**< Closes CAN Channel */
    uint8_t stdTxCmd(const String &lawicelCMD);             /**< Transmits standard CAN Frame (11-bit ID) */
    uint8_t extTxCmd(const String &lawicelCMD);             /**< Transmits extended CAN Frame (29-bit ID) */
    uint8_t stdRtrTxCmd(const String &lawicelCMD);          /**< Transmits standard RTR CAN Frame (11-bit ID) */
    uint8_t extRtrTxCmd(const String &lawicelCMD);          /**< Transmits extended RTR CAN Frame (29-bit ID) */
    uint8_t singlePollCmd(const String &lawicelCMD);        /**< Poll incomming FIFO for CAN frames (single poll) */
    uint8_t allPollCmd(const String &lawicelCMD);           /**< Polls incomming FIFO for CAN frames (all pending frames) */
    uint8_t toggleAutoPollCmd(const String &lawicelCMD);    /**< Toggles Auto Poll for inconming Frames */
    uint8_t getFlagsCmd(const String &lawicelCMD);          /**< Read Status Flags */
    uint8_t setFilterModeCmd(const String &lawicelCMD);     /**< Sets Filter Mode 0 = Dual-Filter, 1 = Single-Filter */
    uint8_t setACnCmd(const String &lawicelCMD);            /**< Sets Acceptance Code Register */
    uint8_t setAMnCmd(const String &lawicelCMD);            /**< Sets Acceptance Mask Register */
    uint8_t setSerialBaudrateCmd(const String &lawicelCMD); /**< Sets UART Baudrate (and saves setting on EEPROM) */
    uint8_t getVersionCmd(const String &lawicelCMD);        /**< Sends Hardware and Software Version */
    uint8_t getSerialNumberCmd(const String &lawicelCMD);   /**< Sends Serial Number of Hardware */
    uint8_t toggleTimeStampCmd(const String &lawicelCMD);   /**< Toggles Timestamp (and saves setting on EEPROM) */
    uint8_t toggleAutoStartCmd(const String &lawicelCMD);   /**< Auto Startup feature (from power on) */

    uint8_t autopoll();      /**< Frame Polling without any extra tags */
    uint32_t getTimestamp(); /**< Returns Timestamp */

    bool m_timestamp = false;   /**< Toggle timestamp */
    bool m_autoPolling = true;  /**< Toggle Auto-Polling */
    String m_serialInput = "";  /**< Input String for Serial-Message */
    String m_serialReturn = ""; /**< String sent back to SerialAdapter */
    uint8_t m_autoStart = 0;    /**< Sets Auto Start Mode */

    SerialInterface *m_selectedSerial; /**< Active Serial Adapter */
    CANInterface *m_selectedCAN;       /**< Active CAN Adapter */
    NVMInterface *m_selectedNVM;       /**< Active NVM Adapter */

private:
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