/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Webserver
@{
@file       ESPServer.h

Handler for ESP32 WebServer

* @}
***************************************************************************************************/
#ifndef ESP_SERVER_H_
#define ESP_SERVER_H_

/* INCLUDES ***************************************************************************************/
#include <ESPAsyncWebServer.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
* namespace for Methods in Async Server
*/
namespace ESPServer
{
  bool init(bool apModeRequested);   /**< Registers the handlers on the server, depending on the WiFi Mode chosen */
  bool begin(void);                  /**< Initializing of AsyncWebServer, DNS and WiFi capabilities.  */
  bool end(void);                    /**< Disconnects and disables the WebServer */
  bool handleNextRequest(void);      /**< Calls next request on DNS Server */
  AsyncWebServer &getInstance(void); /**< Returns server's instance */
} // namespace ESPServer

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* ESP_SERVER_H */