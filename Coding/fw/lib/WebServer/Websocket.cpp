#include <Websocket.h>
#include <SPIFFS.h>

AsyncWebSocket ws("/ws");

static String processor(const String &var);
static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                    void *arg, uint8_t *data, size_t len);

bool websocket::init(AsyncWebServer &server)
{
    server.on("/communication", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/ws.html", String(), false, processor);
    });

    ws.onEvent(onEvent);
    server.addHandler(&ws);
    return true; /**< No error handling when registering handlers */
}

bool websocket::cycle()
{
    ws.cleanupClients();
    return true; /**< No error handling on cleanup */
}

static String processor(const String &var)
{
    Serial.println(var);
    if (var == "STATE")
    {
    }
    return "";
}

static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {
        Serial.println((char *)data);
    }
}

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

void websocket::send(String message)
{
    ws.textAll(message);
}