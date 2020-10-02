#include <Lawicel.h>

/*******************************************
Function: readSerial()
Description: Read Serial input and calls receiveCommand()
********************************************/
uint8_t Lawicel::readSerial()
{
    memset(buffer, '0', 32);

    if (Serial.available())
    {
        int availableBytes = Serial.available() - 1;
        //Serial.println(availableBytes); //Prints the amount of symbols in Buffer

        int counter = 0;
        while (buffer[counter] != CR)
        {
            buffer[counter] = Serial.read();
            counter++;
        }
        Serial.println("");
        for (int i = 0; i < availableBytes; i++)
        {
            Serial.printf("%c", buffer[i]);
        }

        Serial.println("");

        _length = availableBytes;
        return this->receiveCommand();
    }
    else
    {
        return 0;
    }
}

/*******************************************
Function: getState()
Description: Returns State of the CAN Channel
********************************************/
uint8_t Lawicel::getState()
{
    switch (this->_channelState)
    {
    case CLOSED:
    {
        return 0;
    }
    case NORMAL:
    {
        return 1;
    }
    case LISTEN_ONLY:
    {
        return 2;
    }
    default:
        return -1;
    }
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
        return 0;
    }

    case TX_EXT_RTR:
    {
        return 0;
    }

    case POLL_SINGLE:
    {
        return 0;
    }

    case POLL_ALL:
    {
        return 0;
    }

    case POLL_AUTO:
    {
        return 0;
    }

    case STATUS_FLAGS:
    {
        return 0;
    }

    case FILTER_MODE:
    {
        return 0;
    }

    case ACN_REGISTER:
    {
        return 0;
    }

    case AMN_REGISTER:
    {
        return 0;
    }

    case SERIAL_BAUDRATE:
    {
        return 0;
    }

    case VERSION:
    {
        return 0;
    }

    case SERIAL_NUMBER:
    {
        return 0;
    }

    case SET_TIMESTAMP:
    {
        return 0;
    }

    case AUTO_START:
    {
        return 0;
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
    if (this->_length > 2)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }
    else if (this->_length < 2)
    {
        Serial.println("Not enough Arguments!");
        return 1;
    }

    if (_channelState != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }

    switch (this->buffer[1])
    {
    case '0':
    {
        Serial.println("Bitrate not supported!");
        return 1;
    }
    case '1':
    {
        Serial.println("Bitrate not supported!");
        return 1;
    }
    case '2':
    {
        Serial.println("Bitrate 50Kbps set!");
        _baudrate = 50E3;
        return 0;
    }
    case '3':
    {
        Serial.println("Bitrate 100Kbps set!");
        _baudrate = 100E3;
        return 0;
    }
    case '4':
    {
        Serial.println("Bitrate 125Kbps set!");
        _baudrate = 125E3;
        return 0;
    }
    case '5':
    {
        Serial.println("Bitrate 250Kbps set!");
        _baudrate = 250E3;
        return 0;
    }
    case '6':
    {
        Serial.println("Bitrate 500Kbps set!");
        _baudrate = 500E3;
        return 0;
    }
    case '7':
    {
        Serial.println("Bitrate not supported!");
        return 1;
    }
    case '8':
    {
        Serial.println("Bitrate 1 Mbps set!");
        _baudrate = 1000E3;
        return 0;
    }
    default:
    {
        Serial.println("Bitrate not recognized!");
        return 1;
    }
    }
}

/*******************************************
Function: CMD_Set_BTR()
Description: Sets Baudrate through Registers
********************************************/

uint8_t Lawicel::CMD_Set_BTR()
{
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

    if (_channelState != CLOSED)
    {
        Serial.println("Not Allowed! Channel is Open");
        return 1;
    }

    Serial.println("Function not yet implemented!");
    return 1;
}

/*******************************************
Function: CMD_Open_Normal()
Description: Opens CAN Channel in Normal Mode
********************************************/

uint8_t Lawicel::CMD_Open_Normal()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }

    switch (this->_channelState)
    {
    case CLOSED:
    {
        if (!SJA1000.begin(_baudrate))
        {
            Serial.println("Failed! Restarting...");
            delay(5000);
            ESP.restart();
            return 1;
        }
        else
        {
            Serial.println("CAN Channel opened in Normal Mode!");
            Serial.printf("Baudrate: %ld Kbps\n", _baudrate);
            this->_channelState = NORMAL;
            return 0;
        }
    }

    case NORMAL:
    {
        Serial.println("CAN Channel is ALREADY opened in NORMAL Mode");
        return 1;
    }

    case LISTEN_ONLY:
    {
        Serial.println("CAN Channel is ALREADY opened in LISTEN-ONLY Mode");
        return 1;
    }
    default:
        return 1;
    }
}

/*******************************************
Function: CMD_Open_Listen_Only()
Description: Opens CAN Channel in Listen-Only Mode
********************************************/

uint8_t Lawicel::CMD_Open_Listen_Only()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }

    switch (this->_channelState)
    {
    case CLOSED:
    {
        if (!SJA1000.begin(_baudrate))
        {
            Serial.println("Failed! Restarting...");
            delay(5000);
            ESP.restart();
            return 1;
        }
        else
        {
            Serial.println("CAN Channel opened in Listen-Only Mode!");
            Serial.printf("Baudrate: %ld Kbps\n", _baudrate);
            this->_channelState = LISTEN_ONLY;
            return 0;
        }
    }

    case NORMAL:
    {
        Serial.println("CAN Channel is ALREADY opened in NORMAL Mode");
        return 1;
    }

    case LISTEN_ONLY:
    {
        Serial.println("CAN Channel is ALREADY opened in LISTEN-ONLY Mode");
        return 1;
    }
    default:
        return 1;
    }
}

/*******************************************
Function: CMD_Close()
Description: Closes CAN Channel
********************************************/

uint8_t Lawicel::CMD_Close()
{
    if (this->_length > 1)
    {
        Serial.println("Too many Arguments!");
        return 1;
    }

    switch (this->_channelState)
    {
    case CLOSED:
    {
        Serial.println("CAN Channel is already CLOSED");
        return 1;
    }

    case NORMAL:
    {
        Serial.println("CAN Channel Closed");
        this->_channelState = CLOSED;
        SJA1000.end();
        return 0;
    }

    case LISTEN_ONLY:
    {
        Serial.println("CAN Channel Closed");
        this->_channelState = CLOSED;
        return 0;
    }
    default:
        return 1;
    }
}

/*******************************************
Function: CMD_Tx_Std()
Description: Transmits standard CAN Frame (11-bit ID)
********************************************/

uint8_t Lawicel::CMD_Tx_Std()
{
    uint8_t _dlc = charToInt(buffer[4]);

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

    if (_channelState == CLOSED)
    {
        Serial.println("Not Allowed! Channel is Closed");
        return 1;
    }
    else if (_channelState == LISTEN_ONLY)
    {
        Serial.println("Not Allowed! Channel is on Listen-only Mode");
        return 1;
    }

    int32_t _id = IdDecode(0);

    if (!SJA1000.beginPacket(_id))
    {
        return 1;
    }

    for (int bufferPosition = 5; bufferPosition < (_dlc * 2 + 4); bufferPosition += 2)
    {
        SJA1000.write(charToByte(buffer[bufferPosition], buffer[bufferPosition + 1]));
    }

    if (SJA1000.endPacket())
    {
        Serial.printf("Message Sent with Standard ID 0x%x and Data Bytes ", _id);
        for (int i = 0; i < _dlc; i ++)
        {
            Serial.printf("%c%c ",buffer[i+4],buffer[i+5]);
        }
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
    uint8_t _dlc = charToInt(buffer[9]);

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

    if (_channelState == CLOSED)
    {
        Serial.println("Not Allowed! Channel is Closed");
        return 1;
    }
    else if (_channelState == LISTEN_ONLY)
    {
        Serial.println("Not Allowed! Channel is on Listen-only Mode");
        return 1;
    }

    int32_t _id = IdDecode(1);

    if (!SJA1000.beginExtendedPacket(_id))
    {
        return 1;
    }

    for (int bufferPosition = 10; bufferPosition < (_dlc * 2 + 9); bufferPosition += 2)
    {
        SJA1000.write(charToByte(buffer[bufferPosition], buffer[bufferPosition + 1]));
    }

    if (SJA1000.endPacket())
    {
        Serial.printf("Message Sent with Extended ID 0x%x and Data Bytes ", _id);
        for (int i = 0; i < _dlc; i ++)
        {
            Serial.printf("%c%c ",buffer[i+10],buffer[i+11]);
        }
        return 0;
    }

    return 1;
}