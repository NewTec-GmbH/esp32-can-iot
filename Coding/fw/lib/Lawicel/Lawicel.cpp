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
    uint8_t isError = OK;
    m_serialReturn = "";

    if (m_autoPolling)
    {
        if (autopoll() == 0)
        {
            m_selectedSerial->print(m_serialReturn += (char)CR);
        }
    }

    m_serialReturn = "";
    char c = BELL;
    m_selectedSerial->read(c);

    if ('\r' == c)
    {
        if (receiveCommand(m_serialInput) == ERROR)
        {
            m_serialReturn += (char)BELL;
            m_selectedSerial->print(m_serialReturn);
            isError = ERROR;
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
        isError = ERROR;
    }
    else if (c != BELL)
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
    bool isError = OK;
    uint8_t output = 0;

    switch (msb)
    {
    case '0':
        output = 0x00;
        break;
    case '1':
        output = 0x10;
        break;
    case '2':
        output = 0x20;
        break;
    case '3':
        output = 0x30;
        break;
    case '4':
        output = 0x40;
        break;
    case '5':
        output = 0x50;
        break;
    case '6':
        output = 0x60;
        break;
    case '7':
        output = 0x70;
        break;
    case '8':
        output = 0x80;
        break;
    case '9':
        output = 0x90;
        break;
    case 'a':
    case 'A':
        output = 0xA0;
        break;
    case 'b':
    case 'B':
        output = 0xB0;
        break;
    case 'c':
    case 'C':
        output = 0xC0;
        break;
    case 'd':
    case 'D':
        output = 0xD0;
        break;
    case 'e':
    case 'E':
        output = 0xE0;
        break;
    case 'f':
    case 'F':
        output = 0xF0;
        break;

    default:
        isError = ERROR;
        break;
    }

    switch (lsb)
    {
    case '0':
        output += 0x00;
        break;
    case '1':
        output += 0x1;
        break;
    case '2':
        output += 0x2;
        break;
    case '3':
        output += 0x3;
        break;
    case '4':
        output += 0x4;
        break;
    case '5':
        output += 0x5;
        break;
    case '6':
        output += 0x6;
        break;
    case '7':
        output += 0x7;
        break;
    case '8':
        output += 0x8;
        break;
    case '9':
        output += 0x9;
        break;
    case 'a':
    case 'A':
        output += 0xA;
        break;
    case 'b':
    case 'B':
        output += 0xB;
        break;
    case 'c':
    case 'C':
        output += 0xC;
        break;
    case 'd':
    case 'D':
        output += 0xD;
        break;
    case 'e':
    case 'E':
        output += 0xE;
        break;
    case 'f':
    case 'F':
        output += 0xF;
        break;

    default:
        isError = ERROR;
        break;
    }

    if (isError == OK)
    {
        result = output;
    }

    return isError;
}

/**************************************************************************************************/
bool Lawicel::charToInt(char num_symbol, uint8_t &result)
{
    bool isError = OK;
    uint8_t output = num_symbol - 48;
    result = output;
    return isError;
}

/***************************************
 * @todo
 ************************************************************/
bool Lawicel::IdDecode(bool extended, const String &lawicelCMD, uint32_t &result)
{
    bool isError = OK;
    uint32_t output = 0;
    uint8_t IdLength = 3;
    char IdBuffer[8];

    if (extended)
    {
        IdLength = 8;
        IdBuffer[0] = lawicelCMD.charAt(8);
        IdBuffer[1] = lawicelCMD.charAt(7);
        IdBuffer[2] = lawicelCMD.charAt(6);
        IdBuffer[3] = lawicelCMD.charAt(5);
        IdBuffer[4] = lawicelCMD.charAt(4);
        IdBuffer[5] = lawicelCMD.charAt(3);
        IdBuffer[6] = lawicelCMD.charAt(2);
        IdBuffer[7] = lawicelCMD.charAt(1);
    }
    else
    {
        IdBuffer[0] = lawicelCMD.charAt(3);
        IdBuffer[1] = lawicelCMD.charAt(2);
        IdBuffer[2] = lawicelCMD.charAt(1);
    }

    for (int counter = 0; counter < IdLength; counter++)
    {
        if (IdBuffer[counter] >= 48 && IdBuffer[counter] <= 57)
        {
            output = output + (IdBuffer[counter] - 48) * pow(16.0, counter);
        }
        else if (IdBuffer[counter] >= 65 && IdBuffer[counter] <= 70)
        {
            output = output + (IdBuffer[counter] - 55) * pow(16.0, counter);
        }
        else if (IdBuffer[counter] >= 97 && IdBuffer[counter] <= 102)
        {
            output = output + (IdBuffer[counter] - 87) * pow(16.0, counter);
        }
        else
        {
            isError = ERROR;
        }
    }
    if (isError == OK)
    {
        result = output;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::receiveCommand(const String &lawicelCMD)
{
    uint8_t isError = OK;
    switch (lawicelCMD.charAt(0))
    {
    case SET_BAUDRATE:
        isError = setBaudrateCmd(lawicelCMD);
        break;

    case SET_BTR:
        isError = setBTRCmd(lawicelCMD);
        break;

    case OPEN_NORMAL:
        isError = openNormalCmd(lawicelCMD);
        break;

    case OPEN_LISTEN_ONLY:
        isError = openListenOnlyCmd(lawicelCMD);
        break;

    case CLOSE:
        isError = closeCmd(lawicelCMD);
        break;

    case TX_STD:
        isError = stdTxCmd(lawicelCMD);
        break;

    case TX_EXT:
        isError = extTxCmd(lawicelCMD);
        break;

    case TX_STD_RTR:
        isError = stdRtrTxCmd(lawicelCMD);
        break;

    case TX_EXT_RTR:
        isError = extRtrTxCmd(lawicelCMD);
        break;

    case POLL_SINGLE:
        isError = singlePollCmd(lawicelCMD);
        break;

    case POLL_ALL:
        isError = allPollCmd(lawicelCMD);
        break;

    case POLL_AUTO:
        isError = toggleAutoPollCmd(lawicelCMD);
        break;

    case STATUS_FLAGS:
        isError = getFlagsCmd(lawicelCMD);
        break;

    case FILTER_MODE:
        isError = setFilterModeCmd(lawicelCMD);
        break;

    case ACN_REGISTER:
        isError = setACnCmd(lawicelCMD);
        break;

    case AMN_REGISTER:
        isError = setAMnCmd(lawicelCMD);
        break;

    case SERIAL_BAUDRATE:
        isError = setSerialBaudrateCmd(lawicelCMD);
        break;

    case VERSION:
        isError = getVersionCmd(lawicelCMD);
        break;

    case SERIAL_NUMBER:
        isError = getSerialNumberCmd(lawicelCMD);
        break;

    case TOGGLE_TIMESTAMP:
        isError = toggleTimeStampCmd(lawicelCMD);
        break;

    case AUTO_START:
        isError = toggleAutoStartCmd(lawicelCMD);
        break;

    default:
        isError = 1;
        break;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setBaudrateCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;

    uint32_t baudrate = 0;

    if (lawicelCMD.length() != 2)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
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
            isError = ERROR;
            break;

        }
    }

    if (isError == OK)
    {
        m_selectedNVM->save(INIT_CAN_BAUD, lawicelCMD);
        isError = m_selectedCAN->setBaudrate(baudrate);
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::setBTRCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;

    if (lawicelCMD.length() != 5)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
    }
    else
    {
        uint8_t BTR0 = 0;
        uint8_t BTR1 = 0;

        if (charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), BTR0) == 1)
        {
            isError = ERROR;
        }

        if (charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), BTR1) == 1)
        {
            isError = ERROR;
        }

        if (isError == OK)
        {
            isError = m_selectedCAN->setBTR(BTR0, BTR1);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::openNormalCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;

    if (lawicelCMD.length() > 1)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
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
    uint8_t isError = OK;

    if (lawicelCMD.length() > 1)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
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
    uint8_t isError = OK;

    if (lawicelCMD.length() > 1)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = ERROR;
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
    uint8_t isError = OK;
    CANInterface::Frame frame;
    uint8_t dlc = 0;
    if (charToInt(lawicelCMD.charAt(4), dlc) == true)
    {
        isError = ERROR;
    }

    uint32_t id = 0;
    if (IdDecode(0, lawicelCMD, id) == true)
    {
        isError = ERROR;
    }

    int frameposition = 0;

    frame.m_id = id;
    frame.m_dlc = dlc;

    if (lawicelCMD.length() != ((2 * dlc) + 5))
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = ERROR;
    }
    else
    {
        for (int bufferPosition = 5; bufferPosition < (dlc * 2 + 4); bufferPosition += 2, frameposition++)
        {
            uint8_t resultByte = 0;

            if (charToByte(lawicelCMD.charAt(bufferPosition), lawicelCMD.charAt(bufferPosition + 1), resultByte) == true)
            {
                isError = ERROR;
            }
            else
            {
                frame.m_data[frameposition] = resultByte;
            }
        }

        if (isError == OK)
        {
            isError = m_selectedCAN->send(frame);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::extTxCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;
    CANInterface::Frame frame;

    uint8_t dlc = 0;
    if (charToInt(lawicelCMD.charAt(9), dlc) == true)
    {
        isError = ERROR;
    }

    uint32_t id = 0;
    if (IdDecode(1, lawicelCMD, id) == true)
    {
        isError = ERROR;
    }

    int frameposition = 0;

    frame.m_id = id;
    frame.m_dlc = dlc;
    frame.m_extended = true;

    if (lawicelCMD.length() != ((2 * dlc) + 10))
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = ERROR;
    }
    else
    {
        for (int bufferPosition = 10; bufferPosition < (dlc * 2 + 9); bufferPosition += 2, frameposition++)
        {
            uint8_t resultByte = 0;
            if (charToByte(lawicelCMD.charAt(bufferPosition), lawicelCMD.charAt(bufferPosition + 1), resultByte) == true)
            {
                isError = ERROR;
            }
            else
            {
                frame.m_data[frameposition] = resultByte;
            }
        }

        if (isError == OK)
        {
            isError = m_selectedCAN->send(frame);
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::stdRtrTxCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;
    CANInterface::Frame frame;

    uint8_t dlc = 0;
    if (charToInt(lawicelCMD.charAt(4), dlc) == true)
    {
        isError = ERROR;
    }

    uint32_t id = 0;
    if (IdDecode(0, lawicelCMD, id) == true)
    {
        isError = ERROR;
    }

    frame.m_id = id;
    frame.m_dlc = dlc;
    frame.m_rtr = true;

    if (lawicelCMD.length() != 5)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = ERROR;
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
    uint8_t isError = OK;
    CANInterface::Frame frame;

    uint8_t dlc = 0;
    if (charToInt(lawicelCMD.charAt(9), dlc) == true)
    {
        isError = ERROR;
    }

    uint32_t id = 0;
    if (IdDecode(1, lawicelCMD, id) == true)
    {
        isError = ERROR;
    }

    frame.m_id = id;
    frame.m_dlc = dlc;
    frame.m_extended = true;
    frame.m_rtr = true;

    if (lawicelCMD.length() != 10)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        isError = ERROR;
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
    uint8_t isError = OK;

    if (lawicelCMD.length() > 1)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = ERROR;
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
            isError = END_OF_BUFFER; /**< it is no error, but marks the end of the message buffer */
        }
    }
    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::allPollCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;

    if (lawicelCMD.length() > 1)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = ERROR;
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
    uint8_t isError = OK;

    if (lawicelCMD.length() != 2)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
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
            isError = ERROR;
            break;
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::getFlagsCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;
    if (lawicelCMD.length() > 1)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = ERROR;
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
    uint8_t isError = OK;
    bool filterMode;
    if (lawicelCMD.length() != 2)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
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
            isError = ERROR;
            break;
        }

        if (isError == OK)
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
    uint8_t isError = OK;

    if (lawicelCMD.length() != 9)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
    }
    else
    {
        uint8_t ACn[4];

        if (charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), ACn[0]) == true)
        {
            isError = ERROR;
        }
        if (charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), ACn[1]) == true)
        {
            isError = ERROR;
        }
        if (charToByte(lawicelCMD.charAt(5), lawicelCMD.charAt(6), ACn[2]) == true)
        {
            isError = ERROR;
        }
        if (charToByte(lawicelCMD.charAt(7), lawicelCMD.charAt(8), ACn[3]) == true)
        {
            isError = ERROR;
        }

        if (isError == OK)
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
    uint8_t isError = OK;

    if (lawicelCMD.length() != 9)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
    }
    else
    {
        uint8_t AMn[4];

        if (charToByte(lawicelCMD.charAt(1), lawicelCMD.charAt(2), AMn[0]) == true)
        {
            isError = ERROR;
        }
        if (charToByte(lawicelCMD.charAt(3), lawicelCMD.charAt(4), AMn[1]) == true)
        {
            isError = ERROR;
        }
        if (charToByte(lawicelCMD.charAt(5), lawicelCMD.charAt(6), AMn[2]) == true)
        {
            isError = ERROR;
        }
        if (charToByte(lawicelCMD.charAt(7), lawicelCMD.charAt(8), AMn[3]) == true)
        {
            isError = ERROR;
        }

        if (isError == OK)
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
    uint8_t isError = OK;

    long _baudrate = 0;

    if (lawicelCMD.length() != 2)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
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
            isError = ERROR;
            break;
        
        }

        if (isError == OK)
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
    uint8_t isError = OK;

    if (lawicelCMD.length() > 1)
    {
        isError = ERROR;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::getSerialNumberCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;

    if (lawicelCMD.length() > 1)
    {
        isError = ERROR;
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::toggleTimeStampCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;

    if (lawicelCMD.length() != 2)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        isError = ERROR;
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
            isError = ERROR;
            break;
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::toggleAutoStartCmd(const String &lawicelCMD)
{
    uint8_t isError = OK;

    if (lawicelCMD.length() != 2)
    {
        isError = ERROR;
    }
    else if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = ERROR;
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
            isError = ERROR;
            break;
        }
    }

    return isError;
}

/**************************************************************************************************/
uint8_t Lawicel::autopoll()
{
    uint8_t isError = OK;

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        isError = ERROR;
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
            isError = END_OF_BUFFER; /**< it is no error, but marks the end of the message buffer */
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