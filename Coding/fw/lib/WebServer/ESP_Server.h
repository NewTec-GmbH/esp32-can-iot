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

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/
static const uint32_t DNS_PORT = 53U;
static const uint32_t WEBSERVER_PORT = 80U;
static char STA_SSID[32] = "";
static char STA_PASSWORD[32] = "";
static char AP_SSID[32] = "ESP32";
static char AP_PASSWORD[32] = "hochschuleulm";
static char WEB_USER[32] = "admin";
static char WEB_PASSWORD[32] = "admin";
static bool reboot = false; 

namespace ESPServer
{
    void init(void);
    void begin(void);
    void end(void);
    void handle(void);
    AsyncWebServer &getInstance(void);
}


/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* ESP_SERVER_H */