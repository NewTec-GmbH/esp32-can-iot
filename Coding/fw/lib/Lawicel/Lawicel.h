/***************************************************************************************************
BSD 3-Clause License


Copyright (c) 2020-2021, NewTec GmbH - www.newtec.de
All rights reserved.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:


1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.


2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.


3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************************************/
/**
@addtogroup Lawicel
@{
@file       Lawicel.h

Driver for Lawicel Protocol

***************************************************************************************************/
#ifndef LAWICEL_H_
#define LAWICEL_H_

/* INCLUDES ***************************************************************************************/
#include <Arduino.h>
#include "CANInterface.h"
#include "SerialInterface.h"
#include "NVMInterface.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
 *  Lawicel Class contains the protocol to communicate between a Serial connection and a CAN Controller using ASCII symbols.
 */
class Lawicel
{
public:
    /* CONSTANTS ******************************************************************************/
    static const uint16_t MAX_TIMESTAMP;     /**< Maximum value of a Timestamp, representing 1 Minute. */
    static const String X_VERSION;           /**< Hardware and Software Version. */
    static const String X_SERIAL_NUMBER;     /**< Hardware Serial Number. */
    static const char CR;                    /**< CR Character as OK Line Terminator. */
    static const char BELL;                  /**< BEL Character as ERROR Line Terminator. */
    static const uint8_t MAX_COMMAND_LENGTH; /**< Maximum Length of a Lawicel Command. */

    /* TYPES **********************************************************************************/

    /**
     *   Default Constructor for a Lawicel Instance. This is the only Constructor available. 
     *   http://www.can232.com/docs/can232_v3.pdf
     *   @param[in,out] serialInt             Serial Adapter (from abstract class SerialInterface) that 
     *                                          connects the Serial capabilities of the board to the protocol.
     *   @param[in,out] canInt                CAN Adapter (from abstract class CANInterface) that
     *                                          connects the CAN Controller of the board to the protocol.
     *   @param[in,out] nvmInt                Non-Volatile Memory Adapter (from abstract class NVMInterface) that
     *                                          connects the NVM capability of the board to the protocol.
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

    bool executeCycle(); /**< Handles the Lawicel Protocol */
    bool begin();        /**< Initializes Module */
    bool end();          /**< Terminates Module */

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
        AUTO_START = 'Q',       /**< Auto-Startup with CAN Channel open and filters */
        /** Extension of the Lawicel Protocol **/
        CURRENT_PARAMS = 'D', /**< Returns the current configuration of the CAN Bus */
    };

    bool charToByte(char msb, char lsb, uint8_t &result);                     /**< Translates char symbols of a Byte into hex values */
    bool charToInt(char symbol, uint8_t &result);                             /**< Translates char symbols of numbers into int values */
    bool decodeId(bool extended, const String &lawicelCMD, uint32_t &result); /**< Translates char ID into its corresponding integer value */

    bool receiveCommand(const String &lawicelCMD);       /**< Receives and Interprets Buffer with Serial Command */
    bool setBaudrateCmd(const String &lawicelCMD);       /**< Sets Baudrate through presets */
    bool setBTRCmd(const String &lawicelCMD);            /**< Sets Baudrate through Registers */
    bool openNormalCmd(const String &lawicelCMD);        /**< Opens CAN Channel in Normal Mode */
    bool openListenOnlyCmd(const String &lawicelCMD);    /**< Opens CAN Channel in Listen-Only Mode */
    bool closeCmd(const String &lawicelCMD);             /**< Closes CAN Channel */
    bool stdTxCmd(const String &lawicelCMD);             /**< Transmits standard CAN Frame (11-bit ID) */
    bool extTxCmd(const String &lawicelCMD);             /**< Transmits extended CAN Frame (29-bit ID) */
    bool stdRtrTxCmd(const String &lawicelCMD);          /**< Transmits standard RTR CAN Frame (11-bit ID) */
    bool extRtrTxCmd(const String &lawicelCMD);          /**< Transmits extended RTR CAN Frame (29-bit ID) */
    bool singlePollCmd(const String &lawicelCMD);        /**< Poll incomming FIFO for CAN frames (single poll) */
    bool allPollCmd(const String &lawicelCMD);           /**< Polls incomming FIFO for CAN frames (all pending frames) */
    bool toggleAutoPollCmd(const String &lawicelCMD);    /**< Toggles Auto Poll for inconming Frames */
    bool getFlagsCmd(const String &lawicelCMD);          /**< Read Status Flags */
    bool setFilterModeCmd(const String &lawicelCMD);     /**< Sets Filter Mode 0 = Dual-Filter, 1 = Single-Filter */
    bool setACnCmd(const String &lawicelCMD);            /**< Sets Acceptance Code Register */
    bool setAMnCmd(const String &lawicelCMD);            /**< Sets Acceptance Mask Register */
    bool setSerialBaudrateCmd(const String &lawicelCMD); /**< Sets UART Baudrate (and saves setting on EEPROM) */
    bool getVersionCmd(const String &lawicelCMD);        /**< Sends Hardware and Software Version */
    bool getSerialNumberCmd(const String &lawicelCMD);   /**< Sends Serial Number of Hardware */
    bool toggleTimeStampCmd(const String &lawicelCMD);   /**< Toggles Timestamp (and saves setting on EEPROM) */
    bool toggleAutoStartCmd(const String &lawicelCMD);   /**< Auto Startup feature (from power on) */
    bool getCurrentParams(const String &lawicelCMD);     /**< Sends the current configuration of the CAN Bus to the Client*/

    bool autopoll();                /**< Frame Polling without any extra tags */
    String getFormattedTimestamp(); /**< Returns formatted Timestamp */

    bool m_timestamp = false;   /**< Toggle timestamp */
    bool m_autoPolling = true;  /**< Toggle Auto-Polling */
    String m_serialInput = "";  /**< Input String for Serial-Message */
    String m_serialReturn = ""; /**< String sent back to SerialAdapter */
    uint8_t m_autoStart = 0;    /**< Sets Auto Start Mode */

    SerialInterface *m_selectedSerial; /**< Active Serial Adapter */
    CANInterface *m_selectedCAN;       /**< Active CAN Adapter */
    NVMInterface *m_selectedNVM;       /**< Active NVM Adapter */

private:
    /** Preventing using an empty constructor */
    Lawicel();

    /** An instance shall not be copied. */
    Lawicel(const Lawicel &prot);

    /** An instance shall not assigned. */
    Lawicel &operator=(const Lawicel &prot);
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* LAWICEL_H */

/** @} */