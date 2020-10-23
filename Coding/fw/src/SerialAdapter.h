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

class SerialAdapter : public SerialInterface
{
public:
  /* CONSTANTS ******************************************************************************/

  /* TYPES **********************************************************************************/

  /**
  * Default Serial Adapter constructor.
  */
  SerialAdapter() : SerialInterface(), m_baudrate(115200)
  {
  }

  /**
  * Default Serial Adapter destructor.
  */
  ~SerialAdapter()
  {
  }

  /**
  * Initialize Module.
  */
  uint8_t begin()
  {
    Serial.begin(m_baudrate);
    return 0;
  }

  /**
  * Terminate Module
  */
  uint8_t end()
  {
    Serial.end();
    return 0;
  }

  /**
  * Sets the Baudrate for Serial Communication.
  */
  void setBaudrate(uint32_t baudrate)
  {
    m_baudrate = baudrate;
    Serial.updateBaudRate(m_baudrate);
  }

  /**
  * Reads the Serial Adapter into a buffer.
  */
  uint8_t read(char &c)
  {
    if ((Serial.available() > 0) && (Serial.available() < 30))
    {
      c = Serial.read();
    }
    return 0;
  }

  /**
  * Prints a Line to Serial Adapter.
  */
  void print(const String &string)
  {
    Serial.print(string);
  }

  /**
  * Prints an Integer to Serial Adapter.
  */
  void print(uint32_t num)
  {
    Serial.println(num);
  }

  /**
  * Prints a Character to Serial Adapter.
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