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
#include "FlashMem.h"

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

    const String DIRECTORY = "Startup"; /**< Directory to store information in NVM */

    /* TYPES **********************************************************************************/

    /**
     *  Default constructor creates instance of the class using default values.
     */
    NVMAdapter() : NVMInterface()
    {
    }

    /**
     *  Default destructor deletes instance of the class.
     */
    ~NVMAdapter()
    {
    }

    /**
     *  Configures and starts the NVM Controller to use the user values.
     *  @return success
     */
    bool begin()
    {
        return true;
    }

    /**
     *  Stops the NVM Module without destroying the instance.
     * 
     *  @return success 
     */
    bool end()
    {
        return true;
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
        return Settings::save(DIRECTORY, name, value);
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
        return Settings::save(DIRECTORY, name, value);
    }

    /**
     *  Read Data from NVM
     * 
     *  @param[in] name Key of Parameter to retrieve
     *  @return Integer corresponding to the Key, if existent. Zero otherwise
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
     *  Read String from NVM
     * 
     *  @param[in] name Key of Parameter to retrieve
     *  @return String corresponding to the Key, if existent. Empty String otherwise
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
     *  Delete all NVM Entries.
     * 
     *  @return success
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