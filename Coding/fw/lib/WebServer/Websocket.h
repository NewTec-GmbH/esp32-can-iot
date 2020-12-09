#ifndef WEBSOCKET_H_
#define WEBSOCKET_H_
#include <AsyncWebSocket.h>
namespace websocket
{
    bool init(AsyncWebServer &server);
    bool cycle();
    void send(String message);
    bool receive(char &c);
};
#endif