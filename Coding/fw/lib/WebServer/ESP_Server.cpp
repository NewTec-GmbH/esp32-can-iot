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
@file       ESP_Server.cpp

Handler for ESP32 WebServer. @ref ESP_Server.h

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
 *  @param[in] apModeRequested If true, the webpages for AP mode are initialized. 
 *                              Otherwise are the Station Mode Pages initialized.
 *  @return success
 */
static bool initPages(bool apModeRequested);

/* VARIABLES **************************************************************************************/

static AsyncWebServer gWebServer(WebConfig::WEBSERVER_PORT); /**< Instance of AsyncWebServer*/

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
 *  Initialization of AsyncWebServer, DNS and WiFi capabilities.
 * 
 *  @return success
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

    gWebServer.begin();

    return success;
}

/**************************************************************************************************/

/**
 *  Disconnects and disables the WebServer
 *
 *  @return success
 */
bool ESPServer::end()
{
    gWebServer.end();
    SPIFFS.end();
    return WiFi.disconnect(true, true);
}

/**************************************************************************************************/

/**
 *  Verify if restart has been requested.
 *  
 *  @return True is restart is requested by the Captive Portal. False otherwise.
 */
bool ESPServer::isRestartRequested()
{
    return CaptivePortal::isRestartRequested();
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

static bool initPages(bool apModeRequested)
{
    bool success = true;

    if (apModeRequested)
    {
        CaptivePortal::init(gWebServer);
    }
    else
    {
        Pages::init(gWebServer);
    }

    return success;
}
