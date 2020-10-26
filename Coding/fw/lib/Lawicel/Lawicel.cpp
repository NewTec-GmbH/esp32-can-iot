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
uint8_t Lawicel::executeCycle()
{
    uint8_t isError = 0;
    m_serialReturn = "";

    if (m_autoPolling)
    {
        if (autopoll() == 0)
        {
            m_selectedSerial->print(m_serialReturn += (char)CR);
        }
    }

    m_serialReturn = "";
    char c = '\a';
    m_selectedSerial->read(c);

    if ('\r' == c)
    {
        uint8_t CMD_status = receiveCommand(m_serialInput);

        if (m_serialInput.charAt(0) == POLL_SINGLE && CMD_status == 2)
        {
            CMD_status = 0;
        }

        if (CMD_status > 0)
        {
            m_serialReturn += (char)BELL;
            m_selectedSerial->print(m_serialReturn);
            isError = 1;
        }
        else if (m_serialInput.charAt(0) == VERSION)
        {
            m_serialReturn += X_VERSION;
            m_serialReturn += (char)CR;
            m_selectedSerial->print(m_serialReturn);
        }
        else if (m_serialInput.charAt(0) == SERIAL_NUMBER)
        {
            m_serialReturn += X_SERIAL_NUMBER;
            m_serialReturn += (char)CR;
            m_selectedSerial->print(m_serialReturn);
        }
        else
        {
            m_serialReturn += (char)CR;
            m_selectedSerial->print(m_serialReturn);
        }

        m_serialInput = "";
    }
    else if (m_serialInput.length() > 30)
    {
        isError = 1;
    }
    else if (c != '\a')
    {
        m_serialInput += c;
    }

    return isError;
}

/**************************************************************************************************/
void Lawicel::begin()
{
    m_selectedNVM->begin();

    receiveCommand(m_selectedNVM->readString(INIT_SERIAL_BAUD));

    m_selectedSerial->begin();
    m_selectedCAN->begin();

    m_timestamp = m_selectedNVM->readInt(INIT_TIMESTAMP);

    m_autoStart = m_selectedNVM->readInt(INIT_AUTO_START);

    if (m_autoStart > 0)
    {
        m_autoPolling = true;

        receiveCommand(m_selectedNVM->readString(INIT_CAN_BAUD));

        receiveCommand(m_selectedNVM->readString(INIT_FILTER_MODE));

        receiveCommand(m_selectedNVM->readString(INIT_FILTER_ACN));

        receiveCommand(m_selectedNVM->readString(INIT_FILTER_AMN));
    }

    if (m_autoStart == 1)
    {
        receiveCommand("O");
    }
    else if (m_autoStart == 2)
    {
        receiveCommand("L");
    }
}

/**************************************************************************************************/
void Lawicel::end()
{
    m_selectedSerial->end();
    m_selectedCAN->end();
    m_selectedNVM->end();
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/**************************************************************************************************/
bool Lawicel::charToByte(char msb, char lsb, uint8_t &result)
{
    bool isError = false;
    uint8_t output = 0xFF;

    if (msb >= 48 && msb <= 57)
    {
        output = (msb - 48) * 16;
    }
    else if (msb >= 65 && msb <= 70)
    {
        output = (msb - 55) * 16;
    }
    else if (msb >= 97 && msb <= 102)
    {
        output = (msb - 87) * 16;
    }
    else
    {
        isError = true;
    }

    if (lsb >= 48 && lsb <= 57)
    {
        output = output + (lsb - 48);
    }
    else if (lsb >= 65 && lsb <= 70)
    {
        output = output + (lsb - 55);
    }
    else if (lsb >= 97 && lsb <= 102)
    {
        output = output + (lsb - 87);
    }
    else
    {
        isError = true;
    }

    if (isError == false)
    {
        result = output;
    }

    return isError;
}

/**************************************************************************************************/
bool Lawicel::charToInt(char num_symbol, uint8_t &result)
{
    bool isError = false;
    uint8_t output = 0;
    if (num_symbol > 48 && num_symbol < 57)
    {
        output = num_symbol;
        output -= 48;
        result = output;
    }
    else
    {
        isError = true;
    }

    return isError;
}

/**************************************************************************************************/
bool Lawicel::IdDecode(bool extended, const String &lawicelCMD, uint32_t &result)
{
    bool isError = false;
    uint32_t output = 0;
    uint8_t _IdLength = 3;
    char _IdBuffer[8];

    if (extended)
    {
        _IdLength = 8;
        _IdBuffer[0] = lawicelCMD.charAt(8);
        _IdBuffer[1] = lawicelCMD.charAt(7);
        _IdBuffer[2] = lawicelCMD.charAt(6);
        _IdBuffer[3] = lawicelCMD.charAt(5);
        _IdBuffer[4] = lawicelCMD.charAt(4);
        _IdBuffer[5] = lawicelCMD.charAt(3);
        _IdBuffer[6] = lawicelCMD.charAt(2);
        _IdBuffer[7] = lawicelCMD.charAt(1);
    }
    else
    {
        _IdBuffer[0] = lawicelCMD.charAt(3);
        _IdBuffer[1] = lawicelCMD.charAt(2);
        _IdBuffer[2] = lawicelCMD.charAt(1);
    }

    for (int counter = 0; counter < _IdLength; counter++)
    {
        if (_IdBuffer[counter] >= 48 && _IdBuffer[counter] <= 57)
        {
            output = output + (_IdBuffer[counter] - 48) * pow(16.0, counter);
        }
        else if (_IdBuffer[counter] >= 65 && _IdBuffer[counter] <= 70)
        {
            output = output + (_IdBuffer[counter] - 55) * pow(16.0, counter);
        }
        else if (_IdBuffer[counter] >= 97 && _IdBuffer[counter] <= 102)
        {
            output = output + (_IdBuffer[counter] - 87) * pow(16.0, counter);
        }
        else
        {
            isError = 1;
        }
    }
    if (isError == false)
    {
        result = output;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::receiveCommand(const String &lawicelCMD)
{
    uint8_t isError = 0;
    switch (lawicelCMD.charAt(0))
    {
    case SET_BAUDRATE:
    {
        isError = setBaudrateCmd(lawicelCMD);
        break;
    }

    case SET_BTR:
    {
        isError = setBTRCmd(lawicelCMD);
        break;
    }

    case OPEN_NORMAL:
    {
        isError = openNormalCmd(lawicelCMD);
        break;
    }

    case OPEN_LISTEN_ONLY:
    {
        isError = openListenOnlyCmd(lawicelCMD);
        break;
    }

    case CLOSE:
    {
        isError = closeCmd(lawicelCMD);
        break;
    }

    case TX_STD:
    {
        isError = stdTxCmd(lawicelCMD);
        break;
    }

    case TX_EXT:
    {
        isError = extTxCmd(lawicelCMD);
        break;
    }

    case TX_STD_RTR:
    {
        isError = stdRtrTxCmd(lawicelCMD);
        break;
    }

    case TX_EXT_RTR:
    {
        isError = extRtrTxCmd(lawicelCMD);
        break;
    }

    case POLL_SINGLE:
    {
        isError = singlePollCmd(lawicelCMD);
        break;
    }

    case POLL_ALL:
    {
        isError = allPollCmd(lawicelCMD);
        break;
    }

    case POLL_AUTO:
    {
        isError = toggleAutoPollCmd(lawicelCMD);
        break;
    }

    case STATUS_FLAGS:
    {
        isError = getFlagsCmd(lawicelCMD);
        break;
    }

    case FILTER_MODE:
    {
        isError = setFilterModeCmd(lawicelCMD);
        break;
    }

    case ACN_REGISTER:
    {
        isError = setACnCmd(lawicelCMD);
        break;
    }

    case AMN_REGISTER:
    {
        isError = setAMnCmd(lawicelCMD);
        break;
    }

    case SERIAL_BAUDRATE:
    {
        isError = setSerialBaudrateCmd(lawicelCMD);
        break;
    }

    case VERSION:
    {
        isError = getVersionCmd(lawicelCMD);
        break;
    }

    case SERIAL_NUMBER:
    {
        isError = getSerialNumberCmd(lawicelCMD);
        break;
    }

    case TOGGLE_TIMESTAMP:
    {
        isError = toggleTimeStampCmd(lawicelCMD);
        break;
    }

    case AUTO_START:
    {
        isError = toggleAutoStartCmd(lawicelCMD);
        break;
    }

    default:
    {
        isError = 1;
        break;
    }
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setBaudrateCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    long _baudrate = 0;

    if (lawicelCMD.length() != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
        {
            _baudrate = 10E3;
            break;
        }
        case '1':
        {
            _baudrate = 20E3;
            break;
        }
        case '2':
        {
            _baudrate = 50E3;
            break;
        }
        case '3':
        {
            _baudrate = 100E3;
            break;
        }
        case '4':
        {
            _baudrate = 125E3;
            break;
        }
        case '5':
        {
            _baudrate = 250E3;
            break;
        }
        case '6':
        {
            _baudrate = 500E3;
            break;
        }
        case '7':
        {
            _baudrate = 800E3;
            break;
        }
        case '8':
        {
            _baudrate = 1000E3;
            break;
        }
        default:
        {
            isError = 1;
            break;
        }
        }
    }

    if (isError == 0)
    {
        m_selectedNVM->save(INIT_CAN_BAUD, lawicelCMD);
        isError = m_selectedCAN->setBaudrate(_baudrate);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setBTRCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() != 5)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        uint8_t BTR0 = 0;
        uint8_t BTR1 = 0;

        if (charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), BTR0) == 1)
        {
            isError = 1;
        }

        if (charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), BTR1) == 1)
        {
            isError = 1;
        }

        if (isError == 0)
        {
            isError = m_selectedCAN->setBTR(BTR0, BTR1);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::openNormalCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() > 1)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        isError = m_selectedCAN->setState(CANInterface::NORMAL);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::openListenOnlyCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() > 1)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        isError = m_selectedCAN->setState(CANInterface::LISTEN_ONLY);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::closeCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() > 1)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        isError = m_selectedCAN->setState(CANInterface::CLOSED);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::stdTxCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;
    CANInterface::Frame frame;
    uint8_t dlc = 0;
    if (charToInt(lawicelCMD.charAt(4), dlc) == true)
    {
        isError = 1;
    }

    uint32_t id = 0;
    if (IdDecode(0, lawicelCMD, id) == true)
    {
        isError = 1;
    }

    int frameposition = 0;

    frame.m_id = id;
    frame.m_dlc = dlc;

    if (lawicelCMD.length() != ((2 * dlc) + 5))
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = 1;
    }
    else
    {
        for (int bufferPosition = 5; bufferPosition < (dlc * 2 + 4); bufferPosition += 2, frameposition++)
        {
            uint8_t resultByte = 0;

            if (charToByte(lawicelCMD.charAt(bufferPosition), lawicelCMD.charAt(bufferPosition + 1), resultByte) == true)
            {
                isError = 1;
            }
            else
            {
                frame.m_data[frameposition] = resultByte;
            }
        }

        if (isError == 0)
        {
            isError = m_selectedCAN->send(frame);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::extTxCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;
    CANInterface::Frame frame;

    uint8_t dlc = 0;
    if (charToInt(lawicelCMD.charAt(9), dlc) == true)
    {
        isError = 1;
    }

    uint32_t id = 0;
    if (IdDecode(1, lawicelCMD, id) == true)
    {
        isError = 1;
    }

    int frameposition = 0;

    frame.m_id = id;
    frame.m_dlc = dlc;
    frame.m_extended = true;

    if (lawicelCMD.length() != ((2 * dlc) + 10))
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = 1;
    }
    else
    {
        for (int bufferPosition = 10; bufferPosition < (dlc * 2 + 9); bufferPosition += 2, frameposition++)
        {
            uint8_t resultByte = 0;
            if (charToByte(lawicelCMD.charAt(bufferPosition), lawicelCMD.charAt(bufferPosition + 1), resultByte) == true)
            {
                isError = 1;
            }
            else
            {
                frame.m_data[frameposition] = resultByte;
            }
        }

        if (isError == 0)
        {
            isError = m_selectedCAN->send(frame);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::stdRtrTxCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;
    CANInterface::Frame frame;

    uint8_t dlc = 0;
    if (charToInt(lawicelCMD.charAt(4), dlc) == true)
    {
        isError = 1;
    }

    uint32_t id = 0;
    if (IdDecode(0, lawicelCMD, id) == true)
    {
        isError = 1;
    }

    frame.m_id = id;
    frame.m_dlc = dlc;
    frame.m_rtr = true;

    if (lawicelCMD.length() != 5)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = 1;
    }
    else
    {
        isError = m_selectedCAN->send(frame);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::extRtrTxCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;
    CANInterface::Frame frame;

    uint8_t dlc = 0;
    if (charToInt(lawicelCMD.charAt(9), dlc) == true)
    {
        isError = 1;
    }

    uint32_t id = 0;
    if (IdDecode(1, lawicelCMD, id) == true)
    {
        isError = 1;
    }

    frame.m_id = id;
    frame.m_dlc = dlc;
    frame.m_extended = true;
    frame.m_rtr = true;

    if (lawicelCMD.length() != 10)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = 1;
    }
    else
    {
        isError = m_selectedCAN->send(frame);
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::singlePollCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() > 1)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        CANInterface::Frame frame;

        if (m_selectedCAN->pollSingle(frame) != 0)
        {
            char cmd = 't';
            int _id_length = 3;
            if (frame.m_extended == true && frame.m_rtr == false)
            {
                cmd = 'T';
                _id_length = 8;
            }
            else if (frame.m_extended == false && frame.m_rtr == true)
            {
                cmd = 'r';
            }
            else if (frame.m_extended == true && frame.m_rtr == true)
            {
                cmd = 'R';
                _id_length = 8;
            }

            m_serialReturn += cmd;

            String _ID = String(frame.m_id, HEX);
            for (int i = 0; i < _id_length - _ID.length(); i++)
            {
                m_serialReturn += '0';
            }
            m_serialReturn += _ID;

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
            isError = 2; /**< it is no error, but marks the end of the message buffer */
        }
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::allPollCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() > 1)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        while (singlePollCmd(lawicelCMD) == 0)
        {
            m_serialReturn += (char)CR;
            m_selectedSerial->print(m_serialReturn);
            m_serialReturn = "";
        }

        m_serialReturn += 'A';
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::toggleAutoPollCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
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
            isError = 1;
            break;
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::getFlagsCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;
    if (lawicelCMD.length() > 1)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        m_serialReturn += String(m_selectedCAN->getStatusFlags(), HEX);
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setFilterModeCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;
    bool filterMode;
    if (lawicelCMD.length() != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
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
            isError = 1;
            break;
        }

        if (isError == 0)
        {
            m_selectedNVM->save(INIT_FILTER_MODE, lawicelCMD);
            isError = m_selectedCAN->setFilterMode(filterMode);
        }
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setACnCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() != 9)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        uint8_t ACn[4];

        if (charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), ACn[0]) == true)
        {
            isError = 1;
        }
        if (charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), ACn[1]) == true)
        {
            isError = 1;
        }
        if (charToByte(lawicelCMD.charAt(5), lawicelCMD.charAt(6), ACn[2]) == true)
        {
            isError = 1;
        }
        if (charToByte(lawicelCMD.charAt(7), lawicelCMD.charAt(8), ACn[3]) == true)
        {
            isError = 1;
        }

        if (isError == 0)
        {
            m_selectedNVM->save(INIT_FILTER_ACN, lawicelCMD);

            isError = m_selectedCAN->setACn(ACn);
        }
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setAMnCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() != 9)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        uint8_t AMn[4];

        if (charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), AMn[0]) == true)
        {
            isError = 1;
        }
        if (charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), AMn[1]) == true)
        {
            isError = 1;
        }
        if (charToByte(lawicelCMD.charAt(5), lawicelCMD.charAt(6), AMn[2]) == true)
        {
            isError = 1;
        }
        if (charToByte(lawicelCMD.charAt(7), lawicelCMD.charAt(8), AMn[3]) == true)
        {
            isError = 1;
        }

        if (isError == 0)
        {
            m_selectedNVM->save(INIT_FILTER_AMN, lawicelCMD);

            isError = m_selectedCAN->setACn(AMn);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setSerialBaudrateCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    long _baudrate = 0;

    if (lawicelCMD.length() != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
        {
            _baudrate = 230400;
            break;
        }
        case '1':
        {
            _baudrate = 115200;
            break;
        }
        case '2':
        {
            _baudrate = 57600;
            break;
        }
        case '3':
        {
            _baudrate = 38400;
            break;
        }
        case '4':
        {
            _baudrate = 19200;
            break;
        }
        case '5':
        {
            _baudrate = 9600;
            break;
        }
        case '6':
        {
            _baudrate = 2400;
            break;
        }
        default:
        {
            isError = 1;
            break;
        }
        }

        if (isError == 0)
        {
            m_selectedNVM->save(INIT_SERIAL_BAUD, lawicelCMD);
            m_selectedSerial->setBaudrate(_baudrate);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::getVersionCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() > 1)
    {
        isError = 1;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::getSerialNumberCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() > 1)
    {
        isError = 1;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::toggleTimeStampCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
        {
            m_timestamp = false;
            m_selectedNVM->save(INIT_TIMESTAMP, 0);
            break;
        }
        case '1':
        {
            m_timestamp = true;
            m_selectedNVM->save(INIT_TIMESTAMP, 1);
            break;
        }
        default:
            isError = 1;
            break;
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::toggleAutoStartCmd(const String &lawicelCMD)
{
    uint8_t isError = 0;

    if (lawicelCMD.length() != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        switch (lawicelCMD.charAt(1))
        {
        case '0':
        {
            m_autoStart = 0;
            m_selectedNVM->save(INIT_AUTO_START, 0);
            break;
        }
        case '1':
        {
            m_autoStart = 1;
            m_selectedNVM->save(INIT_AUTO_START, 1);
            break;
        }
        case '2':
        {
            m_autoStart = 2;
            m_selectedNVM->save(INIT_AUTO_START, 2);
            break;
        }
        default:
            isError = 1;
            break;
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::autopoll()
{
    uint8_t isError = 0;

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        CANInterface::Frame frame;

        if (m_selectedCAN->pollSingle(frame) != 0)
        {
            char cmd = 't';
            int _id_length = 3;
            if (frame.m_extended == true && frame.m_rtr == false)
            {
                cmd = 'T';
                _id_length = 8;
            }
            else if (frame.m_extended == false && frame.m_rtr == true)
            {
                cmd = 'r';
            }
            else if (frame.m_extended == true && frame.m_rtr == true)
            {
                cmd = 'R';
                _id_length = 8;
            }

            m_serialReturn += cmd;

            String _ID = String(frame.m_id, HEX);
            for (int i = 0; i < _id_length - _ID.length(); i++)
            {
                m_serialReturn += '0';
            }
            m_serialReturn += _ID;

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
            isError = 2; /**< it is no error, but marks the end of the message buffer */
        }
    }
    return isError;
}

/**************************************************************************************************/
uint32_t Lawicel::getTimestamp()
{
    return millis() % MAX_TIMESTAMP;
}

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/