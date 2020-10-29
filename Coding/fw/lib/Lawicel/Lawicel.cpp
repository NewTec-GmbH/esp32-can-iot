/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Lawicel
@{
@file       Lawicel.cpp

Driver for Lawicel Protocol @ref Lawicel.h

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "Lawicel.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/
const uint16_t Lawicel::MAX_TIMESTAMP = 0xEA5F;
const String Lawicel::X_VERSION = "V0101";
const String Lawicel::X_SERIAL_NUMBER = "NNT32";
const char Lawicel::CR = 13;
const char Lawicel::BELL = 7;

const String Lawicel::INIT_SERIAL_BAUD = "SerialBaud";
const String Lawicel::INIT_TIMESTAMP = "ToggleTime";
const String Lawicel::INIT_AUTO_START = "AutoStart";
const String Lawicel::INIT_CAN_BAUD = "CanBaud";
const String Lawicel::INIT_FILTER_MODE = "FilterMode";
const String Lawicel::INIT_FILTER_ACN = "FilterACn";
const String Lawicel::INIT_FILTER_AMN = "FilterAMn";

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/
bool Lawicel::executeCycle()
{
    bool success = true;
    m_serialReturn = "";

    if (m_autoPolling)
    {
        if (autopoll())
        {
            m_serialReturn += CR;
            m_selectedSerial->print(m_serialReturn);
        }
    }

    m_serialReturn = "";
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

            m_serialInput = "";
        }
        else if (m_serialInput.length() > 30)
        {
            success = false;
            m_serialInput = "";
        }
        else if (c != BELL)
        {
            m_serialInput += c;
        }
    }
    
    return success;
}

/**************************************************************************************************/
bool Lawicel::begin()
{
    bool success = true;
    if (!m_selectedNVM->begin())
    {
        success = false;
    }
    else if (!receiveCommand(m_selectedNVM->readString(INIT_SERIAL_BAUD)))
    {
        success = false;
    }
    else if (!m_selectedSerial->begin())
    {
        success = false;
    }
    else if (!m_selectedCAN->begin())
    {
        success = false;
    }
    else
    {
        m_timestamp = m_selectedNVM->readInt(INIT_TIMESTAMP);

        m_autoStart = m_selectedNVM->readInt(INIT_AUTO_START);

        if (m_autoStart > 0)
        {
            m_autoPolling = true;

            if (!receiveCommand(m_selectedNVM->readString(INIT_CAN_BAUD)))
            {
                success = false;
            }
            if (!receiveCommand(m_selectedNVM->readString(INIT_FILTER_MODE)))
            {
                success = false;
            }
            if (!receiveCommand(m_selectedNVM->readString(INIT_FILTER_ACN)))
            {
                success = false;
            }
            if (!receiveCommand(m_selectedNVM->readString(INIT_FILTER_AMN)))
            {
                success = false;
            }
        }

        if (m_autoStart == 1)
        {
            if (!receiveCommand("O"))
            {
                success = false;
            }
        }
        else if (m_autoStart == 2)
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
bool Lawicel::charToByte(char msb, char lsb, uint8_t &result)
{
    bool success = true;
    uint8_t var = 0;
    if (charToInt(msb, var))
    {
        result = var * 16;
    }
    else
    {
        success = false;
    }

    if (charToInt(lsb, var))
    {
        result += var;
    }
    else
    {
        success = false;
    }

    return success;
}

/**************************************************************************************************/
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

    default:
        success = false;
        break;
    }

    return success;
}

/**************************************************************************************************/
bool Lawicel::setBaudrateCmd(const String &lawicelCMD)
{
    bool success = true;

    uint32_t baudrate = 0;

    if (lawicelCMD.length() != 2)
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
        m_selectedNVM->save(INIT_CAN_BAUD, lawicelCMD);
        success = m_selectedCAN->setBaudrate(baudrate);
    }

    return success;
}

/**************************************************************************************************/
bool Lawicel::setBTRCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 5)
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
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
bool Lawicel::openNormalCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 1)
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
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
bool Lawicel::openListenOnlyCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 1)
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
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
bool Lawicel::closeCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 1)
    {
        success = false;
        ;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
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
bool Lawicel::stdTxCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() < 5)
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
                if (lawicelCMD.length() != ((2 * dlc) + 5))
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
bool Lawicel::extTxCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() < 10)
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
bool Lawicel::stdRtrTxCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 5)
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
bool Lawicel::extRtrTxCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 10)
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
bool Lawicel::singlePollCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 1)
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

            if (frame.m_rtr == false)
            {
                for (int i = 0; i < frame.m_dlc; i++)
                {
                    m_serialReturn += String(frame.m_data[i], HEX);
                }
            }

            if (m_timestamp)
            {
                m_serialReturn += String(getTimestamp(), HEX);
            }
        }
    }
    return success;
}

/**************************************************************************************************/
bool Lawicel::allPollCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 1)
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
                m_serialReturn = "";
            }
        }

        m_serialReturn += 'A';
    }

    return success;
}

/**************************************************************************************************/
bool Lawicel::toggleAutoPollCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 2)
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
bool Lawicel::getFlagsCmd(const String &lawicelCMD)
{
    bool success = true;
    if (lawicelCMD.length() > 1)
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
bool Lawicel::setFilterModeCmd(const String &lawicelCMD)
{
    bool success = true;
    bool filterMode;
    if (lawicelCMD.length() != 2)
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
            filterMode = 0;
            break;

        case '1':
            filterMode = 1;
            break;

        default:
            success = false;
            break;
        }

        if (success)
        {
            m_selectedNVM->save(INIT_FILTER_MODE, lawicelCMD);
            success = m_selectedCAN->setFilterMode(filterMode);
        }
    }
    return success;
}

/**************************************************************************************************/
bool Lawicel::setACnCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 9)
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        CANInterface::FILTER acn;

        if (!charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), acn.data[0]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), acn.data[1]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(5), lawicelCMD.charAt(6), acn.data[2]))
        {
            success = false;
        }
        if (!charToByte(lawicelCMD.charAt(7), lawicelCMD.charAt(8), acn.data[3]))
        {
            success = false;
        }

        if (success)
        {
            m_selectedNVM->save(INIT_FILTER_ACN, lawicelCMD);
            success = m_selectedCAN->setACn(acn);
        }
    }
    return success;
}

/**************************************************************************************************/
bool Lawicel::setAMnCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 9)
    {
        success = false;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        success = false;
    }
    else
    {
        CANInterface::FILTER amn;

        if (charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), amn.data[0]))
        {
            success = false;
        }
        if (charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), amn.data[1]))
        {
            success = false;
        }
        if (charToByte(lawicelCMD.charAt(5), lawicelCMD.charAt(6), amn.data[2]))
        {
            success = false;
        }
        if (charToByte(lawicelCMD.charAt(7), lawicelCMD.charAt(8), amn.data[3]))
        {
            success = false;
        }

        if (success)
        {
            m_selectedNVM->save(INIT_FILTER_AMN, lawicelCMD);
            success = m_selectedCAN->setACn(amn);
        }
    }

    return success;
}

/**************************************************************************************************/
bool Lawicel::setSerialBaudrateCmd(const String &lawicelCMD)
{
    bool success = true;
    long _baudrate = 0;

    if (lawicelCMD.length() != 2)
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
            m_selectedNVM->save(INIT_SERIAL_BAUD, lawicelCMD);
            success = m_selectedSerial->setBaudrate(_baudrate);
        }
    }

    return success;
}

/**************************************************************************************************/
bool Lawicel::getVersionCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 1)
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
bool Lawicel::getSerialNumberCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 1)
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
bool Lawicel::toggleTimeStampCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 2)
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
            m_selectedNVM->save(INIT_TIMESTAMP, 0);
            break;

        case '1':
            m_timestamp = true;
            m_selectedNVM->save(INIT_TIMESTAMP, 1);
            break;

        default:
            success = false;
            break;
        }
    }

    return success;
}

/**************************************************************************************************/
bool Lawicel::toggleAutoStartCmd(const String &lawicelCMD)
{
    bool success = true;

    if (lawicelCMD.length() != 2)
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
            m_selectedNVM->save(INIT_AUTO_START, 0);
            break;

        case '1':
            m_autoStart = 1;
            m_selectedNVM->save(INIT_AUTO_START, 1);
            break;

        case '2':
            m_autoStart = 2;
            m_selectedNVM->save(INIT_AUTO_START, 2);
            break;

        default:
            success = false;
            break;
        }
    }

    return success;
}

/**************************************************************************************************/
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

            String idHex = String(frame.m_id, HEX);
            for (int i = 0; i < idLength - idHex.length(); i++)
            {
                m_serialReturn += '0';
            }
            m_serialReturn += idHex;

            m_serialReturn += frame.m_dlc;

            if (frame.m_rtr == false)
            {
                for (int i = 0; i < frame.m_dlc; i++)
                {
                    m_serialReturn += String(frame.m_data[i], HEX);
                }
            }

            if (m_timestamp)
            {
                m_serialReturn += String(getTimestamp(), HEX);
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
uint32_t Lawicel::getTimestamp()
{
    return millis() % MAX_TIMESTAMP;
}

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/