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
@file       test_serial_adapter.h

Native Test Serial Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef TEST_WS_ADAPTER_H
#define TEST_WS_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include <Serialinterface.h>
#include <stdint.h>
#include "WString.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
 *  ESP-32 Adapter as implementation of SerialInterface for the Lawicel Protocol.
 */
class TestSerialAdapter : public SerialInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /** 
     *  Default constructor creates instance of the class using default values.
     */
    TestSerialAdapter() : SerialInterface()
    {
    }

    /** 
     *  Default destructor deletes instance of the class.
     */
    ~TestSerialAdapter()
    {
    }

    /** 
     *  Configures and starts the Serial Controller to use the user values.
     * 
     *  @return success
     */
    bool begin()
    {
        bool success = true;
        return success;
    }

    /** 
     *  Stops the Serial Module without destroying the instance.
     * 
     *  @return success
     */
    bool end()
    {
        bool success = true;
        return success;
    }

    /** 
     *  Sets the Baudrate for Serial Communication.
     * 
     *  @param[in] baudrate      Baudrate for Serial Communication
     *  @return success
     */
    bool setBaudrate(uint32_t baudrate)
    {
        bool success = true;
        m_serialBaudrate = baudrate;
        return success;
    }

    /** 
     *  Prints a String to Serial Adapter.
     * 
     *  @param[in] string     String to be printed
     */
    bool read(char &c)
    {
        bool available = false;
        if (0 != m_inputString.length())
        {
            available = true;
            c = m_inputString[position];
            position++;
        }

        return available;
    }

    /** 
     *  Prints an Integer to Serial Adapter.
     * 
     *  @param[in] num     Integer to be printed
     */
    void print(const String &string)
    {
        m_outputString = string;
    }

    /**
    * Prints an Integer to Serial Adapter.
    * @param[in] num     Integer to be printed
    */
    void print(uint32_t num)
    {
        m_outputString = String(num);
    }

    /** 
     *  Prints a Character to Serial Adapter.
     * 
     *  @param[in] c     Character to be printed
     */
    void print(char c)
    {
        m_outputString = String(c);
    }

    /**
     *  Edit Input Lawicel-Formatted String
     * 
     * @param input Lawicel-Formatted String
     * @return Input length 
     */
    int writeInput(String input)
    {
        m_inputString = "";
        position = 0;
        m_inputString = input + '\r';
        return input.length() + 1;
    }

    String m_inputString;      /**< Simulated Input String */
    String m_outputString;     /**< Simulated Output String */
    uint32_t m_serialBaudrate; /**< Serial Baudrate */
    uint8_t position = 0;      /**< Position Marker */
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* TEST_SERIAL_ADAPTER_H */