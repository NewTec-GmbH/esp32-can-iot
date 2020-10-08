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
  virtual void begin() = 0;

  /**
  * Terminate Module
  */
  virtual void end() = 0;
  /**
  * Save Data in NVM
  */
  virtual uint8_t save(uint8_t address, uint32_t data) = 0;

  /**
  * Read Data from NVM
  */
  virtual uint8_t read(uint8_t address) = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* NVM_INTERFACE_H */