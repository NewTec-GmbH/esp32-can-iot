#include <Lawicel.h>

/*******************************************
Function: begin()
Description: Initialize Protocol
********************************************/
void Lawicel::begin()
{
    String var;
    uint32_t val;

    m_selectedNVM->begin();

    var = m_selectedNVM->readString(INIT_SERIAL_BAUD);
    strcpy(buffer, var.c_str());
    receiveCommand();

    m_selectedSerial->begin();

    val = m_selectedNVM->read(INIT_TIMESTAMP);
    _timestamp = val;

    _autostart = m_selectedNVM->read(INIT_AUTO_START);

    if (_autostart != 0)
    {
        autoPolling = true;

        var = m_selectedNVM->readString(INIT_CAN_BAUD);
        strcpy(buffer, var.c_str());
        receiveCommand();

        var = m_selectedNVM->readString(INIT_FILTER_MODE);
        strcpy(buffer, var.c_str());
        receiveCommand();

        var = m_selectedNVM->readString(INIT_FILTER_ACN);
        strcpy(buffer, var.c_str());
        receiveCommand();

        var = m_selectedNVM->readString(INIT_FILTER_AMN);
        strcpy(buffer, var.c_str());
        receiveCommand();
    }

    if (_autostart == 1)
    {
        var = "O";
        strcpy(buffer, var.c_str());
        receiveCommand();
    }
    else if (_autostart == 2)
    {
        var = "L";
        strcpy(buffer, var.c_str());
        receiveCommand();
    }

    m_selectedSerial->print("System initated Correctly");
}

/*******************************************
Function: end()
Description: Terminate Protocol
********************************************/
void Lawicel::end()
{
}

/*******************************************
Function: charToByte(char MSB, char LSB)
Description: Translates char symbols into hex byte
********************************************/

uint8_t Lawicel::charToByte(char MSB, char LSB)
{
    uint8_t result = -10;
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

/*******************************************
Function: charToInt(char symbol)
Description: Translates char symbols of numbers into int values
********************************************/
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

/*******************************************
Function: IdDecode(bool extended)
Description: Translates char ID into value
********************************************/
uint32_t Lawicel::IdDecode(bool extended)
{
    uint32_t result = 0;
    char _IdBuffer[8];

    uint8_t _IdLength = 3;

    if (extended)
    {
        _IdLength = 8;
        _IdBuffer[0] = buffer[8];
        _IdBuffer[1] = buffer[7];
        _IdBuffer[2] = buffer[6];
        _IdBuffer[3] = buffer[5];
        _IdBuffer[4] = buffer[4];
        _IdBuffer[5] = buffer[3];
        _IdBuffer[6] = buffer[2];
        _IdBuffer[7] = buffer[1];
    }
    else
    {
        _IdBuffer[0] = buffer[3];
        _IdBuffer[1] = buffer[2];
        _IdBuffer[2] = buffer[1];
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

/*******************************************
Function: getTimestamp()
Description: Returns Timestamp
********************************************/
int Lawicel::getTimestamp()
{
    return millis() % MAX_TIMESTAMP;
}

/*******************************************
Function: receiveCommand()
Description: Receives and Interprets Buffer with Serial Command
********************************************/
uint8_t Lawicel::receiveCommand()
{
    m_selectedSerial->print(buffer[0]);
    switch (buffer[0])
    {
    case SET_BAUDRATE:
    {
        m_selectedSerial->print("Command Set Baudrate");
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

/*******************************************
Function: CMD_Set_Baudrate()
Description: Sets Baudrate through presets
********************************************/

uint8_t Lawicel::CMD_Set_Baudrate()
{
    long _baudrate = 0;

    m_selectedSerial->print(_length);

    if (_length > 2)
    {
        return 1;
    }
    else if (_length < 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    m_selectedSerial->print(buffer[1]);
    switch (buffer[1])
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
    m_selectedSerial->print((int)_baudrate);

    m_selectedNVM->saveString(INIT_CAN_BAUD, buffer);

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->setBaudrate(_baudrate);
    }

    return 1;
}

/*******************************************
Function: CMD_Set_BTR()
Description: Sets Baudrate through Registers
********************************************/

uint8_t Lawicel::CMD_Set_BTR()
{
    if (_length > 5)
    {
        return 1;
    }
    else if (_length < 5)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t BTR0 = charToByte(buffer[1], buffer[2]);
    uint8_t BTR1 = charToByte(buffer[3], buffer[4]);

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->setBTR(BTR0, BTR1);
    }

    return 1;
}

/*******************************************
Function: CMD_Open_Normal()
Description: Opens CAN Channel in Normal Mode
********************************************/

uint8_t Lawicel::CMD_Open_Normal()
{
    if (_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    CANInterface::BUS_STATE state = CANInterface::NORMAL;
    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->setState(state);
    }

    return 1;
}

/*******************************************
Function: CMD_Open_Listen_Only()
Description: Opens CAN Channel in Listen-Only Mode
********************************************/

uint8_t Lawicel::CMD_Open_Listen_Only()
{
    if (_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    CANInterface::BUS_STATE state = CANInterface::LISTEN_ONLY;
    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->setState(state);
    }

    return 1;
}

/*******************************************
Function: CMD_Close()
Description: Closes CAN Channel
********************************************/

uint8_t Lawicel::CMD_Close()
{
    if (_length > 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    CANInterface::BUS_STATE state = CANInterface::CLOSED;
    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->setState(state);
    }

    return 1;
}

/*******************************************
Function: CMD_Tx_Std()
Description: Transmits standard CAN Frame (11-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Std()
{
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(buffer[4]);
    int32_t _id = IdDecode(0);
    int frameposition = 0;

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.Data = new uint8_t[_dlc];

    if (_length > ((2 * _dlc) + 5))
    {
        return 1;
    }
    else if (_length < ((2 * _dlc) + 5))
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        return 1;
    }

    for (int bufferPosition = 5; bufferPosition < (_dlc * 2 + 4); bufferPosition += 2, frameposition++)
    {
        frame.Data[frameposition] = (charToByte(buffer[bufferPosition], buffer[bufferPosition + 1]));
    }

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->send(frame);
    }

    return 1;
}

/*******************************************
Function: CMD_Tx_Ext()
Description: Transmits extended CAN Frame (29-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Ext()
{
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(buffer[9]);
    int32_t _id = IdDecode(1);
    int frameposition = 0;

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.Extended = true;
    frame.Data = new uint8_t[_dlc];

    if (_length > ((2 * _dlc) + 10))
    {
        return 1;
    }
    else if (_length < ((2 * _dlc) + 10))
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        return 1;
    }

    for (int bufferPosition = 10; bufferPosition < (_dlc * 2 + 9); bufferPosition += 2, frameposition++)
    {
        frame.Data[frameposition] = (charToByte(buffer[bufferPosition], buffer[bufferPosition + 1]));
    }

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->send(frame);
    }

    return 1;
}

/*******************************************
Function: CMD_Tx_Std_RTR()
Description: Transmits standard RTR CAN Frame (11-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Std_RTR()
{
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(buffer[4]);
    int32_t _id = IdDecode(0);

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.RTR = true;

    if (_length > ((2 * _dlc) + 5))
    {
        return 1;
    }
    else if (_length < ((2 * _dlc) + 5))
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        return 1;
    }

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->send(frame);
    }

    return 1;
}

/*******************************************
Function: CMD_Tx_Ext_RTR()
Description: Transmits extended RTR CAN Frame (29-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Ext_RTR()
{
    CANInterface::Frame frame;
    uint8_t _dlc = charToInt(buffer[9]);
    int32_t _id = IdDecode(1);

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.Extended = true;
    frame.RTR = true;

    if (_length > ((2 * _dlc) + 10))
    {
        return 1;
    }
    else if (_length < ((2 * _dlc) + 10))
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::NORMAL)
    {
        return 1;
    }

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->send(frame);
    }
    return 1;
}

/*******************************************
Function: CMD_Poll_Single()
Description: 
********************************************/

uint8_t Lawicel::CMD_Poll_Single()
{
    char *str = nullptr;
    char cmd = 't';
    CANInterface::Frame *frame = nullptr;

    if (_length > 1)
    {
        return 1;
    }
    if (_length < 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    if (m_selectedCAN->pollSingle(frame))
    {
        sprintf(str, "%c", BELL);
        m_selectedSerial->send(str);
        return 0;
    }

    if (frame->Extended == true && frame->RTR == false)
    {
        cmd = 'T';
    }
    else if (frame->Extended == false && frame->RTR == true)
    {
        cmd = 'r';
    }
    else if (frame->Extended == true && frame->RTR == true)
    {
        cmd = 'R';
    }

    int _dlc = frame->DLC;

    sprintf(str, "%c%X%d", cmd, frame->ID, frame->DLC);
    for (int i = 0; i < _dlc; i++)
    {
        sprintf(str, "%02X", frame->Data[i]);
    }

    if (_timestamp)
    {
        sprintf(str, "%04X", getTimestamp());
    }

    sprintf(str, "%c", CR);

    if (m_selectedSerial != nullptr)
    {
        m_selectedSerial->send(str);
        return 0;
    }

    return 1;
}

/*******************************************
Function: CMD_Poll_All(); 
Description: Polls incomming FIFO for CAN frames (all pending frames)
********************************************/

uint8_t Lawicel::CMD_Poll_All()
{

    CANInterface::Frame *frame = nullptr;

    if (_length > 1)
    {
        return 1;
    }
    if (_length < 1)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    int toRead = m_selectedCAN->pollAll(frame);

    if (toRead == 0)
    {
        char *str = nullptr;
        sprintf(str, "A%c", BELL);
        m_selectedSerial->send(str);
        return 0;
    }

    for (int i = 0; i < toRead; i++)
    {
        char *str = nullptr;
        char cmd = 't';
        if (frame[i].Extended == true && frame[i].RTR == false)
        {
            cmd = 'T';
        }
        else if (frame[i].Extended == false && frame[i].RTR == true)
        {
            cmd = 'r';
        }
        else if (frame[i].Extended == true && frame[i].RTR == true)
        {
            cmd = 'R';
        }

        int _dlc = frame[i].DLC;

        sprintf(str, "%c%X%d", cmd, frame[i].ID, frame[i].DLC);
        for (int j = 0; j < _dlc; j++)
        {
            sprintf(str, "%02X", frame[i].Data[j]);
        }

        if (_timestamp)
        {
            sprintf(str, "%04X", getTimestamp());
        }

        sprintf(str, "%c", CR);

        if (m_selectedSerial != nullptr)
        {
            m_selectedSerial->send(str);
        }
    }

    char *str = nullptr;
    sprintf(str, "A%c", BELL);
    m_selectedSerial->send(str);
    return 0;
}

/*******************************************
Function: CMD_Poll_Auto()
Description: Toggles Auto Poll for inconming Frames
********************************************/

uint8_t Lawicel::CMD_Poll_Auto()
{
    autoPolling = !autoPolling;
    return 0;
}

/*******************************************
Function: CMD_Flags()
Description: Read Status Flags
********************************************/

uint8_t Lawicel::CMD_Flags()
{
    char *str = nullptr;
    if (_length > 1)
    {
        return 1;
    }
    if (_length < 1)
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

    sprintf(str, "F%X%c", statusCode, CR);

    if (m_selectedSerial != nullptr)
    {
        m_selectedSerial->send(str);
    }

    return 1;
}

/*******************************************
Function: CMD_Set_Filter_Mode()
Description: Sets Filter Mode 0 = Dual-Filter, 1 = Single-Filter
********************************************/

uint8_t Lawicel::CMD_Set_Filter_Mode()
{
    if (_length > 2)
    {
        return 1;
    }
    else if (_length < 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }
    bool filterMode = false;
    if (buffer[1] == '1')
    {
        filterMode = true;
    }

    m_selectedNVM->saveString(INIT_FILTER_MODE, buffer);

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->setFilterMode(filterMode);
    }

    return 1;
}

/*******************************************
Function: CMD_Set_ACn()
Description: Sets Acceptance Code Register
********************************************/

uint8_t Lawicel::CMD_Set_ACn()
{
    if (_length > 9)
    {
        return 1;
    }
    else if (_length < 9)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t ACn[4];

    ACn[0] = charToByte(buffer[1], buffer[2]);
    ACn[1] = charToByte(buffer[3], buffer[4]);
    ACn[2] = charToByte(buffer[5], buffer[6]);
    ACn[3] = charToByte(buffer[7], buffer[8]);

    m_selectedNVM->saveString(INIT_FILTER_ACN, buffer);

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->setACn(ACn);
    }

    return 1;
}

/*******************************************
Function: CMD_Set_AMn()
Description: Sets Acceptance Mask Register
********************************************/

uint8_t Lawicel::CMD_Set_AMn()
{
    if (_length > 9)
    {
        return 1;
    }
    else if (_length < 9)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t AMn[4];

    AMn[0] = charToByte(buffer[1], buffer[2]);
    AMn[1] = charToByte(buffer[3], buffer[4]);
    AMn[2] = charToByte(buffer[5], buffer[6]);
    AMn[3] = charToByte(buffer[7], buffer[8]);

    m_selectedNVM->saveString(INIT_FILTER_AMN, buffer);

    if (m_selectedCAN != nullptr)
    {
        return m_selectedCAN->setAMn(AMn);
    }

    return 1;
}

/*******************************************
Function: CMD_Set_Serial_Baudrate()
Description: Sets UART Baudrate (and saves setting on EEPROM)
********************************************/

uint8_t Lawicel::CMD_Set_Serial_Baudrate()
{
    long _baudrate = 0;

    if (_length > 2)
    {
        return 1;
    }
    else if (_length < 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    switch (buffer[1])
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

    m_selectedNVM->saveString(INIT_SERIAL_BAUD, buffer);

    if (m_selectedSerial != nullptr)
    {
        m_selectedSerial->setBaudrate(_baudrate);
        return 0;
    }

    return 1;
}

/*******************************************
Function: CMD_Version()
Description: Sends Hardware and Software Version
********************************************/

uint8_t Lawicel::CMD_Version()
{
    if (_length > 1)
    {
        return 1;
    }
    if (_length < 1)
    {
        return 1;
    }

    return 0;
}

/*******************************************
Function: CMD_Serial_Number()
Description: Sends Serial Number of Hardware
********************************************/

uint8_t Lawicel::CMD_Serial_Number()
{
    if (_length > 1)
    {
        return 1;
    }
    if (_length < 1)
    {
        return 1;
    }

    return 0;
}

/*******************************************
Function: CMD_Activate_Timestamp()
Description: Toggles Timestamp (and saves setting on EEPROM)
********************************************/

uint8_t Lawicel::CMD_Timestamp()
{
    if (_length > 2)
    {
        return 1;
    }
    else if (_length < 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CANInterface::CLOSED)
    {
        return 1;
    }

    uint8_t var = charToInt(buffer[1]);

    m_selectedNVM->save(INIT_TIMESTAMP, var);

    if (var == 0)
    {
        _timestamp = false;
        return 0;
    }
    else if (var == 1)
    {
        _timestamp = true;
        return 0;
    }

    return 1;
}

/*******************************************
Function: CMD_Auto_Start()
Description: Auto Startup feature (from power on)
********************************************/

uint8_t Lawicel::CMD_Auto_Start()
{
    if (_length > 2)
    {
        return 1;
    }
    else if (_length < 2)
    {
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    int var = charToInt(buffer[1]);

    if (var <= 2)
    {
        _autostart = var;
        m_selectedNVM->save(INIT_AUTO_START, var);
        return 0;
    }

    return 1;
}

/*******************************************
Function: Handler(uint8_t CMD)
Description: Handles the Serial Messages
********************************************/

bool Lawicel::handler()
{
    char str[100];

    if (m_selectedCAN == nullptr)
    {
        return false;
    }

    if (m_selectedSerial == nullptr)
    {
        return false;
    }

    _length = m_selectedSerial->read(buffer);

    if (_length == 0)
    {
        return true;
    }

    uint8_t CMD_status = receiveCommand();

    if (CMD_status == 1)
    {
        sprintf(str, "%c", BELL);
        return true;
    }
    else if (CMD_status != 0)
    {
        return false;
    }

    if (buffer[0] == POLL_SINGLE || buffer[0] == POLL_ALL || buffer[0] == POLL_AUTO)
    {
        return true;
    }
    else if (buffer[0] == VERSION)
    {
        sprintf(str, "%s", X_VERSION);
    }
    else if (buffer[0] == SERIAL_NUMBER)
    {
        sprintf(str, "%s", X_SERIAL_NUMBER);
    }

    sprintf(str, "%c", CR);

    m_selectedSerial->send(str);

    if (autoPolling)
    {
        Autopoll();
    }

    return true;
}

/*******************************************
Function: Autopoll()
Description: Frame Polling without any extra tags
********************************************/

uint8_t Lawicel::Autopoll()
{
    CANInterface::Frame *frame = nullptr;

    if (m_selectedCAN->getChannelState() == CANInterface::CLOSED)
    {
        return 1;
    }

    int toRead = m_selectedCAN->pollAll(frame);

    if (toRead == 0)
    {
        return 0;
    }

    for (int i = 0; i < toRead; i++)
    {
        char str[100];
        char cmd = 't';
        if (frame[i].Extended == true && frame[i].RTR == false)
        {
            cmd = 'T';
        }
        else if (frame[i].Extended == false && frame[i].RTR == true)
        {
            cmd = 'r';
        }
        else if (frame[i].Extended == true && frame[i].RTR == true)
        {
            cmd = 'R';
        }

        int _dlc = frame[i].DLC;

        sprintf(str, "%c%X%d", cmd, frame[i].ID, frame[i].DLC);
        for (int j = 0; j < _dlc; j++)
        {
            sprintf(str, "%02X", frame[i].Data[j]);
        }

        if (_timestamp)
        {
            sprintf(str, "%04X", getTimestamp());
        }

        sprintf(str, "%c", CR);

        if (m_selectedSerial != nullptr)
        {
            m_selectedSerial->send(str);
        }
    }

    return 0;
}
