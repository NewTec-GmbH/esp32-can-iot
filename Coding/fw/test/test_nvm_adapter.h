/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Test
@{
@file       test_nvm_adapter.h

Native Test NVM Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef TEST_NVM_ADAPTER_H_
#define TEST_NVM_ADAPTER_H_

/* INCLUDES ***************************************************************************************/
#include "NVMInterface.h"
#include <stdint.h>
#include "WString.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
*  Native Adapter as implementation of NVMInterface for the Lawicel Protocol.
*/
class TestNVMAdapter : public NVMInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
    * Default constructor creates instance of the class using default values.
    */
    TestNVMAdapter() : NVMInterface()
    {
    }

    /**
    *Default destructor deletes instance of the class.
    */
    ~TestNVMAdapter()
    {
    }

    /**
    * Configures and starts the NVM Controller to use the user values.
    */
    bool begin()
    {
        bool success = true;
        return success;
    }

    /**
    * Stops the NVM Module without destroying the instance.
    */
    bool end()
    {
        bool success = true;
        return success;
    }

    /**
    * Save Data in NVM
    */
    bool save(const String &name, int32_t value)
    {
    }

    /**
    * Save String in NVM
    */
    bool save(const String &name, const String &value)
    {
        bool success = true;
        return success;
    }

    /**
    * Read Data from NVM
    */
    uint32_t readInt(const String &name)
    {
        uint32_t result;
        return result;
    }

    /**
     * Read String from NVM
    */
    String readString(const String &name)
    {
        String result;
        return result;
    }

    /**
     * Delete all NVM Entries.
     */
    bool clearEntries()
    {
        bool success = true;
        return success;
    }

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* TEST_NVM_ADAPTER_H */