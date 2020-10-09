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
  void begin()
  {
    Serial.begin(m_baudrate);
  }

  /**
  * Terminate Module
  */
  void end()
  {
    Serial.end();
  }

  /**
  * Send String to output.
  */
  void send(char *str)
  {
    Serial.print(str);
  }

  /**
  * Send String to output.
  */
  void setBaudrate(long _baudrate)
  {
    m_baudrate = _baudrate;
    Serial.updateBaudRate(m_baudrate);
  }

  /**
  * Send String to output.
  */
  uint8_t read(char *Buffer)
  {
    memset(Buffer, '0', 32);
    int availableBytes = 0;

    if (Serial.available())
    {
      availableBytes = Serial.available();
      for (int i = 0; i < availableBytes; i++)
      {
        Buffer[i] = Serial.read();
      }
    }
    return availableBytes;
  }

  /**
    * Prints a Line to Serial Adapter.
    */
  void print(String string)
  {
    Serial.println(string);
  }

  void print(int num)
  {
    Serial.println(num);
  }

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