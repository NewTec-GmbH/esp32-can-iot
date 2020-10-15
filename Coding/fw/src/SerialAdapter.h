/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup gggggModule_group gggggModule
@{
@file       Xxxxx.h

Enter short description here.

Enter detailed description here.

@version    %$Id: CppTemplate.h 8740 2018-05-05 12:46:37Z link $
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
  void setBaudrate(long _baudrate)
  {
    m_baudrate = _baudrate;
    Serial.updateBaudRate(m_baudrate);
  }

  /**
  * Reads the Serial Adapter into a buffer.
  */
  String read()
  {
    if (Serial.available() > 0){
      return Serial.readStringUntil('\r');
    }
    else
    {
      return "";
    }        
  }

  /**
  * Prints a Line to Serial Adapter.
  */
  void print(String string)
  {
    Serial.print(string);
  }

  /**
  * Prints an Integer to Serial Adapter.
  */
  void print(int num)
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
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* XXXXX_H */