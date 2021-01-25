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
        bool success = true;
        m_outputInt = value;
        return success;
    }

    /**
    * Save String in NVM
    */
    bool save(const String &name, const String &value)
    {
        bool success = true;
        m_outputString = value;
        return success;
    }

    /**
    * Read Data from NVM
    */
    uint32_t readInt(const String &name)
    {
        uint32_t result = 0;

        if( name == INIT_AUTO_START)
        {
            result = 0;
        }

        if(name == INIT_TIMESTAMP)
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
        String result = "";

        if(name == INIT_SERIAL_BAUD)
        {
            result = "U2";
        }
        if(name == INIT_CAN_BAUD)
        {
            result = "S6";
        }
        if(name == INIT_FILTER_MODE)
        {
            result = "W0";
        }
        if(name == INIT_FILTER_ACN)
        {
            result = "M00000000";
        }
        if(name == INIT_FILTER_AMN)
        {
            result = "mFFFFFFFF";
        }

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

    String m_outputString = "";
    uint32_t m_outputInt = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* TEST_NVM_ADAPTER_H */