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
#include <Lawicel.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

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
            m_serialReturn += (char)CR;
            m_selectedSerial->print(m_serialReturn);
        }
    }

    m_serialReturn = "";

    m_serialInput = m_selectedSerial->read();
    m_length = m_serialInput.length();

    if (m_length != 0)
    {
        uint8_t CMD_status = receiveCommand();

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
    }

    return isError;
}

/**************************************************************************************************/
void Lawicel::begin()
{
    m_selectedNVM->begin();

    m_serialInput = "";
    m_serialInput = m_selectedNVM->readString(INIT_SERIAL_BAUD);
    receiveCommand();

    m_selectedSerial->begin();
    m_selectedCAN->begin();

    m_timestamp = m_selectedNVM->readInt(INIT_TIMESTAMP);

    m_autoStart = m_selectedNVM->readInt(INIT_AUTO_START);

    if (m_autoStart > 0)
    {
        m_autoPolling = true;

        m_serialInput = m_selectedNVM->readString(INIT_CAN_BAUD);
        receiveCommand();

        m_serialInput = m_selectedNVM->readString(INIT_FILTER_MODE);
        receiveCommand();

        m_serialInput = m_selectedNVM->readString(INIT_FILTER_ACN);
        receiveCommand();

        m_serialInput = m_selectedNVM->readString(INIT_FILTER_AMN);
        receiveCommand();
    }

    if (m_autoStart == 1)
    {
        m_serialInput = "O";
        receiveCommand();
    }
    else if (m_autoStart == 2)
    {
        m_serialInput = "L";
        receiveCommand();
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
uint8_t Lawicel::charToByte(char MSB, char LSB)
{
    uint8_t result = 0xFF;

    if (MSB >= 48 && MSB <= 57)
    {
        result = (MSB - 48) * 16;
    }
    else if (MSB >= 65 && MSB <= 70)
    {
        result = (MSB - 55) * 16;
    }
    else if (MSB >= 97 && MSB <= 102)
    {
        result = (MSB - 87) * 16;
    }

    if (LSB >= 48 && LSB <= 57)
    {
        result = result + (LSB - 48);
    }
    else if (LSB >= 65 && LSB <= 70)
    {
        result = result + (LSB - 55);
    }
    else if (LSB >= 97 && LSB <= 102)
    {
        result = result + (LSB - 87);
    }

    return result;
}

/**************************************************************************************************/
uint8_t Lawicel::charToInt(char num_symbol)
{
    uint8_t result = 0;
    if (num_symbol > 48 && num_symbol < 57)
    {
        result = num_symbol;
        result -= 48;
    }

    return result;
}

/**************************************************************************************************/
uint32_t Lawicel::IdDecode(bool extended)
{
    uint32_t result = 0;
    uint8_t _IdLength = 3;
    char _IdBuffer[8];

    if (extended)
    {
        _IdLength = 8;
        _IdBuffer[0] = m_serialInput.charAt(8);
        _IdBuffer[1] = m_serialInput.charAt(7);
        _IdBuffer[2] = m_serialInput.charAt(6);
        _IdBuffer[3] = m_serialInput.charAt(5);
        _IdBuffer[4] = m_serialInput.charAt(4);
        _IdBuffer[5] = m_serialInput.charAt(3);
        _IdBuffer[6] = m_serialInput.charAt(2);
        _IdBuffer[7] = m_serialInput.charAt(1);
    }
    else
    {
        _IdBuffer[0] = m_serialInput.charAt(3);
        _IdBuffer[1] = m_serialInput.charAt(2);
        _IdBuffer[2] = m_serialInput.charAt(1);
    }

    for (int counter = 0; counter < _IdLength; counter++)
    {
        if (_IdBuffer[counter] >= 48 && _IdBuffer[counter] <= 57)
        {
            result = result + (_IdBuffer[counter] - 48) * pow(16.0, counter);
        }
        else if (_IdBuffer[counter] >= 65 && _IdBuffer[counter] <= 70)
        {
            result = result + (_IdBuffer[counter] - 55) * pow(16.0, counter);
        }
        else if (_IdBuffer[counter] >= 97 && _IdBuffer[counter] <= 102)
        {
            result = result + (_IdBuffer[counter] - 87) * pow(16.0, counter);
        }
    }

    return result;
}

/**************************************************************************************************/
uint8_t Lawicel::receiveCommand()
{
    uint8_t isError = 0;
    m_length = m_serialInput.length();
    switch (m_serialInput.charAt(0))
    {
    case SET_BAUDRATE:
    {
        isError = setBaudrateCmd();
        break;
    }

    case SET_BTR:
    {
        isError = setBTRCmd();
        break;
    }

    case OPEN_NORMAL:
    {
        isError = openNormalCmd();
        break;
    }

    case OPEN_LISTEN_ONLY:
    {
        isError = openListenOnlyCmd();
        break;
    }

    case CLOSE:
    {
        isError = closeCmd();
        break;
    }

    case TX_STD:
    {
        isError = stdTxCmd();
        break;
    }

    case TX_EXT:
    {
        isError = extTxCmd();
        break;
    }

    case TX_STD_RTR:
    {
        isError = stdRtrTxCmd();
        break;
    }

    case TX_EXT_RTR:
    {
        isError = extRtrTxCmd();
        break;
    }

    case POLL_SINGLE:
    {
        isError = singlePollCmd();
        break;
    }

    case POLL_ALL:
    {
        isError = allPollCmd();
        break;
    }

    case POLL_AUTO:
    {
        isError = toggleAutoPollCmd();
        break;
    }

    case STATUS_FLAGS:
    {
        isError = getFlagsCmd();
        break;
    }

    case FILTER_MODE:
    {
        isError = setFilterModeCmd();
        break;
    }

    case ACN_REGISTER:
    {
        isError = setACnCmd();
        break;
    }

    case AMN_REGISTER:
    {
        isError = setAMnCmd();
        break;
    }

    case SERIAL_BAUDRATE:
    {
        isError = setSerialBaudrateCmd();
        break;
    }

    case VERSION:
    {
        isError = getVersionCmd();
        break;
    }

    case SERIAL_NUMBER:
    {
        isError = getSerialNumberCmd();
        break;
    }

    case TOGGLE_TIMESTAMP:
    {
        isError = toggleTimeStampCmd();
        break;
    }

    case AUTO_START:
    {
        isError = toggleAutoStartCmd();
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
uint8_t Lawicel::setBaudrateCmd()
{
    uint8_t isError = 0;

    long _baudrate = 0;

    if (m_length != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        switch (m_serialInput.charAt(1))
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
        m_selectedNVM->saveString(INIT_CAN_BAUD, m_serialInput);
        isError = m_selectedCAN->setBaudrate(_baudrate);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setBTRCmd()
{
    uint8_t isError = 0;

    if (m_length != 5)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        uint8_t BTR0 = charToByte(m_serialInput.charAt(1), m_serialInput.charAt(2));
        uint8_t BTR1 = charToByte(m_serialInput.charAt(3), m_serialInput.charAt(4));

        isError = m_selectedCAN->setBTR(BTR0, BTR1);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::openNormalCmd()
{
    uint8_t isError = 0;

    if (m_length > 1)
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
uint8_t Lawicel::openListenOnlyCmd()
{
    uint8_t isError = 0;

    if (m_length > 1)
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
uint8_t Lawicel::closeCmd()
{
    uint8_t isError = 0;

    if (m_length > 1)
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
uint8_t Lawicel::stdTxCmd()
{
    uint8_t isError = 0;
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(m_serialInput.charAt(4));
    int32_t _id = IdDecode(0);
    int frameposition = 0;

    frame.m_id = _id;
    frame.m_dlc = _dlc;

    if (m_length != ((2 * _dlc) + 5))
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = 1;
    }
    else
    {
        for (int bufferPosition = 5; bufferPosition < (_dlc * 2 + 4); bufferPosition += 2, frameposition++)
        {
            frame.m_data[frameposition] = (charToByte(m_serialInput.charAt(bufferPosition), m_serialInput.charAt(bufferPosition + 1)));
        }

        isError = m_selectedCAN->send(frame);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::extTxCmd()
{
    uint8_t isError = 0;
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(m_serialInput.charAt(9));
    int32_t _id = IdDecode(1);
    int frameposition = 0;

    frame.m_id = _id;
    frame.m_dlc = _dlc;
    frame.m_extended = true;

    if (m_length != ((2 * _dlc) + 10))
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = 1;
    }
    else
    {
        for (int bufferPosition = 10; bufferPosition < (_dlc * 2 + 9); bufferPosition += 2, frameposition++)
        {
            frame.m_data[frameposition] = (charToByte(m_serialInput.charAt(bufferPosition), m_serialInput.charAt(bufferPosition + 1)));
        }

        isError = m_selectedCAN->send(frame);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::stdRtrTxCmd()
{
    uint8_t isError = 0;
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(m_serialInput.charAt(4));
    int32_t _id = IdDecode(0);

    frame.m_id = _id;
    frame.m_dlc = _dlc;
    frame.m_rtr = true;

    if (m_length != 5)
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
uint8_t Lawicel::extRtrTxCmd()
{
    uint8_t isError = 0;
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(m_serialInput.charAt(9));
    int32_t _id = IdDecode(1);

    frame.m_id = _id;
    frame.m_dlc = _dlc;
    frame.m_extended = true;
    frame.m_rtr = true;

    if (m_length != 10)
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
uint8_t Lawicel::singlePollCmd()
{
    uint8_t isError = 0;

    if (m_length > 1)
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
uint8_t Lawicel::allPollCmd()
{
    uint8_t isError = 0;

    if (m_length > 1)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        while (singlePollCmd() == 0)
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
uint8_t Lawicel::toggleAutoPollCmd()
{
    uint8_t isError = 0;

    if (m_length != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        switch (m_serialInput.charAt(1))
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
uint8_t Lawicel::getFlagsCmd()
{
    uint8_t isError = 0;
    if (m_length > 1)
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
uint8_t Lawicel::setFilterModeCmd()
{
    uint8_t isError = 0;
    bool filterMode;
    if (m_length != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        switch (m_serialInput.charAt(1))
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
            m_selectedNVM->saveString(INIT_FILTER_MODE, m_serialInput);
            isError = m_selectedCAN->setFilterMode(filterMode);
        }
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setACnCmd()
{
    uint8_t isError = 0;

    if (m_length != 9)
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

        ACn[0] = charToByte(m_serialInput.charAt(1), m_serialInput.charAt(2));
        ACn[1] = charToByte(m_serialInput.charAt(3), m_serialInput.charAt(4));
        ACn[2] = charToByte(m_serialInput.charAt(5), m_serialInput.charAt(6));
        ACn[3] = charToByte(m_serialInput.charAt(7), m_serialInput.charAt(8));

        m_selectedNVM->saveString(INIT_FILTER_ACN, m_serialInput);

        isError = m_selectedCAN->setACn(ACn);
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setAMnCmd()
{
    uint8_t isError = 0;

    if (m_length != 9)
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

        AMn[0] = charToByte(m_serialInput.charAt(1), m_serialInput.charAt(2));
        AMn[1] = charToByte(m_serialInput.charAt(3), m_serialInput.charAt(4));
        AMn[2] = charToByte(m_serialInput.charAt(5), m_serialInput.charAt(6));
        AMn[3] = charToByte(m_serialInput.charAt(7), m_serialInput.charAt(8));

        m_selectedNVM->saveString(INIT_FILTER_AMN, m_serialInput);

        isError = m_selectedCAN->setAMn(AMn);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setSerialBaudrateCmd()
{
    uint8_t isError = 0;

    long _baudrate = 0;

    if (m_length != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }
    else
    {
        switch (m_serialInput.charAt(1))
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
            m_selectedNVM->saveString(INIT_SERIAL_BAUD, m_serialInput);
            m_selectedSerial->setBaudrate(_baudrate);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::getVersionCmd()
{
    uint8_t isError = 0;

    if (m_length > 1)
    {
        isError = 1;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::getSerialNumberCmd()
{
    uint8_t isError = 0;

    if (m_length > 1)
    {
        isError = 1;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::toggleTimeStampCmd()
{
    uint8_t isError = 0;

    if (m_length != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        switch (m_serialInput.charAt(1))
        {
        case '0':
        {
            m_timestamp = false;
            m_selectedNVM->saveInt(INIT_TIMESTAMP, 0);
            break;
        }
        case '1':
        {
            m_timestamp = true;
            m_selectedNVM->saveInt(INIT_TIMESTAMP, 1);
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
uint8_t Lawicel::toggleAutoStartCmd()
{
    uint8_t isError = 0;

    if (m_length != 2)
    {
        isError = 1;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = 1;
    }
    else
    {
        switch (m_serialInput.charAt(1))
        {
        case '0':
        {
            m_autoStart = 0;
            m_selectedNVM->saveInt(INIT_AUTO_START, 0);
            break;
        }
        case '1':
        {
            m_autoStart = 1;
            m_selectedNVM->saveInt(INIT_AUTO_START, 1);
            break;
        }
        case '2':
        {
            m_autoStart = 2;
            m_selectedNVM->saveInt(INIT_AUTO_START, 2);
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