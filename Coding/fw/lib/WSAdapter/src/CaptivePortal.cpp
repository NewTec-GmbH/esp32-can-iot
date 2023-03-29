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
@file       CaptivePortal.cpp

Captive Portal for ESP32 WebServer @ref CaptivePortal.h

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "CaptivePortal.h"
#include "Web_Config.h"
#include <SPIFFS.h>
#include "WLAN.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

static bool restartRequested = false; /**<  True if restart has been requested by user */

/**************************************************************************************************/

/**
 *  Processor to save the required credentials incoming from the Webpage
 * 
 *  @param[in] name Name of the parameter
 *  @param[in] value Value of the parameter 
 */
static void credentialsProcessor(const String &name, const String &value);

/**
 *  Captive portal request handler.
 */
class CaptiveRequestHandler : public AsyncWebHandler
{
public:
    /**
     *  Constructs the captive portal request handler.
     */
    CaptiveRequestHandler()
    {
    }

    /**
     *  Destroys the captive portal request handler.
     */
    ~CaptiveRequestHandler()
    {
    }

    /**
     *  Checks whether the request can be handled.
     * 
     *  @param[in] request   Web request
     *  @return If request can be handled, it will return true otherwise false.
     */
    bool canHandle(AsyncWebServerRequest *request) override
    {
        /* The captive portal handles every request. */
        return true;
    }

    /**
     *  Handles the request.
     * 
     *  @param[in] request   Web request, which to handle.
     */
    void handleRequest(AsyncWebServerRequest *request) override
    {
        if (nullptr == request)
        {
            return;
        }
        /** Forces authentication */
        if (!request->authenticate(WebConfig::getWEB_USER().c_str(), WebConfig::getWEB_PASS().c_str()))
        {
            return request->requestAuthentication();
        }

        if (HTTP_POST == request->method())
        {
            if (0 != request->args())
            {
                int params = request->params();
                for (int i = 0; i < params; i++)
                {
                    AsyncWebParameter *p = request->getParam(i);
                    if (nullptr != p)
                    {
                        credentialsProcessor(p->name(), p->value());
                    }
                }
                request->send(SPIFFS, "/setCredentials.html");
                restartRequested = true;
            }
        }
        else if (HTTP_GET == request->method())
        {
            request->send(SPIFFS, "/STACredentials.html");
        }
        else
        {
            request->send(WebConfig::HTTP_BAD_REQUEST, "text/plain", "Error. Bad Request");
        }
    }

    /**
     *  Function tells the server if the Body of the request has to be parsed too. As this website uses a POST Request, body must be parsed.
     * 
     *  @return True if the Body of the request is trivial and should not be parsed. False otherwise.
     */
    bool isRequestHandlerTrivial() override
    {
        return false;
    }

private:
};

/* PUBLIC METHODES ********************************************************************************/

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

static CaptiveRequestHandler gCaptivePortalReqHandler; /**< Instance of Captive Portal Handler */

/* EXTERNAL FUNCTIONS *****************************************************************************/

/**
 *  Registers the Captive Portal handler on the Server.
 * 
 *  @param[in] webServer AsyncWebserver Instance to register to.
 */
void CaptivePortal::init(AsyncWebServer &webServer)
{
    webServer.serveStatic("/js/", SPIFFS, "/js/", "max-age=120");
    webServer.serveStatic("/css/", SPIFFS, "/css/", "max-age=120");
    webServer.serveStatic("/pictures/", SPIFFS, "/pictures/", "max-age = 120");
    webServer.addHandler(&gCaptivePortalReqHandler).setFilter(ON_AP_FILTER);
}

/**
 *  Verify if restart has been requested
 *
 *  @return True if restart has been requested. False otherwise.
 */
bool CaptivePortal::isRestartRequested()
{
    return restartRequested;
}

/* INTERNAL FUNCTIONS *****************************************************************************/

/**
 *  Saves the Credentials given by the user to the Flash Memory
 * 
 *  @param[in] name Name of Argument from Web POST Submit
 *  @param[in] value Value of Argument from Web POST Submit
 */
static void credentialsProcessor(const String &name, const String &value)
{
    if ((name == "STA_SSID") || (name == "STA_Password"))
    {
        wlan::saveConfig(name, value);
    }
}
