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
@file       SerialAdapter.h

ESP32 Serial Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef SERIAL_ADAPTER_H
#define SERIAL_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include "Serialinterface.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
 *  ESP-32 Adapter as implementation of SerialInterface for the Lawicel Protocol.
 */
class SerialAdapter : public SerialInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
     *  Default constructor creates instance of the class using default values.
     */
    SerialAdapter() : SerialInterface(), m_baudrate(115200)
    {
    }

    /**
     *  Default destructor deletes instance of the class.
     */
    ~SerialAdapter()
    {
    }

    /**
     *  Configures and starts the Serial Controller to use the user values.
     * 
     *  @return success
     */
    bool begin()
    {
        Serial.begin(m_baudrate);
        return true;
    }

    /**
     *  Stops the Serial Module without destroying the instance.
     * 
     *  @return success
     */
    bool end()
    {
        Serial.end();
        return true;
    }

    /** 
     *  Sets the Baudrate for Serial Communication.
     * 
     *  @param[in] baudrate      Baudrate for Serial Communication
     *  @return success
     */
    bool setBaudrate(uint32_t baudrate)
    {
        m_baudrate = baudrate;
        Serial.updateBaudRate(m_baudrate);
        return true;
    }

    /** 
     *  Reads the Serial Adapter into a buffer.
     * 
     *  @param[in,out] c   Character received on the Serial Interface
     *  @return success
     */
    bool read(char &c)
    {
        bool success = false;
        if (0 < Serial.available())
        {
            c = Serial.read();
            success = true;
        }

        return success;
    }

    /** 
     *  Prints a String to Serial Adapter.
     * 
     *  @param[in] string     String to be printed
     */
    void print(const String &string)
    {
        Serial.print(string);
    }

    /** 
     *  Prints an Integer to Serial Adapter.
     * 
     *  @param[in] num     Integer to be printed
     */
    void print(uint32_t num)
    {
        Serial.println(num);
    }

    /** 
     *  Prints a Character to Serial Adapter.
     * 
     *  @param[in] c     Character to be printed
     */
    void print(char c)
    {
        Serial.println(c);
    }

protected:
private:
    long m_baudrate;            /**< Serial Baudrate */
    String currentCommand = ""; /**< Command Buffer. TODO: Delete unused String */
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_ADAPTER_H */