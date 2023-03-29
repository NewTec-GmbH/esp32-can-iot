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
@addtogroup Application
@{
@file       main.cpp

Main Application

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include <Arduino.h>
#include <Lawicel.h>
#include "CANAdapter.h"
#include "NVMAdapter.h"
#include "Board.h"

#ifdef USE_SERIAL_ADAPTER_WS
    #include "WebSocketAdapter.h"
    #include "WLAN.h"
#elif USE_SERIAL_ADAPTER_UART
    #include "SerialAdapter.h"
#elif USE_SERIAL_ADAPTER_TELNET
    #include "TelnetAdapter.h"
#endif

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

static CANAdapter gSja1000Adapter;   /**< CAN Adapter Instance */
static NVMAdapter gFlashAdapter;     /**< NVM Adapter Instance */

#ifdef USE_SERIAL_ADAPTER_WS
    static WebSocketAdapter gWsadapter;  /**< WebSocket Adapter Instance */
    static uint32_t gLastSend = 0;  /**< Timestamp of last sent WebSocket Buffer */
    static uint32_t gWaitTime = 50; /**< Delay between WebSocket Buffer send in milliseconds*/
    
    /** Instance of Lawicel Protocol */
    static Lawicel gProtocolLawicel(gWsadapter, gSja1000Adapter, gFlashAdapter);
#elif USE_SERIAL_ADAPTER_UART
    static SerialAdapter gSerialAdapter; /**< Serial Adapter Instance */

    /** Instance of Lawicel Protocol */
    static Lawicel gProtocolLawicel(gSerialAdapter, gSja1000Adapter, gFlashAdapter);
#elif USE_SERIAL_ADAPTER_TELNET
    static TelnetAdapter gTelnetAdapter; /**< Telnet Adapter Instance */

    /** Instance of Lawicel Protocol */
    static Lawicel gProtocolLawicel(gTelnetAdapter, gSja1000Adapter, gFlashAdapter); 
#endif


/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
 *  Initialization of Application
 */
void setup()
{
    Board::init();
    if (!gProtocolLawicel.begin())
    {
        Board::haltSystem();
    }
}

/**************************************************************************************************/

/**
 *  Application Loop
 */
void loop()
{
#ifdef USE_SERIAL_ADAPTER_WS
    if (!wlan::getAP_MODE())
    {
#endif
        if (!gProtocolLawicel.executeCycle())
        {
            Board::blinkError(250);
        }

#ifdef USE_SERIAL_ADAPTER_WS
        if (!wlan::checkConnection())
        {
            Board::haltSystem();
        }
    }
    if (ESPServer::isRestartRequested())
    {
        Board::reset();
    }

    if (millis() - gLastSend > gWaitTime)
    {
        gLastSend = millis();
        websocket::sendBuffer();
    }
#endif
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/
