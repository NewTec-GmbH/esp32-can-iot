/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Webserver
@{
@file       Pages.h

Web Pages for ESP32 WebServer

* @}
***************************************************************************************************/
#ifndef PAGES_H_
#define PAGES_H_

/* INCLUDES ***************************************************************************************/
#include <ESPAsyncWebServer.h>
#include <Web_Config.h>
#include <SPIFFS.h>
#include <stdint.h>
#include <Settings.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/
namespace Pages
{
    /**
    * Initialize all web pages and register them on the web server.
    * @param[in] srv   Web server
    */
    void init(AsyncWebServer &server);

    /**
    * Error web page used in case a requested path was not found.
    * @param[in] request   Web request
    */
    void error(AsyncWebServerRequest *request);

} // namespace Pages

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/

#endif /* PAGES_H_ */