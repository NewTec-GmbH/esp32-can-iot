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
#include <DNSServer.h>
#include "Web_config.h"

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
  namespace
  {
    static AsyncWebServer webServer(WebConfig::WEBSERVER_PORT); /**< Instance of AsyncWebServer*/
    static DNSServer dnsServer;                                 /**< Instance of DNS Server*/
  }                                                             // namespace
  bool begin(void);                                             /**< Initializing of AsyncWebServer, DNS and WiFi capabilities.  */
  bool end(void);                                               /**< Disconnects and disables the WebServer */
  bool handleNextRequest(void);                                 /**< Calls next request on DNS Server */
  bool isRestartRequested(void);                                /**< Returns true if restart requested by Web Server */

  // namespace
} // namespace ESPServer

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* ESP_SERVER_H */