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
#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

/* INCLUDES ***************************************************************************************/

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

class SerialInterface
{
public:
  /* CONSTANTS ******************************************************************************/

  /* TYPES **********************************************************************************/

  /**
     * Default constructor.
     */

  SerialInterface()
  {
  }

  /**
    * Default destructor
    */

  virtual ~SerialInterface()
  {
  }

  /**
    * Initialize Module
    */
  virtual void begin() = 0;

  /**
  * Terminate Module
  */
 virtual void end() = 0;

  /**
    * Send a Data String.
    */

  virtual void send(char *str) = 0;

  /**
    * Sets the Baudrate for Serial Communication.
    */

  virtual void setBaudrate(long _baudrate) = 0;

  /**
    * Reads the Serial Adapter into a buffer.
    */

  virtual uint8_t read(char *Buffer) = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */