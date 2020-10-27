/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Adapters
@{
@file       NVMAdapter.h

ESP32 NVM Adapter for Lawicel Protocol

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

/**
*  ESP-32 Adapter as implementation of NVMInterface for the Lawicel Protocol.
*/
class NVMAdapter : public NVMInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
    * Default constructor creates instance of the class using default values.
    */
    NVMAdapter() : NVMInterface()
    {
    }

    /**
    *Default destructor deletes instance of the class.
    */
    ~NVMAdapter()
    {
    }

    /**
    * Configures and starts the NVM Controller to use the user values.
    */
    uint8_t begin()
    {
        nvm.begin("Startup", false);
        nvm.end();
        return 0;
    }

    /**
    * Stops the NVM Module without destroying the instance.
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
    void save(const String &name, int32_t value)
    {
        nvm.begin("Startup", false);
        nvm.putULong(name.c_str(), value);
        nvm.end();
    }

    /**
    * Save String in NVM
    */
    void save(const String &name, const String &value)
    {
        nvm.begin("Startup", false);
        nvm.putString(name.c_str(), value);
        nvm.end();
    }

    /**
    * Read Data from NVM
    */
    uint32_t readInt(const String &name)
    {
        nvm.begin("Startup", false);
        uint32_t value = nvm.getULong(name.c_str());
        nvm.end();

        return value;
    }

    /**
     * Read String from NVM
    */
    String readString(const String &name)
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