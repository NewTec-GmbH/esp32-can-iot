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
#include "Pages.h"
#include "Web_Config.h"
#include <SPIFFS.h>
#include "Settings.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/**
*   Processor for the Webpages, in order to replace the Templates in HTML (%TEMPLATE%) with their correct value.
*   Function given by the AsyncWebServer Library
*   @param [in] var: Webpage to be displayed before replacing the Templates
*   return Webpage with replaced Templates
*/
static String pageProcessor(const String &var);

/**
* Handles the request when the index page is requested
*/
static void indexPage(AsyncWebServerRequest *request);

/**
* Handles the request when the error page is requested
*/
static void errorPage(AsyncWebServerRequest *request);

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/
/**************************************************************************************************/
void Pages::init(AsyncWebServer &webServer)
{
    webServer.on("/", HTTP_GET, indexPage);
    webServer.serveStatic("/js/", SPIFFS, "/js/", "max-age=120");
    webServer.serveStatic("/css/", SPIFFS, "/css/", "max-age=120");
    webServer.serveStatic("/pictures/", SPIFFS, "/pictures/", "max-age = 120");

    webServer.onNotFound(errorPage);
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
        temp = WebConfig::getSTA_SSID();
    }
    else if (var == "AP_SSID")
    {
       temp = WebConfig::getAP_SSID();
    }
    else if (var == "AP_PASS")
    {
        temp = WebConfig::getAP_PASS();
    }
    else if (var == "SERVER_USER")
    {
        temp = WebConfig::getWEB_USER();
    }
    else if (var == "SERVER_PASS")
    {
        temp = WebConfig::getWEB_PASS();
    }
    return temp;
}

static void indexPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }

    if (!request->authenticate(WebConfig::getWEB_USER().c_str(), WebConfig::getWEB_PASS().c_str()))
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

    if (!request->authenticate(WebConfig::getWEB_USER().c_str(), WebConfig::getWEB_PASS().c_str()))
    {
        return request->requestAuthentication();
    }

    request->send(WebConfig::HTTP_NOT_FOUND, "text/plain", "Not Found");
}