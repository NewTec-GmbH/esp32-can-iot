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
  * Constructs a empty Serial Adapter.
  **/
  SerialAdapter() : m_name(), m_baudrate()
  {
  }

  /**
  * Default Serial Adapter constructor.
  */
  SerialAdapter(const String name, long baudrate) : m_name(name), m_baudrate(baudrate)
  {
    Serial.begin(m_baudrate);
  }

  /**
  * Default Serial Adapter destructor.
  */
  ~SerialAdapter();

  /**
  * Get Adapter name
  */
  const String &getName() const
  {
    return m_name;
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

    if (Serial.available())
    {
      int availableBytes = Serial.available();
      Serial.println(availableBytes);
      for (int i = 0; i < availableBytes; i++)
      {
        Buffer[i] = Serial.read();
        Buffer[i + 1] = '\n';
      }
      for (int i = 0; i < availableBytes; i++)
      {
        Serial.printf("%c", Buffer[i]);
      }
      return availableBytes;
    }

    return 1;
  }

protected:
private:
  String m_name;
  long m_baudrate;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* XXXXX_H */