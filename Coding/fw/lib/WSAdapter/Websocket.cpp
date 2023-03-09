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
@addtogroup Webserver
@{
@file       Websocket.cpp

Configuration of ESP32 WebSocket. @ref Websocket.h

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "Websocket.h"
#include <SPIFFS.h>
#include "Board.h"
#include "WLAN.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/**
 *  Handler for incoming Web Socket Message
 * 
 *  @param[in] arg Information of Web Socket Message
 *  @param[in] data Data of Web Socket Message
 *  @param[in] len Length of Data of Web Socket Message
 */
static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

/**
 *  Handler for Web Socket Event
 * 
 *  @param[in] server Instance of ESPAsyncWebServer
 *  @param[in] client Instance of Web Client
 *  @param[in] type Type of Web Socket Event
 *  @param[in] arg Information of Web Socket Event
 *  @param[in] data Data of Web Socket Event
 *  @param[in] len Length of Data of Web Socket Event
 */
static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                    void *arg, uint8_t *data, size_t len);

/* VARIABLES **************************************************************************************/

static AsyncWebSocket gWs("/ws"); /**< Instance of Web Socket Handler */
static QueueHandle_t gInputQueue; /**< WebSocket input Queue */
static String gOutputBuffer = ""; /**< WebSocket output Buffer */

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
 *  Initializes the WebSocket Service
 * 
 *  @param[in] server AsyncWeb Server Instance
 */
void websocket::init(AsyncWebServer &server)
{
    server.on("/communication", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/ws.html");
    });

    gWs.onEvent(onEvent);
    server.addHandler(&gWs);
    gInputQueue = xQueueCreate(100, sizeof(char));
}

/**************************************************************************************************/

/**
 *  Send WebSocket Message
 * 
 *  @param[in] message Message to be sent to client through WebSocket
 */
void websocket::send(const String &message)
{
    gOutputBuffer += message;
}

/**************************************************************************************************/

/**
 *  Sends the Websocket Buffer
 *   
 *  @return success
 */
bool websocket::sendBuffer()
{
    bool success = true;

    if (gOutputBuffer.length() != 0)
    {
        gWs.textAll(gOutputBuffer);
        gOutputBuffer.clear();
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Receive character from WebSocket Message
 * 
 *  @param[in,out] c Character to be received
 *  @return success
 */
bool websocket::receive(char &c)
{
    bool success = false;

    if (xQueueReceive(gInputQueue, &c, 0) == pdTRUE)
    {
        success = true;
    }

    return success;
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

/**************************************************************************************************/

/**
 *  Handler for incoming Web Socket Message
 * 
 *  @param[in] arg Information of Web Socket Event
 *  @param[in] data Data of Web Socket Event
 *  @param[in] len Length of Data of Web Socket Event
 */
static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if ((info->final) && (0 == info->index) && (len == info->len) && (WS_TEXT == info->opcode))
    {
        for (int i = 0; i < len; i++)
        {
            if (errQUEUE_FULL == xQueueSendToBack(gInputQueue, &data[i], 0))
            {
                Serial.println("Queue Full");
                Board::blinkError(250);
                break;
            }
        }
    }
}

/**************************************************************************************************/

/**
 *  Handler for Web Socket Event
 * 
 *  @param[in] server Instance of ESPAsyncWebServer
 *  @param[in] client Instance of Web Client
 *  @param[in] type Type of Web Socket Event
 *  @param[in] arg Information of Web Socket Event
 *  @param[in] data Data of Web Socket Event
 *  @param[in] len Length of Data of Web Socket Event
 */
static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                    void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}