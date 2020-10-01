#include <Lawicel.h>

/*******************************************
Function: readSerial()
Description: Read Serial input and calls receiveCommand()
********************************************/
void Lawicel::readSerial()
{
    memset(buffer, '0', 32);

    if (Serial.available())
    {
        int availableBytes = Serial.available();
        //        Serial.println(availableBytes);   //Prints the amount of symbols in Buffer
        for (int i = 0; i < availableBytes; i++)
        {
            buffer[i] = Serial.read();
            buffer[i + 1] = '\n';
        }
        for (int i = 0; i < availableBytes; i++)
        {
            Serial.printf("%c", buffer[i]);
        }
        Serial.println("");

        this->receiveCommand(buffer, availableBytes);

        Serial.println("");
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
Function: receiveCommand(const char buffer[], const int length)
Description: Receives and Interprets Buffer with Serial Command
********************************************/

uint8_t Lawicel::receiveCommand(const char buffer[], const int length)
{
    switch (buffer[0])
    {
    case SET_BAUDRATE:
    {
        return 0;
    }

    case SET_BTR:
    {
        return 0;
    }

    case OPEN_NORMAL:
    {
        return 0;
    }

    case OPEN_LISTEN_ONLY:
    {
        return 0;
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
Function: getOpen()
Description: Opens CAN Channel
********************************************/

void Lawicel::getOpen()
{
    if (!SJA1000.begin(_baudrate))
    {
        Serial.println("Failed! Restarting...");
        delay(5000);
        ESP.restart();
    }
    else
    {
        Serial.println("CAN Ready!");
    }
}