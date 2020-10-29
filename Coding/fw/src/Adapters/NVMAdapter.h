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
    const char *DIRECTORY = "Startup";
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
        nvm.begin(DIRECTORY, false);
        nvm.end();
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
        bool success = true;
        if (nvm.begin(DIRECTORY, false))
        {
            nvm.putULong(name.c_str(), value);
            nvm.end();
        }
        else
        {
            success = false;
        }
        return success;
    }

    /**
    * Save String in NVM
    */
    bool save(const String &name, const String &value)
    {
        bool success = true;
        if (nvm.begin(DIRECTORY, false))
        {
            nvm.putString(name.c_str(), value);
            nvm.end();
        }
        else
        {
            success = false;
        }
        return success;
    }

    /**
    * Read Data from NVM
    */
    uint32_t readInt(const String &name)
    {
        nvm.begin(DIRECTORY, false);
        uint32_t value = nvm.getULong(name.c_str());
        nvm.end();

        return value;
    }

    /**
     * Read String from NVM
    */
    String readString(const String &name)
    {
        nvm.begin(DIRECTORY, false);
        String value = nvm.getString(name.c_str());
        nvm.end();
        return value;
    }

    /**
     * Delete all NVM Entries.
     */
    bool clearEntries()
    {
        bool success = true;
        if (!nvm.begin(DIRECTORY, false))
        {
            success = false;
        }
        else if (!nvm.clear())
        {
            success = false;
        }
        nvm.end();
        return success;
    }

private:
    Preferences nvm;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* NVM_ADAPTER_H */