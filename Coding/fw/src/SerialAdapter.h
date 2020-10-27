/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Adapters
@{
@file       SerialAdapter.h

ESP32 Serial Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef SERIAL_ADAPTER_H
#define SERIAL_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include <Serialinterface.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
*  ESP-32 Adapter as implementation of SerialInterface for the Lawicel Protocol.
*/
class SerialAdapter : public SerialInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
    *  Default constructor creates instance of the class using default values.
    * @param m_baudrate     Sets the Default baudrate to the Serial Channel.
    */
    SerialAdapter() : SerialInterface(), m_baudrate(115200)
    {
    }

    /**
    * Default destructor deletes instance of the class.
    */
    ~SerialAdapter()
    {
    }

    /**
    * Configures and starts the Serial Controller to use the user values.
    * @return 0 for OK, 1 for Error
    */
    uint8_t begin()
    {
        Serial.begin(m_baudrate);
        return 0;
    }

    /**
    * Stops the Serial Module without destroying the instance.
    * @return 0 for OK, 1 for Error
    */
    uint8_t end()
    {
        Serial.end();
        return 0;
    }

    /**
    * Sets the Baudrate for Serial Communication.
    * @param[in] baudrate      Baudrate for Serial Communication
    * @return 0 for OK, 1 for Error
    */
    uint8_t setBaudrate(uint32_t baudrate)
    {
        m_baudrate = baudrate;
        Serial.updateBaudRate(m_baudrate);
        return 0;
    }

    /**
    * Reads the Serial Adapter into a buffer.
    * @return isError: 0 for OK, 1 for Error
    */
    uint8_t read(char &c)
    {
        uint8_t isError = 0;
        if ((Serial.available() > 0) && (Serial.available() < 30))
        {
            c = Serial.read();
        }
        else
        {
            isError = 1;
        }

        return isError;
    }

    /**
    * Prints a Line to Serial Adapter.
    * @param[in] string     String to be printed
    */
    void print(const String &string)
    {
        Serial.print(string);
    }

    /**
    * Prints an Integer to Serial Adapter.
    * @param[in] num     Integer to be printed
    */
    void print(uint32_t num)
    {
        Serial.println(num);
    }

    /**
    * Prints a Character to Serial Adapter.
    * @param[in] c     Character to be printed
    */
    void print(char c)
    {
        Serial.println(c);
    }

protected:
private:
    long m_baudrate;
    String currentCommand = "";
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_ADAPTER_H */