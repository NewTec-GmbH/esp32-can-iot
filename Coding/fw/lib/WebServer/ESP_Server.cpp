/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Webserver
@{
@file       ESPServer.cpp

Handler for ESP32 WebServer. @ref ESPServer.h

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "ESP_Server.h"
#include <SPIFFS.h>
#include "Board.h"
#include "Web_config.h"
#include "Pages.h"
#include "CaptivePortal.h"
#include "WLAN.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/**
* Registers the handlers on the server, depending on the WiFi Mode chosen
* @param bool apModeRequested  determines if AP Mode or STA Mode are requested, to choose the correct handlers
* return success
*/
static bool initPages(bool apModeRequested);

/* VARIABLES **************************************************************************************/
static AsyncWebServer webServer(WebConfig::WEBSERVER_PORT); /**< Instance of AsyncWebServer*/

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
*   Initializing of AsyncWebServer, DNS and WiFi capabilities. 
*   return success
*/
bool ESPServer::begin()
{
    bool success = true;

    if (!wlan::begin())
    {
        success = false;
    }
    else if (wlan::getAP_MODE())
    {
        if (!initPages(true))
        {
            success = false;
        }
    }
    else
    {
        if (!initPages(false))
        {
            success = false;
        }
    }

    if (!SPIFFS.begin())
    {
        success = false;
    }

    webServer.begin();

    return success;
}

/**************************************************************************************************/

/**
*   Disconnects and disables the WebServer
*/
bool ESPServer::end()
{
    webServer.end();
    SPIFFS.end();
    return WiFi.disconnect(true, true);
}


/**************************************************************************************************/

/*
*   Returns True is Restart is requested by the Captive Portal
*/
bool ESPServer::isRestartRequested()
{
    return CaptivePortal::isRestartRequested();
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

/**************************************************************************************************/

/*
*   Initializes the corresponding Webpages, depending on the WiFi Mode specified by user
*/
bool initPages(bool apModeRequested)
{
    bool success = true;

    if (apModeRequested)
    {
        CaptivePortal::init(webServer);
    }
    else
    {
        Pages::init(webServer);     
    }

    return success;
}
