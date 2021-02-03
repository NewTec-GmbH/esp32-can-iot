/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
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
AsyncWebSocket ws("/ws");

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                    void *arg, uint8_t *data, size_t len);

/* VARIABLES **************************************************************************************/

static QueueHandle_t inputQueue;
static String outputBuffer = "";

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/*
*   Initializes the WebSocket Service
*/
void websocket::init(AsyncWebServer &server)
{
    server.on("/communication", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/ws.html");
    });

    ws.onEvent(onEvent);
    server.addHandler(&ws);
    inputQueue = xQueueCreate(100, sizeof(char));
}

/**************************************************************************************************/

/*
*   Send WebSocket Message
*/
void websocket::send(const String &message)
{
    outputBuffer += message;
}

/**************************************************************************************************/

/**
*   Sends the Websocket Buffer
*   
*/
bool websocket::sendBuffer()
{
    bool success = true;

    if (outputBuffer.length() != 0)
    {
        ws.textAll(outputBuffer);
        outputBuffer.clear();
    }
    return success;
}

/**************************************************************************************************/

/*
*   Receive WebSocket Message
*/
bool websocket::receive(char &c)
{
    bool success = false;

    if (xQueueReceive(inputQueue, &c, 0) == pdTRUE)
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

/*
*   Handler for incoming Web Socket Message
*/
static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if ((info->final) && (0 == info->index) && (len == info->len) && (WS_TEXT == info->opcode))
    {
        for (int i = 0; i < len; i++)
        {
            if (errQUEUE_FULL == xQueueSendToBack(inputQueue, &data[i], 0))
            {
                Serial.println("Queue Full");
                Board::blinkError(250);
                break;
            }
        }
    }
}

/**************************************************************************************************/

/*
*   Handler for Web Socket Event
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