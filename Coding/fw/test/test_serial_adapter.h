/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Test
@{
@file       test_serial_adapter.h

Native Test Serial Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef TEST_WS_ADAPTER_H
#define TEST_WS_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include <Serialinterface.h>
#include <stdint.h>
#include "WString.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
*  ESP-32 Adapter as implementation of SerialInterface for the Lawicel Protocol.
*/
class TestSerialAdapter : public SerialInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
    *  Default constructor creates instance of the class using default values.
    * @param m_baudrate     Sets the Default baudrate to the Serial Channel.
    */
    TestSerialAdapter() : SerialInterface()
    {
    }

    /**
    * Default destructor deletes instance of the class.
    */
    ~TestSerialAdapter()
    {
    }

    /**
    * Configures and starts the Serial Controller to use the user values.
    * @return 0 for OK, 1 for Error
    */
    bool begin()
    {
        bool success = false;
        return success;
    }

    /**
    * Stops the Serial Module without destroying the instance.
    * @return 0 for OK, 1 for Error
    */
    bool end()
    {
        bool success = false;
        return success;
    }

    /**
    * Sets the Baudrate for Serial Communication.
    * @param[in] baudrate      Baudrate for Serial Communication
    * @return 0 for OK, 1 for Error
    */
    bool setBaudrate(uint32_t baudrate)
    {
        bool success = false;
        return success;
    }

    /**
    * Reads the Serial Adapter into a buffer.
    * @return isError: 0 for OK, 1 for Error
    */
    bool read(char &c)
    {
        bool success = false;
        return success;
    }

    /**
    * Prints a Line to Serial Adapter.
    * @param[in] string     String to be printed
    */
    void print(const String &string)
    {
    }

    /**
    * Prints an Integer to Serial Adapter.
    * @param[in] num     Integer to be printed
    */
    void print(uint32_t num)
    {
    }

    /**
    * Prints a Character to Serial Adapter.
    * @param[in] c     Character to be printed
    */
    void print(char c)
    {
    }

protected:
private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* TEST_SERIAL_ADAPTER_H */