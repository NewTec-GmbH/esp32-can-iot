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

        for (int i = 0; i < availableBytes; i++)
        {
            Serial.printf("%c", buffer[i]);
        }

        Serial.println("");
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
Function: charToByte(char MSB, char LSB)
Description: Translates char symbols into hex values
********************************************/

uint8_t Lawicel::charToByte(char MSB, char LSB)
{
    uint8_t result = 0;
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
        return 0;
    }

    case TX_STD:
    {
        return 0;
    }

    case TX_EXT:
    {
        return 0;
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

    switch (this ->_channelState)
    {
    case CLOSED:
    {
        Serial.println("CASE CLOSED");
        if (!SJA1000.begin(_baudrate))
        {
            Serial.println("Failed! Restarting...");
            delay(5000);
            ESP.restart();
            return 1;
        }
        else
        {
            Serial.println("CAN Ready!");
            this ->_channelState = NORMAL;
            return 0;
        }
    }

    case NORMAL:
    {
        Serial.println("CAN Channel is already OPEN in NORMAL Mode");
        return 1;
    }

    case LISTEN_ONLY:
    {
        Serial.println("CAN Channel is already OPEN in LISTEN-ONLY Mode");
        return 1;
    }
    default:
    Serial.println("Default");
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

    switch (this ->_channelState)
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
            Serial.println("CAN Ready!");
            this ->_channelState = LISTEN_ONLY;
            return 0;
        }
    }

    case NORMAL:
    {
        Serial.println("CAN Channel is already OPEN in NORMAL Mode");
        return 1;
    }

    case LISTEN_ONLY:
    {
        Serial.println("CAN Channel is already OPEN in LISTEN-ONLY Mode");
        return 1;
    }
    default:
        return -1;
    }
}