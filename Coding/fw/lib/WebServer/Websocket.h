/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Webserver
@{
@file       Websocketg.h

Configuration of ESP32 WebSocket

* @}
***************************************************************************************************/
#ifndef WEBSOCKET_H_
#define WEBSOCKET_H_
/* INCLUDES ***************************************************************************************/
#include <AsyncWebSocket.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

namespace websocket
{
    void init(AsyncWebServer &server); /**< Initializes the WebSocket Service */
    void send(String message);         /**< Sends a WebSocket Message */
    bool receive(char &c);             /**< Receives a WebSocket Message */

}; // namespace websocket

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/

#endif /* WEBSOCKET_H_ */