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
@file       Lawicel.cpp

Driver for Lawicel Protocol @ref Lawicel.h


***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "Lawicel.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

const uint16_t Lawicel::MAX_TIMESTAMP = 0xEA5F;  /**< Maximum value of a Timestamp, representing 1 Minute. */
const String Lawicel::X_VERSION = "V0101";       /**< Hardware and Software Version. */
const String Lawicel::X_SERIAL_NUMBER = "NNT32"; /**< Hardware Serial Number. */
const char Lawicel::CR = 13;                     /**< CR Character as OK Line Terminator. */
const char Lawicel::BELL = 7;                    /**< BEL Character as ERROR Line Terminator. */
const uint8_t Lawicel::MAX_COMMAND_LENGTH = 30;  /**< Maximum Length of a Lawicel Command. */

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
 *  Handles the Lawicel Protocol 
 * 
 *  @return  success
 */
bool Lawicel::executeCycle()
{
    bool success = true;
    m_serialReturn.clear();

    if (m_autoPolling)
    {
        if (autopoll())
        {
            m_serialReturn += CR;
            m_selectedSerial->print(m_serialReturn);
        }
    }

    m_serialReturn.clear();
    char c = BELL;

    if (m_selectedSerial->read(c))
    {
        if ('\r' == c)
        {
            if (!receiveCommand(m_serialInput))
            {
                m_serialReturn += BELL;
                m_selectedSerial->print(m_serialReturn);
                success = false;
            }
            else
            {
                m_serialReturn += CR;
                m_selectedSerial->print(m_serialReturn);
            }

            m_serialInput.clear();
        }
        else if (MAX_COMMAND_LENGTH < m_serialInput.length())
        {
            success = false;
            m_serialInput.clear();
        }
        else if (BELL != c)
        {
            m_serialInput += c;
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Initializes Module 
 * 
 *  @return  success
 */
bool Lawicel::begin()
{
    bool success = true;
    if (!m_selectedNVM->begin())
    {
        success = false;
    }
    receiveCommand(m_selectedNVM->readString(m_selectedNVM->INIT_SERIAL_BAUD));

    if (!m_selectedSerial->begin())
    {
        success = false;
    }
    else if (!m_selectedCAN->begin())
    {
        success = false;
    }
    else
    {
        m_timestamp = m_selectedNVM->readInt(m_selectedNVM->INIT_TIMESTAMP);

        m_autoStart = m_selectedNVM->readInt(m_selectedNVM->INIT_AUTO_START);

        if (0 < m_autoStart)
        {
            m_autoPolling = true;

            receiveCommand(m_selectedNVM->readString(m_selectedNVM->INIT_CAN_BAUD));

            receiveCommand(m_selectedNVM->readString(m_selectedNVM->INIT_FILTER_MODE));

            receiveCommand(m_selectedNVM->readString(m_selectedNVM->INIT_FILTER_ACN));

            receiveCommand(m_selectedNVM->readString(m_selectedNVM->INIT_FILTER_AMN));
        }

        if (1 == m_autoStart)
        {
            if (!receiveCommand("O"))
            {
                success = false;
            }
        }
        else if (2 == m_autoStart)
        {
            if (!receiveCommand("L"))
            {
                success = false;
            }
        }
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Terminates Module 
 * 
 *  @return  success
 */
bool Lawicel::end()
{
    bool success = true;

    if (!m_selectedSerial->end())
    {
        success = false;
    }
    if (!m_selectedCAN->end())
    {
        success = false;
    }
    if (!m_selectedNVM->end())
    {
        success = false;
    }

    return success;
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/**************************************************************************************************/

/**
 *  Translates char symbols of a Byte into hex values
 * 
 *  @param[in] msb  Most Significant bits of resulting Byte
 *  @param[in] lsb  Least Significant bits of resulting Byte
 *  @param[in,out] result   Resulting Byte
 *  @return success 
 */
bool Lawicel::charToByte(char msb, char lsb, uint8_t &result)
{
    bool success = true;
    uint8_t msbInteger = 0;
    uint8_t lsbInteger = 0;

    if (charToInt(msb, msbInteger))
    {
        if (charToInt(lsb, lsbInteger))
        {
            result = msbInteger * 16;
            result += lsbInteger;
        }
        else
        {
            success = false;
        }
    }
    else
    {
        success = false;
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Translates char symbols of numbers into int values
 *  @param[in] num_symbol   Char to convert
 *  @param[in,out] result   Resulting integer
 *  @return success
 */
bool Lawicel::charToInt(char num_symbol, uint8_t &result)
{
    bool success = true;
    switch (num_symbol)
    {
    case '0':
        result = 0x0;
        break;
    case '1':
        result = 0x1;
        break;
    case '2':
        result = 0x2;
        break;
    case '3':
        result = 0x3;
        break;
    case '4':
        result = 0x4;
        break;
    case '5':
        result = 0x5;
        break;
    case '6':
        result = 0x6;
        break;
    case '7':
        result = 0x7;
        break;
    case '8':
        result = 0x8;
        break;
    case '9':
        result = 0x9;
        break;
    case 'a':
    case 'A':
        result = 0xA;
        break;
    case 'b':
    case 'B':
        result = 0xB;
        break;
    case 'c':
    case 'C':
        result = 0xC;
        break;
    case 'd':
    case 'D':
        result = 0xD;
        break;
    case 'e':
    case 'E':
        result = 0xE;
        break;
    case 'f':
    case 'F':
        result = 0xF;
        break;

    default:
        success = false;
        break;
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Translates char ID into its corresponding integer value 
 * 
 *  @param[in] extended True if Frame is Extended, false otherwise
 *  @param[in] lawicelCMD Frame in Lawicel Format
 *  @param[in,out] result Resulting ID
 *  @return success
 */
bool Lawicel::decodeId(bool extended, const String &lawicelCMD, uint32_t &result)
{
    bool success = true;
    uint32_t output = 0;
    uint8_t IdLength = 3;

    if (extended)
    {
        IdLength = 8;
    }

    for (int counter = 0; counter < IdLength; counter++)
    {
        uint8_t var = 0;
        if (charToInt(lawicelCMD[counter + 1], var))
        {
            output += (var << (4 * (IdLength - counter - 1)));
        }
        else
        {
            success = false;
        }
    }

    if (success)
    {
        result = output;
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Receives and Interprets Buffer with Serial Command 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::receiveCommand(const String &lawicelCMD)
{
    bool success = true;
    switch (lawicelCMD.charAt(0))
    {
    case SET_BAUDRATE:
        success = setBaudrateCmd(lawicelCMD);
        break;

    case SET_BTR:
        success = setBTRCmd(lawicelCMD);
        break;

    case OPEN_NORMAL:
        success = openNormalCmd(lawicelCMD);
        break;

    case OPEN_LISTEN_ONLY:
        success = openListenOnlyCmd(lawicelCMD);
        break;

    case CLOSE:
        success = closeCmd(lawicelCMD);
        break;

    case TX_STD:
        success = stdTxCmd(lawicelCMD);
        break;

    case TX_EXT:
        success = extTxCmd(lawicelCMD);
        break;

    case TX_STD_RTR:
        success = stdRtrTxCmd(lawicelCMD);
        break;

    case TX_EXT_RTR:
        success = extRtrTxCmd(lawicelCMD);
        break;

    case POLL_SINGLE:
        success = singlePollCmd(lawicelCMD);
        break;

    case POLL_ALL:
        success = allPollCmd(lawicelCMD);
        break;

    case POLL_AUTO:
        success = toggleAutoPollCmd(lawicelCMD);
        break;

    case STATUS_FLAGS:
        success = getFlagsCmd(lawicelCMD);
        break;

    case FILTER_MODE:
        success = setFilterModeCmd(lawicelCMD);
        break;

    case ACN_REGISTER:
        success = setACnCmd(lawicelCMD);
        break;

    case AMN_REGISTER:
        success = setAMnCmd(lawicelCMD);
        break;

    case SERIAL_BAUDRATE:
        success = setSerialBaudrateCmd(lawicelCMD);
        break;

    case VERSION:
        success = getVersionCmd(lawicelCMD);
        break;

    case SERIAL_NUMBER:
        success = getSerialNumberCmd(lawicelCMD);
        break;

    case TOGGLE_TIMESTAMP:
        success = toggleTimeStampCmd(lawicelCMD);
        break;

    case AUTO_START:
        success = toggleAutoStartCmd(lawicelCMD);
        break;

    case CURRENT_PARAMS:
        success = getCurrentParams(lawicelCMD);
        break;

    default:
        success = false;
        break;
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Sets Baudrate through presets 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::setBaudrateCmd(const String &lawicelCMD)
{
    bool success = true;

    uint32_t baudrate = 0;

    if (2 != lawicelCMD.length())
    {
        success = false;
    }
    else if (CANInterface::CLOSED != m_selectedCAN->getChannelState())
    {
        success = false;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
            baudrate = 10E3;
            break;

        case '1':
            baudrate = 20E3;
            break;

        case '2':
            baudrate = 50E3;
            break;

        case '3':
            baudrate = 100E3;
            break;

        case '4':
            baudrate = 125E3;
            break;

        case '5':
            baudrate = 250E3;
            break;

        case '6':
            baudrate = 500E3;
            break;

        case '7':
            baudrate = 800E3;
            break;

        case '8':
            baudrate = 1000E3;
            break;

        default:
            success = false;
            break;
        }
    }

    if (success)
    {
        m_selectedNVM->save(m_selectedNVM->INIT_CAN_BAUD, lawicelCMD);
        success = m_selectedCAN->setBaudrate(baudrate);
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Sets Baudrate through Registers 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::setBTRCmd(const String &lawicelCMD)
{
    bool success = true;

    if (5 != lawicelCMD.length())
    {
        success = false;
    }
    else if (CANInterface::CLOSED != m_selectedCAN->getChannelState())
    {
        success = false;
    }
    else
    {
        uint8_t BTR0 = 0;
        uint8_t BTR1 = 0;

        if (!charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), BTR0))
        {
            success = false;
        }

        if (!charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), BTR1))
        {
            success = false;
        }

        if (success)
        {
            success = m_selectedCAN->setBTR(BTR0, BTR1);
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Opens CAN Channel in Normal Mode 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::openNormalCmd(const String &lawicelCMD)
{
    bool success = true;

    if (1 != lawicelCMD.length())
    {
        success = false;
    }
    else if (CANInterface::CLOSED != m_selectedCAN->getChannelState())
    {
        success = false;
    }
    else
    {
        success = m_selectedCAN->setState(CANInterface::NORMAL);
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Opens CAN Channel in Listen-Only Mode 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::openListenOnlyCmd(const String &lawicelCMD)
{
    bool success = true;

    if (1 != lawicelCMD.length())
    {
        success = false;
    }
    else if (CANInterface::CLOSED != m_selectedCAN->getChannelState())
    {
        success = false;
    }
    else
    {
        success = m_selectedCAN->setState(CANInterface::LISTEN_ONLY);
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Closes CAN Channel 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::closeCmd(const String &lawicelCMD)
{
    bool success = true;

    if (1 != lawicelCMD.length())
    {
        success = false;
        ;
    }
    else if (CANInterface::CLOSED == m_selectedCAN->getChannelState())
    {
        success = false;
    }
    else
    {
        success = m_selectedCAN->setState(CANInterface::CLOSED);
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Transmits standard CAN Frame (11-bit ID)
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::stdTxCmd(const String &lawicelCMD)
{
    bool success = true;

    if (5 > lawicelCMD.length())
    {
        success = false;
    }
    else if (CANInterface::NORMAL != m_selectedCAN->getChannelState())
    {
        success = false;
    }
    else
    {
        uint8_t dlc = 0;
        if (!charToInt(lawicelCMD.charAt(4), dlc))
        {
            success = false;
        }
        else
        {
            uint32_t id = 0;
            if (!decodeId(0, lawicelCMD, id))
            {
                success = false;
            }
            else
            {
                if (((2 * dlc) + 5) != lawicelCMD.length())
                {
                    success = false;
                }
                else
                {
                    CANInterface::Frame frame;
                    frame.m_id = id;
                    frame.m_dlc = dlc;

                    int frameposition = 0;
                    for (int bufferPosition = 5; bufferPosition < (dlc * 2 + 4); bufferPosition += 2, frameposition++)
                    {
                        uint8_t resultByte = 0;

                        if (!charToByte(lawicelCMD.charAt(bufferPosition), lawicelCMD.charAt(bufferPosition + 1), resultByte))
                        {
                            success = false;
                        }
                        else
                        {
                            frame.m_data[frameposition] = resultByte;
                        }
                    }

                    if (success)
                    {
                        success = m_selectedCAN->send(frame);
                    }
                }
            }
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Transmits extended CAN Frame (29-bit ID) 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::extTxCmd(const String &lawicelCMD)
{
    bool success = true;

    if (10 > lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        success = false;
    }
    else
    {
        uint8_t dlc = 0;
        if (!charToInt(lawicelCMD.charAt(9), dlc))
        {
            success = false;
        }
        else
        {
            uint32_t id = 0;
            if (!decodeId(1, lawicelCMD, id))
            {
                success = false;
            }
            else
            {
                if (lawicelCMD.length() != ((2 * dlc) + 10))
                {
                    success = false;
                }
                else
                {
                    CANInterface::Frame frame;
                    frame.m_id = id;
                    frame.m_dlc = dlc;
                    frame.m_extended = true;

                    int frameposition = 0;
                    for (int bufferPosition = 10; bufferPosition < (dlc * 2 + 9); bufferPosition += 2, frameposition++)
                    {
                        uint8_t resultByte = 0;
                        if (!charToByte(lawicelCMD.charAt(bufferPosition), lawicelCMD.charAt(bufferPosition + 1), resultByte))
                        {
                            success = false;
                        }
                        else
                        {
                            frame.m_data[frameposition] = resultByte;
                        }
                    }

                    if (success)
                    {
                        success = m_selectedCAN->send(frame);
                    }
                }
            }
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Transmits standard RTR CAN Frame (11-bit ID) 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::stdRtrTxCmd(const String &lawicelCMD)
{
    bool success = true;

    if (5 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        success = false;
    }
    else
    {
        uint32_t id = 0;
        if (!decodeId(0, lawicelCMD, id))
        {
            success = false;
        }
        else
        {
            uint8_t dlc = 0;
            if (!charToInt(lawicelCMD.charAt(4), dlc))
            {
                success = false;
            }
            else
            {
                CANInterface::Frame frame;
                frame.m_id = id;
                frame.m_dlc = dlc;
                frame.m_rtr = true;
                success = m_selectedCAN->send(frame);
            }
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Transmits extended RTR CAN Frame (29-bit ID) 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::extRtrTxCmd(const String &lawicelCMD)
{
    bool success = true;

    if (10 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        success = false;
    }
    else
    {
        uint8_t dlc = 0;
        if (!charToInt(lawicelCMD.charAt(9), dlc))
        {
            success = false;
        }
        else
        {
            uint32_t id = 0;
            if (!decodeId(1, lawicelCMD, id))
            {
                success = false;
            }
            else
            {
                CANInterface::Frame frame;
                frame.m_id = id;
                frame.m_dlc = dlc;
                frame.m_extended = true;
                frame.m_rtr = true;
                success = m_selectedCAN->send(frame);
            }
        }
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Poll incomming FIFO for CAN frames (single poll) 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::singlePollCmd(const String &lawicelCMD)
{
    bool success = true;

    if (1 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        CANInterface::Frame frame;
        if (m_selectedCAN->pollSingle(frame))
        {
            char cmd = 't';
            int idLength = 3;
            if (frame.m_extended == true && frame.m_rtr == false)
            {
                cmd = 'T';
                idLength = 8;
            }
            else if (frame.m_extended == false && frame.m_rtr == true)
            {
                cmd = 'r';
            }
            else if (frame.m_extended == true && frame.m_rtr == true)
            {
                cmd = 'R';
                idLength = 8;
            }

            m_serialReturn += cmd;

            String idVar = String(frame.m_id, HEX);
            for (int i = 0; i < idLength - idVar.length(); i++)
            {
                m_serialReturn += '0';
            }
            m_serialReturn += idVar;

            m_serialReturn += frame.m_dlc;

            if (false == frame.m_rtr)
            {
                for (int i = 0; i < frame.m_dlc; i++)
                {
                    if (0x10 > frame.m_data[i])
                    {
                        m_serialReturn += '0';
                    }
                    m_serialReturn += String(frame.m_data[i], HEX);
                }
            }

            if (m_timestamp)
            {
                m_serialReturn += getFormattedTimestamp();
            }
        }
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Polls incomming FIFO for CAN frames (all pending frames) 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::allPollCmd(const String &lawicelCMD)
{
    bool success = true;

    if (1 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        while (singlePollCmd(lawicelCMD))
        {
            if (m_serialReturn.isEmpty())
            {
                break;
            }
            else
            {
                m_serialReturn += (char)CR;
                m_selectedSerial->print(m_serialReturn);
                m_serialReturn.clear();
            }
        }

        m_serialReturn += 'A';
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Toggles Auto Poll for inconming Frames 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::toggleAutoPollCmd(const String &lawicelCMD)
{
    bool success = true;

    if (2 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
            m_autoPolling = false;
            break;
        case '1':
            m_autoPolling = true;
            break;

        default:
            success = false;
            break;
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Read Status Flags
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::getFlagsCmd(const String &lawicelCMD)
{
    bool success = true;
    if (1 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        m_serialReturn += String(m_selectedCAN->getStatusFlags(), HEX);
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Sets Filter Mode 0 = Dual-Filter, 1 = Single-Filter 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::setFilterModeCmd(const String &lawicelCMD)
{
    bool success = true;
    CANInterface::FILTER_MODE filterMode;
    if (2 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
            filterMode = CANInterface::DUAL_FILTER;
            break;

        case '1':
            filterMode = CANInterface::SINGLE_FILTER;
            break;

        default:
            success = false;
            break;
        }

        if (success)
        {
            m_selectedNVM->save(m_selectedNVM->INIT_FILTER_MODE, lawicelCMD);
            success = m_selectedCAN->setFilterMode(filterMode);
        }
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Sets Acceptance Code Register 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::setACnCmd(const String &lawicelCMD)
{
    bool success = true;

    if (9 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        CANInterface::Filter acn;

        if (!charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), acn.m_filterBytes[0]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), acn.m_filterBytes[1]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(5), lawicelCMD.charAt(6), acn.m_filterBytes[2]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(7), lawicelCMD.charAt(8), acn.m_filterBytes[3]))
        {
            success = false;
        }

        if (success)
        {
            m_selectedNVM->save(m_selectedNVM->INIT_FILTER_ACN, lawicelCMD);
            success = m_selectedCAN->setACn(acn);
        }
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Sets Acceptance Mask Register
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::setAMnCmd(const String &lawicelCMD)
{
    bool success = true;

    if (9 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        CANInterface::Filter amn;

        if (!charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), amn.m_filterBytes[0]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), amn.m_filterBytes[1]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(5), lawicelCMD.charAt(6), amn.m_filterBytes[2]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(7), lawicelCMD.charAt(8), amn.m_filterBytes[3]))
        {
            success = false;
        }

        if (success)
        {
            m_selectedNVM->save(m_selectedNVM->INIT_FILTER_AMN, lawicelCMD);
            success = m_selectedCAN->setAMn(amn);
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Sets UART Baudrate (and saves setting on EEPROM) 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::setSerialBaudrateCmd(const String &lawicelCMD)
{
    bool success = true;
    long _baudrate = 0;

    if (2 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
            _baudrate = 230400;
            break;

        case '1':
            _baudrate = 115200;
            break;

        case '2':
            _baudrate = 57600;
            break;

        case '3':
            _baudrate = 38400;
            break;

        case '4':
            _baudrate = 19200;
            break;

        case '5':
            _baudrate = 9600;
            break;

        case '6':
            _baudrate = 2400;
            break;

        default:
            success = false;
            break;
        }

        if (success)
        {
            m_selectedNVM->save(m_selectedNVM->INIT_SERIAL_BAUD, lawicelCMD);
            success = m_selectedSerial->setBaudrate(_baudrate);
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 * Sends Hardware and Software Version 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::getVersionCmd(const String &lawicelCMD)
{
    bool success = true;

    if (1 != lawicelCMD.length())
    {
        success = false;
    }
    else
    {
        m_serialReturn += X_VERSION;
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Sends Serial Number of Hardware 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::getSerialNumberCmd(const String &lawicelCMD)
{
    bool success = true;

    if (1 != lawicelCMD.length())
    {
        success = false;
    }
    else
    {
        m_serialReturn += X_SERIAL_NUMBER;
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Toggles Timestamp (and saves setting on EEPROM) 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::toggleTimeStampCmd(const String &lawicelCMD)
{
    bool success = true;

    if (2 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
            m_timestamp = false;
            m_selectedNVM->save(m_selectedNVM->INIT_TIMESTAMP, 0);
            break;

        case '1':
            m_timestamp = true;
            m_selectedNVM->save(m_selectedNVM->INIT_TIMESTAMP, 1);
            break;

        default:
            success = false;
            break;
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Auto Startup feature (from power on) 
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::toggleAutoStartCmd(const String &lawicelCMD)
{
    bool success = true;

    if (2 != lawicelCMD.length())
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
            m_autoStart = 0;
            m_selectedNVM->save(m_selectedNVM->INIT_AUTO_START, 0);
            break;

        case '1':
            m_autoStart = 1;
            m_selectedNVM->save(m_selectedNVM->INIT_AUTO_START, 1);
            break;

        case '2':
            m_autoStart = 2;
            m_selectedNVM->save(m_selectedNVM->INIT_AUTO_START, 2);
            break;

        default:
            success = false;
            break;
        }
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Sends the current configuration of the CAN Bus to the Client
 * 
 *  @param[in] lawicelCMD Lawicel-formatted String
 *  @return success
 */
bool Lawicel::getCurrentParams(const String &lawicelCMD)
{
    bool success = true;

    if (1 != lawicelCMD.length())
    {
        success = false;
    }
    else
    {
        m_serialReturn += 'D';
        m_serialReturn += m_selectedNVM->readInt(m_selectedNVM->INIT_AUTO_START);
        m_serialReturn += m_selectedNVM->readString(m_selectedNVM->INIT_CAN_BAUD);
        m_serialReturn += m_selectedNVM->readInt(m_selectedNVM->INIT_TIMESTAMP);
        m_serialReturn += (uint8_t)m_selectedCAN->getChannelState();
    }

    return success;
}

/**************************************************************************************************/

/**
 *  Frame Polling without any extra tags
 * 
 *  @return success
 */
bool Lawicel::autopoll()
{
    bool success = true;

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        CANInterface::Frame frame;
        if (m_selectedCAN->pollSingle(frame))
        {
            char cmd = 't';
            int idLength = 3;
            if ((true == frame.m_extended) && (false == frame.m_rtr))
            {
                cmd = 'T';
                idLength = 8;
            }
            else if ((false == frame.m_extended) && (true == frame.m_rtr))
            {
                cmd = 'r';
            }
            else if ((true == frame.m_extended) && (true == frame.m_rtr))
            {
                cmd = 'R';
                idLength = 8;
            }

            m_serialReturn += cmd;

            String idHex = String(frame.m_id, HEX);
            for (int i = 0; i < idLength - idHex.length(); i++)
            {
                m_serialReturn += '0';
            }
            m_serialReturn += idHex;

            m_serialReturn += frame.m_dlc;

            if (false == frame.m_rtr)
            {
                for (int i = 0; i < frame.m_dlc; i++)
                {
                    if (0x10 > frame.m_data[i])
                    {
                        m_serialReturn += '0';
                    }
                    m_serialReturn += String(frame.m_data[i], HEX);
                }
            }

            if (m_timestamp)
            {
                m_serialReturn += getFormattedTimestamp();
            }
        }
        else
        {
            success = false;
        }
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Returns formatted Timestamp
 * 
 * @return timestamp 
 */
String Lawicel::getFormattedTimestamp()
{
    String timestamp;
    String temp = String(millis() % MAX_TIMESTAMP, HEX);

    for (int i = 0; i < (4 - temp.length()); i++)
    {
        timestamp += '0';
    }

    timestamp += temp;

    return timestamp;
}

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

/** @} */