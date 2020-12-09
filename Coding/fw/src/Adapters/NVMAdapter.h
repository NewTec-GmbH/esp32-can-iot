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
#include "NVMInterface.h"
#include "Settings.h"

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
    const String DIRECTORY = "Startup";
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
    bool begin()
    {
        return true;
    }

    /**
    * Stops the NVM Module without destroying the instance.
    */
    bool end()
    {
        return true;
    }

    /**
    * Save Data in NVM
    */
    bool save(const String &name, int32_t value)
    {
        return Settings::save(DIRECTORY, name, value);
    }

    /**
    * Save String in NVM
    */
    bool save(const String &name, const String &value)
    {
        return Settings::save(DIRECTORY, name, value);
    }

    /**
    * Read Data from NVM
    */
    uint32_t readInt(const String &name)
    {
        uint32_t result;
        if (!Settings::get(DIRECTORY, name, result))
        {
            result = 0;
        }
        return result;
    }

    /**
     * Read String from NVM
    */
    String readString(const String &name)
    {
        String result;
        if (!Settings::get(DIRECTORY, name, result))
        {
            result = "";
        }
        return result;
    }

    /**
     * Delete all NVM Entries.
     */
    bool clearEntries()
    {
        return Settings::clear(DIRECTORY);
    }

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* NVM_ADAPTER_H */