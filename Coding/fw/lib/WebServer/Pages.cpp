/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Webserver
@{
@file       Pages.cpp

Web Pages for ESP32 WebServer @ref Pages.h

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include <Pages.h>
#include <Web_Config.h>
#include <SPIFFS.h>
#include <Settings.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
static String pageProcessor(const String &var);
static void indexPage(AsyncWebServerRequest *request);
static void errorPage(AsyncWebServerRequest *request);

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/
/**************************************************************************************************/
void Pages::init(AsyncWebServer &server)
{
    server.on("/", HTTP_GET, indexPage);

    server.serveStatic("/css/w3.css", SPIFFS, "/css/w3.css", "max-age = 3600");
    server.serveStatic("/pictures/NewTec_Logo.png", SPIFFS, "/pictures/NewTec_Logo.png", "max-age = 3600");

    server.onNotFound(errorPage);
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/
static String pageProcessor(const String &var)
{
    String temp;

    if (var == "STATION_SSID")
    {
        temp = WebConfig::STA_SSID;
    }
    else if (var == "AP_SSID")
    {
        temp = WebConfig::AP_SSID;
    }
    else if (var == "AP_PASS")
    {
        temp = WebConfig::AP_PASSWORD;
    }
    else if (var == "SERVER_USER")
    {
        temp = WebConfig::WEB_USER;
    }
    else if (var == "SERVER_PASS")
    {
        temp = WebConfig::WEB_PASSWORD;
    }
    return temp;
}

static void indexPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }

    if (!request->authenticate(WebConfig::WEB_USER.c_str(), WebConfig::WEB_PASSWORD.c_str()))
    {
        return request->requestAuthentication();
    }

    return request->send(SPIFFS, "/index.html", String(), false, pageProcessor);
}

static void errorPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }

    if (!request->authenticate(WebConfig::WEB_USER.c_str(), WebConfig::WEB_PASSWORD.c_str()))
    {
        return request->requestAuthentication();
    }

    request->send(404, "text/plain", "Not Found");
}