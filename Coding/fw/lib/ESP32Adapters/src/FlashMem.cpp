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
@addtogroup Settings
@{
@file       FlashMem.cpp

Handler for ESP32 Preferences in Flash Memory. @ref FlashMem.h

***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "FlashMem.h"
#include <Preferences.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

static Preferences gMemory; /**< Instances of Preferences Library to save information in NVM */

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
 *  Saves uint32_t value to Flash memory
 */
bool Settings::save(const String &directory, const String &key, const uint32_t &value)
{
    bool success = false;
    if (gMemory.begin(directory.c_str(), false))
    {
        gMemory.putULong(key.c_str(), value);
        gMemory.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Saves String value to Flash memory
 */
bool Settings::save(const String &directory, const String &key, const String &value)
{
    bool success = false;
    if (gMemory.begin(directory.c_str(), false))
    {
        gMemory.putString(key.c_str(), value);
        gMemory.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Gets uint32_t value from Flash memory
 */
bool Settings::get(const String &directory, const String &key, uint32_t &value, const uint32_t defaultValue)
{
    bool success = false;
    if (gMemory.begin(directory.c_str(), false))
    {
        value = gMemory.getULong(key.c_str(), defaultValue);
        gMemory.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Gets String from Flash memory
 */
bool Settings::get(const String &directory, const String &key, String &value, const String &defaultValue)
{
    bool success = false;
    if (gMemory.begin(directory.c_str(), false))
    {
        value = gMemory.getString(key.c_str(), defaultValue);
        gMemory.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/
/**
 *  Clears all entries on a directory
 */
bool Settings::clear(const String &directory)
{
    bool success = false;
    if (gMemory.begin(directory.c_str(), false))
    {
        success = gMemory.clear();
    }

    return success;
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

/** @} */