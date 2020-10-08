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
#ifndef NVM_ADAPTER_H
#define NVM_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include <Preferences.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

class NVMAdapter
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
     * Default constructor.
     */

    NVMAdapter()
    {
    }

    /**
    * Default destructor
    */

    ~NVMAdapter()
    {
    }

    /**
    * Initialize Module
    */
    void begin()
    {
    }

    /**
    * Terminate Module
    */
    void end()
    {
    }

    /**
    * Save Data in NVM
    */
    void save(const char *key,int32_t value)
    {
        nvm.begin("Startup", false);
        nvm.putULong(key, value);
        nvm.end();
    }

    /**
    * Read Data from NVM
    */
    uint32_t read(const char *key)
    {
        nvm.begin("Startup", false);
        uint32_t value = nvm.putULong(key, value);
        nvm.end();
        
        return value;
    }

private:
    Preferences nvm;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* NVM_ADAPTER_H */