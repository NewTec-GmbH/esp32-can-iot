/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Adapters
@{
@file       WSAdapter.h

ESP32 WebSocket Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef WS_ADAPTER_H
#define WS_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include <Serialinterface.h>
#include <Websocket.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
*  ESP-32 Adapter as implementation of SerialInterface for the Lawicel Protocol.
*/
class WSAdapter : public SerialInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
    *  Default constructor creates instance of the class using default values.
    * @param m_baudrate     Sets the Default baudrate to the Serial Channel.
    */
    WSAdapter() : SerialInterface()
    {
    }

    /**
    * Default destructor deletes instance of the class.
    */
    ~WSAdapter()
    {
    }

    /**
    * Configures and starts the Serial Controller to use the user values.
    * @return 0 for OK, 1 for Error
    */
    bool begin()
    {
        Serial.begin(115200);
        return true;
    }

    /**
    * Stops the Serial Module without destroying the instance.
    * @return 0 for OK, 1 for Error
    */
    bool end()
    {
        return true;
    }

    /**
    * Sets the Baudrate for Serial Communication.
    * @param[in] baudrate      Baudrate for Serial Communication
    * @return 0 for OK, 1 for Error
    */
    bool setBaudrate(uint32_t baudrate)
    {
        return true;
    }

    /**
    * Reads the Serial Adapter into a buffer.
    * @return isError: 0 for OK, 1 for Error
    */
    bool read(char &c)
    {
        bool success = false;
        char input;
        if(websocket::receive(input))
        {
            c = input;
            success = true;
        }
        return success;
    }

    /**
    * Prints a Line to Serial Adapter.
    * @param[in] string     String to be printed
    */
    void print(const String &string)
    {
        websocket::send(string);
    }

    /**
    * Prints an Integer to Serial Adapter.
    * @param[in] num     Integer to be printed
    */
    void print(uint32_t num)
    {
        String tmp (num);
        websocket::send(tmp);
    }

    /**
    * Prints a Character to Serial Adapter.
    * @param[in] c     Character to be printed
    */
    void print(char c)
    {
        String tmp (c);
        websocket::send(tmp);
    }

protected:
private:
    long m_baudrate;
    String currentCommand = "";
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_ADAPTER_H */