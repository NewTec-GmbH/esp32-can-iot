#include <Lawicel.h>

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
Function: stdIdDecode(char B2, char B1, char B0)
Description: Translates char std ID int value
********************************************/
uint32_t Lawicel::IdDecode(bool extended)
{
    uint32_t result = 0;
    char _IdBuffer[8];

    uint8_t _IdLength = 3;

    if (extended)
    {
        _IdLength = 8;
        _IdBuffer[0] = this->buffer[8];
        _IdBuffer[1] = this->buffer[7];
        _IdBuffer[2] = this->buffer[6];
        _IdBuffer[3] = this->buffer[5];
        _IdBuffer[4] = this->buffer[4];
        _IdBuffer[5] = this->buffer[3];
        _IdBuffer[6] = this->buffer[2];
        _IdBuffer[7] = this->buffer[1];
    }
    else
    {
        _IdBuffer[0] = this->buffer[3];
        _IdBuffer[1] = this->buffer[2];
        _IdBuffer[2] = this->buffer[1];
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
Function: receiveCommand()
Description: Receives and Interprets Buffer with Serial Command
********************************************/

uint8_t Lawicel::receiveCommand()
{
    switch (this->buffer[0])
    {
    case SET_BAUDRATE:
    {
        return CMD_Set_Baudrate();
    }

    case SET_BTR:
    {
        return CMD_Set_BTR();
        ;
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
        Serial.println("Command not Recognized");
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
    CANCommand cmd;
    long _baudrate = 0;

    if (_length > 2)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (_length < 2)
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }

    switch (this->buffer[1])
    {
    case '0':
    {
        Serial.println("Bitrate 10Kbps set!");
        _baudrate = 10E3;
        break;
    }
    case '1':
    {
        Serial.println("Bitrate 20Kbps set!");
        _baudrate = 20E3;
        break;
    }
    case '2':
    {
        Serial.println("Bitrate 50Kbps set!");
        _baudrate = 50E3;
        break;
    }
    case '3':
    {
        Serial.println("Bitrate 100Kbps set!");
        _baudrate = 100E3;
        break;
    }
    case '4':
    {
        Serial.println("Bitrate 125Kbps set!");
        _baudrate = 125E3;
        break;
    }
    case '5':
    {
        Serial.println("Bitrate 250Kbps set!");
        _baudrate = 250E3;
        break;
    }
    case '6':
    {
        Serial.println("Bitrate 500Kbps set!");
        _baudrate = 500E3;
        break;
    }
    case '7':
    {
        Serial.println("Bitrate 800Kbps set!");
        _baudrate = 800E3;
        break;
    }
    case '8':
    {
        Serial.println("Bitrate 1 Mbps set!");
        _baudrate = 1000E3;
        break;
    }
    default:
    {
        Serial.println("Bitrate not recognized!");
        return 1;
    }
    }

    cmd.Baudrate = _baudrate;
    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(cmd);
        return 0;
    }
    return 1;
}

/*******************************************
Function: CMD_Set_BTR()
Description: Sets Baudrate through Registers
********************************************/

uint8_t Lawicel::CMD_Set_BTR()
{
    CANCommand cmd;

    if (this->_length > 5)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < 5)
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }

    cmd.BTR0 = charToByte(buffer[1], buffer[2]);
    cmd.BTR1 = charToByte(buffer[3], buffer[4]);

    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(cmd);
        return 0;
    }
    return 1;
}

/*******************************************
Function: CMD_Open_Normal()
Description: Opens CAN Channel in Normal Mode
********************************************/

uint8_t Lawicel::CMD_Open_Normal()
{
    CANCommand cmd;

    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is already Open");
        return 1;
    }

    cmd.State = NORMAL;
    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(cmd);
        return 0;
    }
    return 1;
}

/*******************************************
Function: CMD_Open_Listen_Only()
Description: Opens CAN Channel in Listen-Only Mode
********************************************/

uint8_t Lawicel::CMD_Open_Listen_Only()
{
    CANCommand cmd;
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is already Open");
        return 1;
    }

    cmd.State = LISTEN_ONLY;
    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(cmd);
        return 0;
    }
    return 1;
}

/*******************************************
Function: CMD_Close()
Description: Closes CAN Channel
********************************************/

uint8_t Lawicel::CMD_Close()
{
    CANCommand cmd;
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CLOSED)
    {
        Serial.println("Not Allowed! Channel is already Closed");
        return 1;
    }

    cmd.State = CLOSED;
    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(cmd);
        return 0;
    }
    return 1;
}

/*******************************************
Function: CMD_Tx_Std()
Description: Transmits standard CAN Frame (11-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Std()
{
    Frame frame;
    uint8_t _dlc = charToInt(buffer[4]);
    int32_t _id = IdDecode(0);
    int frameposition = 0;

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.Data = new uint8_t[_dlc];

    if (this->_length > ((2 * _dlc) + 5))
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < ((2 * _dlc) + 5))
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != NORMAL)
    {
        Serial.println("Not Allowed! Channel is not in Normal Mode");
        return 1;
    }

    for (int bufferPosition = 5; bufferPosition < (_dlc * 2 + 4); bufferPosition += 2, frameposition++)
    {
        frame.Data[frameposition] = (charToByte(buffer[bufferPosition], buffer[bufferPosition + 1]));
    }

    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(frame);
        return 0;
    }

    return 1;
}

/*******************************************
Function: CMD_Tx_Ext()
Description: Transmits extended CAN Frame (29-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Ext()
{
    Frame frame;
    uint8_t _dlc = charToInt(buffer[9]);
    int32_t _id = IdDecode(1);
    int frameposition = 0;

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.Extended = YES;
    frame.Data = new uint8_t[_dlc];

    if (this->_length > ((2 * _dlc) + 10))
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < ((2 * _dlc) + 10))
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != NORMAL)
    {
        Serial.println("Not Allowed! Channel is not in Normal Mode");
        return 1;
    }

    for (int bufferPosition = 10; bufferPosition < (_dlc * 2 + 9); bufferPosition += 2, frameposition++)
    {
        frame.Data[frameposition] = (charToByte(buffer[bufferPosition], buffer[bufferPosition + 1]));
    }

    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(frame);
        return 0;
    }
    return 1;
}

/*******************************************
Function: CMD_Tx_Std_RTR()
Description: Transmits standard RTR CAN Frame (11-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Std_RTR()
{
    Frame frame;
    uint8_t _dlc = charToInt(buffer[4]);
    int32_t _id = IdDecode(0);

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.RTR = YES;

    if (this->_length > ((2 * _dlc) + 5))
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < ((2 * _dlc) + 5))
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != NORMAL)
    {
        Serial.println("Not Allowed! Channel is not in Normal Mode");
        return 1;
    }

    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(frame);
        return 0;
    }

    return 1;
}

/*******************************************
Function: CMD_Tx_Ext_RTR()
Description: Transmits extended RTR CAN Frame (29-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Ext_RTR()
{
    Frame frame;
    uint8_t _dlc = charToInt(buffer[9]);
    int32_t _id = IdDecode(1);

    frame.ID = _id;
    frame.DLC = _dlc;
    frame.Extended = YES;
    frame.RTR = YES;

    if (this->_length > ((2 * _dlc) + 10))
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < ((2 * _dlc) + 10))
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != NORMAL)
    {
        Serial.println("Not Allowed! Channel is not in Normal Mode");
        return 1;
    }

    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(frame);
        return 0;
    }
    return 1;
}

/*******************************************
Function: CMD_Poll_Single()
Description: 
********************************************/

uint8_t Lawicel::CMD_Poll_Single()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    if (this->_length < 1)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CLOSED)
    {
        Serial.println("Not Allowed! Channel is Closed");
        return 1;
    }

    Serial.println("Function not Implemented");
    return 1;
}

/*******************************************
Function: CMD_Poll_All(); 
Description: Polls incomming FIFO for CAN frames (all pending frames)
********************************************/

uint8_t Lawicel::CMD_Poll_All()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    if (this->_length < 1)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CLOSED)
    {
        Serial.println("Not Allowed! Channel is Closed");
        return 1;
    }

    Serial.println("Function Not Implemented!");
    return 1;
}

/*******************************************
Function: CMD_Poll_Auto()
Description: Toggles Auto Poll for inconming Frames
********************************************/

uint8_t Lawicel::CMD_Poll_Auto()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    if (this->_length < 1)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CLOSED)
    {
        Serial.println("Not Allowed! Channel is Closed");
        return 1;
    }

    Serial.println("Function Not Implemented!");
    return 1;
}

/*******************************************
Function: CMD_Flags()
Description: Read Status Flags
********************************************/

uint8_t Lawicel::CMD_Flags()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    if (this->_length < 1)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CLOSED)
    {
        Serial.println("Not Allowed! Channel is Closed");
        return 1;
    }

    Serial.println("Function Not Implemented!");
    return 1;
}

/*******************************************
Function: CMD_Set_Filter_Mode()
Description: Sets Filter Mode 0 = Dual-Filter, 1 = Single-Filter
********************************************/

uint8_t Lawicel::CMD_Set_Filter_Mode()
{
    CANCommand cmd;

    if (this->_length > 2)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < 2)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }

    if (buffer[1] == '1')
    {
        cmd.FilterMode = true;
    }

    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(cmd);
        return 0;
    }

    return 0;
}

/*******************************************
Function: CMD_Set_ACn()
Description: Sets Acceptance Code Register
********************************************/

uint8_t Lawicel::CMD_Set_ACn()
{
    CANCommand cmd;

    if (this->_length > 9)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < 9)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }

    cmd.AC0 = charToByte(buffer[1], buffer[2]);
    cmd.AC1 = charToByte(buffer[3], buffer[4]);
    cmd.AC2 = charToByte(buffer[5], buffer[6]);
    cmd.AC3 = charToByte(buffer[7], buffer[8]);

    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(cmd);
        return 0;
    }

    return 1;
}

/*******************************************
Function: CMD_Set_AMn()
Description: Sets Acceptance Mask Register
********************************************/

uint8_t Lawicel::CMD_Set_AMn()
{
    CANCommand cmd;

    if (this->_length > 9)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < 9)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }

    cmd.AM0 = charToByte(buffer[1], buffer[2]);
    cmd.AM1 = charToByte(buffer[3], buffer[4]);
    cmd.AM2 = charToByte(buffer[5], buffer[6]);
    cmd.AM3 = charToByte(buffer[7], buffer[8]);

    if (m_selectedCAN != nullptr)
    {
        m_selectedCAN->send(cmd);
        return 0;
    }

    return 1;
}

/*******************************************
Function: CMD_Set_Serial_Baudrate()
Description: Sets UART Baudrate (and saves setting on EEPROM)
********************************************/

uint8_t Lawicel::CMD_Set_Serial_Baudrate()
{
    if (_length > 2)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (_length < 2)
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }

    Serial.println("Function Not Implemented!");
    return 1;
}

/*******************************************
Function: CMD_Version()
Description: Sends Hardware and Software Version
********************************************/

uint8_t Lawicel::CMD_Version()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    if (this->_length < 1)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }

    Serial.println("Function Not Implemented!");
    return 1;
}

/*******************************************
Function: CMD_Serial_Number()
Description: Sends Serial Number of Hardware
********************************************/

uint8_t Lawicel::CMD_Serial_Number()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    if (this->_length < 1)
    {
        Serial.println("Not Enough Arguments!");
        return 1;
    }
    
    Serial.println("Function Not Implemented!");
    return 1;
}

/*******************************************
Function: CMD_Activate_Timestamp()
Description: Toggles Timestamp (and saves setting on EEPROM)
********************************************/

uint8_t Lawicel::CMD_Timestamp()
{
    if (_length > 2)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (_length < 2)
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }
    
    Serial.println("Function Not Implemented!");
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
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (_length < 2)
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (m_selectedCAN->getChannelState() == CLOSED)
    {
        Serial.println("Not Allowed! Channel is Closed");
        return 1;
    }
    
    Serial.println("Function Not Implemented!");
    return 1;
}