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
bool Lawicel::handler()
{
    m_serialReturn = "";

    if (m_autoPolling)
    {
        if (Autopoll() == 0)
        {
            m_selectedSerial->print(m_serialReturn);
        }
    }

    m_serialReturn = "";

    m_serialInput = m_selectedSerial->read();
    m_length = m_serialInput.length();

    if (m_length == 0)
    {
        return true;
    }

    uint8_t CMD_status = receiveCommand();

    if (m_serialInput.charAt(0) == POLL_SINGLE && CMD_status == 2)
    {
        CMD_status = 0;
    }

    if (CMD_status > 0)
    {
        m_serialReturn += (char)BELL;
        m_selectedSerial->print(m_serialReturn);
        return false;
    }

    if (m_serialInput.charAt(0) == VERSION)
    {
        m_serialReturn += X_VERSION;
    }
    else if (m_serialInput.charAt(0) == SERIAL_NUMBER)
    {
        m_serialReturn += X_SERIAL_NUMBER;
    }

    m_serialReturn += (char)CR;

    m_selectedSerial->print(m_serialReturn);

    return true;
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

    m_autostart = m_selectedNVM->readInt(INIT_AUTO_START);

    if (m_autostart > 0)
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

    if (m_autostart == 1)
    {
        m_serialInput = "O";
        receiveCommand();
    }
    else if (m_autostart == 2)
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
    if (num_symbol < 48 || num_symbol > 57)
    {
        return -10;
    }

    result = num_symbol;
    result -= 48;

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
    m_length = m_serialInput.length();
    switch (m_serialInput.charAt(0))
    {
    case SET_BAUDRATE:
    {
        return CMD_Set_Baudrate();
    }

    case SET_BTR:
    {
        return CMD_Set_BTR();
    }

    case OPEN_NORMAL:
    {
        return CMD_Open_Normal();
    }

    case OPEN_LISTEN_ONLY:
    {
        return CMD_Open_Listen_Only();
    }

    case CLOSE:
    {
        return CMD_Close();
    }

    case TX_STD:
    {
        return CMD_Tx_Std();
    }

    case TX_EXT:
    {
        return CMD_Tx_Ext();
    }

    case TX_STD_RTR:
    {
        return CMD_Tx_Std_RTR();
    }

    case TX_EXT_RTR:
    {
        return CMD_Tx_Ext_RTR();
    }

    case POLL_SINGLE:
    {
        return CMD_Poll_Single();
    }

    case POLL_ALL:
    {
        return CMD_Poll_All();
    }

    case POLL_AUTO:
    {
        return CMD_Poll_Auto();
    }

    case STATUS_FLAGS:
    {
        return CMD_Flags();
    }

    case FILTER_MODE:
    {
        return CMD_Set_Filter_Mode();
    }

    case ACN_REGISTER:
    {
        return CMD_Set_ACn();
    }

    case AMN_REGISTER:
    {
        return CMD_Set_AMn();
    }

    case SERIAL_BAUDRATE:
    {
        return CMD_Set_Serial_Baudrate();
    }

    case VERSION:
    {
        return CMD_Version();
    }

    case SERIAL_NUMBER:
    {
        return CMD_Serial_Number();
    }

    case TOGGLE_TIMESTAMP:
    {
        return CMD_Timestamp();
    }

    case AUTO_START:
    {
        return CMD_Auto_Start();
    }

    default:
    {
        return 1;
    }
    }
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Set_Baudrate()
{
    long _baudrate = 0;

    if (m_length != 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

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
        return 1;
    }
    }

    m_selectedNVM->saveString(INIT_CAN_BAUD, m_serialInput);

    return m_selectedCAN->setBaudrate(_baudrate);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Set_BTR()
{
    if (m_length != 5)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t BTR0 = charToByte(m_serialInput.charAt(1), m_serialInput.charAt(2));
    uint8_t BTR1 = charToByte(m_serialInput.charAt(3), m_serialInput.charAt(4));

    return m_selectedCAN->setBTR(BTR0, BTR1);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Open_Normal()
{
    if (m_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    return m_selectedCAN->setState(CANInterface::NORMAL);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Open_Listen_Only()
{
    if (m_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    return m_selectedCAN->setState(CANInterface::LISTEN_ONLY);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Close()
{
    if (m_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    return m_selectedCAN->setState(CANInterface::CLOSED);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Tx_Std()
{
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(m_serialInput.charAt(4));
    int32_t _id = IdDecode(0);
    int frameposition = 0;

    frame.ID = _id;
    frame.DLC = _dlc;

    if (m_length != ((2 * _dlc) + 5))
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        return 1;
    }

    for (int bufferPosition = 5; bufferPosition < (_dlc * 2 + 4); bufferPosition += 2, frameposition++)
    {
        frame.Data[frameposition] = (charToByte(m_serialInput.charAt(bufferPosition), m_serialInput.charAt(bufferPosition + 1)));
    }

    return m_selectedCAN->send(frame);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Tx_Ext()
{
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(m_serialInput.charAt(9));
    int32_t _id = IdDecode(1);
    int frameposition = 0;

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.Extended = true;

    if (m_length != ((2 * _dlc) + 10))
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        return 1;
    }

    for (int bufferPosition = 10; bufferPosition < (_dlc * 2 + 9); bufferPosition += 2, frameposition++)
    {
        frame.Data[frameposition] = (charToByte(m_serialInput.charAt(bufferPosition), m_serialInput.charAt(bufferPosition + 1)));
    }

    return m_selectedCAN->send(frame);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Tx_Std_RTR()
{
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(m_serialInput.charAt(4));
    int32_t _id = IdDecode(0);

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.RTR = true;

    if (m_length != 5)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        return 1;
    }

    return m_selectedCAN->send(frame);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Tx_Ext_RTR()
{
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(m_serialInput.charAt(9));
    int32_t _id = IdDecode(1);

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.Extended = true;
    frame.RTR = true;

    if (m_length != 10)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        return 1;
    }

    return m_selectedCAN->send(frame);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Poll_Single()
{
    if (m_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    CANInterface::Frame frame = m_selectedCAN->pollSingle();

    if (frame.ID == 0xFFF)
    {
        return 2;
    }

    char cmd = 't';
    int _id_length = 3;
    if (frame.Extended == true && frame.RTR == false)
    {
        cmd = 'T';
        _id_length = 8;
    }
    else if (frame.Extended == false && frame.RTR == true)
    {
        cmd = 'r';
    }
    else if (frame.Extended == true && frame.RTR == true)
    {
        cmd = 'R';
        _id_length = 8;
    }

    m_serialReturn += cmd;

    String _ID = String(frame.ID, HEX);
    for (int i = 0; i < _id_length - _ID.length(); i++)
    {
        m_serialReturn += '0';
    }
    m_serialReturn += _ID;

    m_serialReturn += frame.DLC;

    if (frame.RTR == false)
    {
        for (int i = 0; i < frame.DLC; i++)
        {
            m_serialReturn += String(frame.Data[i], HEX);
        }
    }

    if (m_timestamp)
    {
        m_serialReturn += String(getTimestamp(), HEX);
    }

    return 0;
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Poll_All()
{
    if (m_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    while (CMD_Poll_Single() == 0)
    {
        m_selectedSerial->print(m_serialReturn);
        m_serialReturn = "";
    }

    m_serialReturn += 'A';

    return 0;
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Poll_Auto()
{
    if (m_length != 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    if (m_serialInput.charAt(1) == '0')
    {
        m_autoPolling = false;
        return 0;
    }
    else if (m_serialInput.charAt(1) == '1')
    {
        m_autoPolling = true;
        return 0;
    }

    return 1;
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Flags()
{
    if (m_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    bool flags[8] = {};
    if (m_selectedCAN->getStatusFlags(flags) == 1)
    {
        return 1;
    }

    uint8_t statusCode = 0;

    for (int position = 0; position < 8; position++)
    {
        statusCode += flags[position] * pow(16.0, position);
    }

    return 1;
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Set_Filter_Mode()
{
    if (m_length != 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    bool filterMode;

    if (m_serialInput.charAt(1) == '1')
    {
        filterMode = true;
    }
    else if (m_serialInput.charAt(1) == '0')
    {
        filterMode = false;
    }
    else
    {
        return 1;
    }

    m_selectedNVM->saveString(INIT_FILTER_MODE, m_serialInput);

    return m_selectedCAN->setFilterMode(filterMode);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Set_ACn()
{
    if (m_length != 9)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t ACn[4];

    ACn[0] = charToByte(m_serialInput.charAt(1), m_serialInput.charAt(2));
    ACn[1] = charToByte(m_serialInput.charAt(3), m_serialInput.charAt(4));
    ACn[2] = charToByte(m_serialInput.charAt(5), m_serialInput.charAt(6));
    ACn[3] = charToByte(m_serialInput.charAt(7), m_serialInput.charAt(8));

    m_selectedNVM->saveString(INIT_FILTER_ACN, m_serialInput);

    return m_selectedCAN->setACn(ACn);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Set_AMn()
{
    if (m_length != 9)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t AMn[4];

    AMn[0] = charToByte(m_serialInput.charAt(1), m_serialInput.charAt(2));
    AMn[1] = charToByte(m_serialInput.charAt(3), m_serialInput.charAt(4));
    AMn[2] = charToByte(m_serialInput.charAt(5), m_serialInput.charAt(6));
    AMn[3] = charToByte(m_serialInput.charAt(7), m_serialInput.charAt(8));

    m_selectedNVM->saveString(INIT_FILTER_AMN, m_serialInput);

    return m_selectedCAN->setAMn(AMn);
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Set_Serial_Baudrate()
{
    long _baudrate = 0;

    if (m_length != 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

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
        return 1;
    }
    }

    m_selectedNVM->saveString(INIT_SERIAL_BAUD, m_serialInput);

    m_selectedSerial->setBaudrate(_baudrate);

    return 0;
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Version()
{
    if (m_length > 1)
    {
        return 1;
    }

    return 0;
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Serial_Number()
{
    if (m_length > 1)
    {
        return 1;
    }

    return 0;
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Timestamp()
{
    if (m_length != 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t var = charToInt(m_serialInput.charAt(1));

    if (var <= 1)
    {
        m_timestamp = var;
        m_selectedNVM->saveInt(INIT_TIMESTAMP, var);
        return 0;
    }

    return 1;
}

/**************************************************************************************************/
uint8_t Lawicel::CMD_Auto_Start()
{
    if (m_length != 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t var = charToInt(m_serialInput.charAt(1));

    if (var <= 2)
    {
        m_autostart = var;
        m_selectedNVM->saveInt(INIT_AUTO_START, var);
        return 0;
    }

    return 1;
}

/**************************************************************************************************/
uint8_t Lawicel::Autopoll()
{
    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }
    else
    {
        CANInterface::Frame frame = m_selectedCAN->pollSingle();

        if (frame.ID == 0xFFF)
        {
            return 1;
        }

        char cmd = 't';
        int _id_length = 3;
        if (frame.Extended == true && frame.RTR == false)
        {
            cmd = 'T';
            _id_length = 8;
        }
        else if (frame.Extended == false && frame.RTR == true)
        {
            cmd = 'r';
        }
        else if (frame.Extended == true && frame.RTR == true)
        {
            cmd = 'R';
            _id_length = 8;
        }

        m_serialReturn += cmd;

        String _ID = String(frame.ID, HEX);
        for (int i = 0; i < _id_length - _ID.length(); i++)
        {
            m_serialReturn += '0';
        }
        m_serialReturn += _ID;

        m_serialReturn += frame.DLC;

        if (frame.RTR == false)
        {
            for (int i = 0; i < frame.DLC; i++)
            {
                m_serialReturn += String(frame.Data[i], HEX);
            }
        }

        if (m_timestamp)
        {
            m_serialReturn += String(getTimestamp(), HEX);
        }
        return 0;
    }
}

/**************************************************************************************************/
uint32_t Lawicel::getTimestamp()
{
    return millis() % MAX_TIMESTAMP;
}

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/