/***************************************************************************************************
BSD 3-Clause License


Copyright (c) 2020-2021, NewTec GmbH - www.newtec.de
All rights reserved.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:


1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.


2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.


3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#include "WLAN.h"
#include "Websocket.h"

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
    websocket::init(webServer);
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
        temp = wlan::getSTA_SSID();
    }
    else if (var == "AP_SSID")
    {
        temp = wlan::getAP_SSID();
    }
    else if (var == "AP_PASS")
    {
        temp = wlan::getAP_PASS();
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