/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Interfaces
@ingroup Lawicel
@{
@file       SerialInterface.h

SerialInterface for Lawicel Protocol

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
   * Default destructor. 
   */
  virtual ~SerialInterface()
  {
  }

  /** 
   * Initialize Module.
   */
  virtual uint8_t begin() = 0;

  /** 
   * Terminate Module. 
   */
  virtual uint8_t end() = 0;

  /** 
   * Sets the Baudrate for Serial Communication.
   * @param[in] baudrate      Baudrate for Serial Communication
   */
  virtual void setBaudrate(uint32_t baudrate) = 0;

  /** 
   * Reads the Serial Adapter into a buffer.
   * @return Serial input 
   */
  virtual uint8_t read(char &c) = 0;

  /** 
   * Prints a String to Serial Adapter.
   * @param[in] string     String to be printed
   */
  virtual void print(const String &string) = 0;

  /** 
   * Prints an Integer to Serial Adapter.
   * @param[in] num     Integer to be printed
   */
  virtual void print(uint32_t num) = 0;

  /** 
   * Prints a Character to Serial Adapter.
   * @param[in] c     Character to be printed
   */
  virtual void print(char c) = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */