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
@file       FlashMem.h

Handler for ESP32 Preferences in Flash Memory

* @}
***************************************************************************************************/
#ifndef FLASH_MEM_H_
#define FLASH_MEM_H_

/* INCLUDES ***************************************************************************************/
#include <Preferences.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/
/*
* Implementation of the Preferences Library for the project. Initial values and commands are
* saved and called through this class.
*/
namespace Settings
{
    bool save(                         /**< Saves uint32_t value to Flash memory */
              const String &directory, /**< Directory where information is stored */
              const String &key,       /**< Name of Memory Location */
              const uint32_t &value);  /**< Value to be stored */

    bool save(                         /**< Saves uint32_t value to Flash memory */
              const String &directory, /**< Directory where information is stored */
              const String &key,       /**< Name of Memory Location */
              const String &value);    /**< String to be stored */

    bool get(                                   /**< Gets uint32_t value from Flash memory */
             const String &directory,           /**< Directory where information is stored */
             const String &key,                 /**< Name of Memory Location */
             uint32_t &value,                   /**< Variable to write the value to */
             const uint32_t &defaultValue = 0U); /**< Default value returned if no value stored in memory */

    bool get(                                 /**< Gets uint32_t value from Flash memory */
             const String &directory,         /**< Directory where information is stored */
             const String &key,               /**< Name of Memory Location */
             String &value,                   /**< Variable to write the String to */
             const String &defaultValue = ""); /**< Default String returned if no String stored in memory */

    bool clear(const String &directory); /**< Clears all entries on a directory */
};                                       // namespace Settings

    /* INLINE FUNCTIONS ***************************************************************************/

    /* PROTOTYPES *********************************************************************************/

#endif /* FLASH_MEM_H_ */