/***************************************************************************************************
BSD 3-Clause License


Copyright (c) 2020-2023, NewTec GmbH - www.newtec.de
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
@file       TelnetAdapter.h

ESP32 Telnet Serial Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef TELNET_ADAPTER_H
#define TELNET_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include "Serialinterface.h"
#include <ESPTelnet.h>
#include "WLAN.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

static const uint32_t TELNET_PORT = 23U; /** Telnet Port number */
static ESPTelnet telnet;    /** Instance of Telnet */
static QueueHandle_t gInputQueue; /**< WebSocket input Queue */

/**
 *  ESP-32 Telnet Adapter as implementation of SerialInterface for the Lawicel Protocol.
 */
class TelnetAdapter : public SerialInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
     *  Default constructor creates instance of the class using default values.
     */
    TelnetAdapter() : SerialInterface()
    {
    }

    /**
     *  Default destructor deletes instance of the class.
     */
    ~TelnetAdapter()
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
        gInputQueue = xQueueCreate(100, sizeof(char));

        if (!wlan::begin())
        {
            success = false;
        }
        else if (NULL == gInputQueue)
        {
            success = false;
        }
        else
        {
            telnet.onInputReceived([](String str) {
                str += "\r"; // Telnet does not append CR by default
                for (int i = 0; i < str.length(); i++)
                {
                    if (pdTRUE != xQueueSendToBack(gInputQueue, &str[i], 0))
                    {
                        break;
                    }
                }
            });

            telnet.onConnect([](String str) {
                telnet.println("Connected to ESP-CAN-IOT");
            });

            success = telnet.begin(TELNET_PORT);
        }
        
        return success;
    }

    /**
     *  Stops the Serial Module without destroying the instance.
     * 
     *  @return success
     */
    bool end()
    {
        telnet.stop();
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
        telnet.loop();

        if (xQueueReceive(gInputQueue, &c, 0) == pdTRUE)
        {
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
        // Implementation here
        telnet.print(string);
    }

    /** 
     *  Prints an Integer to Serial Adapter.
     * 
     *  @param[in] num     Integer to be printed
     */
    void print(uint32_t num)
    {
        telnet.print(num);
    }

    /** 
     *  Prints a Character to Serial Adapter.
     * 
     *  @param[in] c     Character to be printed
     */
    void print(char c)
    {
        telnet.print(c);
    }

protected:
private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_ADAPTER_H */