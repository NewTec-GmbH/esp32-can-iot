/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Lawicel
@{
@file       NVMInterface.h

NVM Interface for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef NVM_INTERFACE_H
#define NVM_INTERFACE_H

/* INCLUDES ***************************************************************************************/

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

class NVMInterface
{
public:
  /* CONSTANTS ******************************************************************************/

  /* TYPES **********************************************************************************/

  /**
  * Default constructor.
  */

  NVMInterface()
  {
  }

  /**
  * Default destructor
  */

  virtual ~NVMInterface()
  {
  }

  /**
    * Initialize Module
    */
  virtual uint8_t begin() = 0;

  /**
  * Terminate Module
  */
  virtual uint8_t end() = 0;

  /**
  * Save Data in NVM
  */
  virtual void saveInt(String name, int32_t value) = 0;

  /**
  * Save String in NVM
  */
  virtual void saveString(String name, String value) = 0;

  /**
  * Read Data from NVM
  */
  virtual uint32_t readInt(String name) = 0;

  /**
  * Read String from NVM
  */
  virtual String readString(String name) = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* NVM_INTERFACE_H */