#include <Websocket.h>
#include <SPIFFS.h>

AsyncWebSocket ws("/ws");

static String inputBuffer;

static String processor(const String &var);
static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                    void *arg, uint8_t *data, size_t len);

bool websocket::init(AsyncWebServer &server)
{
    Serial.begin(115200);
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
        inputBuffer += (char *)data;
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
    String systime = String(millis());
    if(message[0] == (char)7)
    {
        message = '.';
    }
    else 
    {
        message += systime.substring(0, 7);
    }
    ws.textAll(message);
}

bool websocket::receive(char &c)
{
    bool available = false;
    if (inputBuffer.length() != 0)
    {
        available = true;
        c = inputBuffer[0];
        inputBuffer.remove(0, 1);
    }

    return available;
}