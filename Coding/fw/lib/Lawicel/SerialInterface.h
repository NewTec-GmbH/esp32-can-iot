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
   * Default constructor creates instance of the class using default values.
   */
  SerialInterface()
  {
  }

  /** 
   * Default destructor deletes instance of the class.
   */
  virtual ~SerialInterface()
  {
  }

  /** 
   * Configures and starts the Serial Controller to use the user values.
   * @return 0 for OK, 1 for Error
   */
  virtual uint8_t begin() = 0;

  /** 
   * Stops the Serial Module without destroying the instance.
   * @return 0 for OK, 1 for Error
   */
  virtual uint8_t end() = 0;

  /** 
   * Sets the Baudrate for Serial Communication.
   * @param[in] baudrate      Baudrate for Serial Communication
   * @return 0 for OK, 1 for Error
   */
  virtual uint8_t setBaudrate(uint32_t baudrate) = 0;

  /** 
   * Reads the Serial Adapter into a buffer.
   * @return isError: 0 for OK, 1 for Error
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