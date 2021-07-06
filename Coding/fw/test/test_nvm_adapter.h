/***************************************************************************************************
BSD 3-Clause License


Copyright (c) 2020-2021, NewTec GmbH - www.newtec.de
All rights reserved.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:


1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.


2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.


3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
     *  Default constructor creates instance of the class using default values.
     */
    TestNVMAdapter() : NVMInterface()
    {
    }

    /**
     *  Default destructor deletes instance of the class.
     */
    ~TestNVMAdapter()
    {
    }

    /**
     *  Configures and starts the NVM Controller to use the user values.
     * 
     *  @return success
     */
    bool begin()
    {
        bool success = true;
        return success;
    }

    /**
     *  Stops the NVM Module without destroying the instance.
     * 
     *  @return success
     */
    bool end()
    {
        bool success = true;
        return success;
    }

    /**
     *  Save Data in NVM
     * 
     *  @param[in] name Key of Parameter to save
     *  @param[in] value Integer to save
     *  @return success
     */
    bool save(const String &name, int32_t value)
    {
        bool success = true;
        m_outputInt = value;
        return success;
    }

    /**
     *  Save String in NVM
     * 
     *  @param[in] name Key of Parameter to save
     *  @param[in] value String to save
     *  @return success
     */
    bool save(const String &name, const String &value)
    {
        bool success = true;
        m_outputString = value;
        return success;
    }

    /**
     *  Read Data from NVM
     * 
     *  @param[in] name Key of Parameter to retrieve
     *  @return Integer corresponding to the Key, if existent. Zero otherwise
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
     *  Read String from NVM
     * 
     *  @param[in] name Key of Parameter to retrieve
     *  @return String corresponding to the Key, if existent. Empty String otherwise
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
     *  Delete all NVM Entries.
     * 
     *  @return success
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