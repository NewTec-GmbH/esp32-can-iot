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
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <FS.h>
#include <Preferences.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

namespace ESPServer
{
    void init();
    void begin(void);
    void end(void);
    void handle(void);
    AsyncWebServer &getInstance(void);
}


/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* ESP_SERVER_H */