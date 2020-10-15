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
#include <NVMInterface.h>
#include <Preferences.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

class NVMAdapter : public NVMInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
     * Default constructor.
     */

    NVMAdapter() : NVMInterface()
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
    uint8_t begin()
    {
        nvm.begin("Startup", false);
        nvm.end();
        return 0;
    }

    /**
    * Terminate Module
    */
    uint8_t end()
    {
        nvm.begin("Startup", false);
        nvm.clear();
        nvm.end();
        return 0;
    }

    /**
    * Save Data in NVM
    */
    void saveInt(String name, int32_t value)
    {
        nvm.begin("Startup", false);
        nvm.putULong(name.c_str(), value);
        nvm.end();
    }

    /**
    * Save String in NVM
    */
    void saveString(String name, String value)
    {
        nvm.begin("Startup", false);
        nvm.putString(name.c_str(), value);
        nvm.end();
    }

    /**
    * Read Data from NVM
    */
    uint32_t readInt(String name)
    {
        nvm.begin("Startup", false);
        uint32_t value = nvm.getULong(name.c_str());
        nvm.end();

        return value;
    }

    /**
     * Read String from NVM
    */
    String readString(String name)
    {
        nvm.begin("Startup", false);
        String value = nvm.getString(name.c_str());
        nvm.end();
        return value;
    }


private:
    Preferences nvm;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* NVM_ADAPTER_H */