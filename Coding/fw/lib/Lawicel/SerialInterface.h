/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Lawicel
@{
@file       SerialInterface.h

Serial Interface for Lawicel Protocol

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
    virtual void begin() = 0;

   /** 
   * Terminate Module. 
   */
    virtual void end() = 0;

   /** 
   * Sets the Baudrate for Serial Communication.
   * @param[in] _baudrate      Baudrate for Serial Communication
   */
    virtual void setBaudrate(long _baudrate) = 0;

   /** 
   * Reads the Serial Adapter into a buffer.
   * @return Serial input 
   */
    virtual String read() = 0;

   /** 
   * Prints a String to Serial Adapter.
   * @param[in] string     String to be printed
   */
    virtual void print(String string) = 0;

   /** 
   * Prints a Integer to Serial Adapter.
   * @param[in] num     Integer to be printed
   */
    virtual void print(int num) = 0;

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