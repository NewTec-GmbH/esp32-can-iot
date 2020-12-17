/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
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
static bool restartRequested = false; /**<  Variable to call Restart */
/**************************************************************************************************/
/**
*  Processor to save the required credentials incoming from the Webpage
* @param name Name of the parameter
* @param value Value of the parameter 
*/
static void credentialsProcessor(String name, String value);

/**
* Captive portal request handler.
*/
class CaptiveRequestHandler : public AsyncWebHandler
{
public:
    /**
    * Constructs the captive portal request handler.
    */
    CaptiveRequestHandler()
    {
    }

    /**
    * Destroys the captive portal request handler.
    */
    ~CaptiveRequestHandler()
    {
    }

    /**
    * Checks whether the request can be handled.
    * @param[in] request   Web request
    * @return If request can be handled, it will return true otherwise false.
    */
    bool canHandle(AsyncWebServerRequest *request) override
    {
        /* The captive portal handles every request. */
        return true;
    }

    /**
    * Handles the request.
    * @param[in] request   Web request, which to handle.
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
            if (request->args() != 0)
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
* @brief Function tells the server if the Body of the request has to be parsed too. As this website uses a POST Request, body must be parsed.
* 
* @return true The Body is trivial and will not be parsed.
* @return false The Body is important/not trivial and must be parsed.
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
static CaptiveRequestHandler CaptivePortalReqHandler; /**< Instance of Handler */

/* EXTERNAL FUNCTIONS *****************************************************************************/
/**
 * @brief Links the Captive Portal handler to the Server
 * 
 * @param server AsyncWebserver Instance to initialize to
 */
void CaptivePortal::init(AsyncWebServer &webServer)
{
    webServer.serveStatic("/css/w3.css", SPIFFS, "/css/w3.css", "max-age = 3600");
    webServer.serveStatic("/pictures/NewTec_Logo.png", SPIFFS, "/pictures/NewTec_Logo.png", "max-age = 3600");
    webServer.addHandler(&CaptivePortalReqHandler).setFilter(ON_AP_FILTER);
}

/**
 * @brief return true if restart has been requested 
 */
bool CaptivePortal::isRestartRequested()
{
    return restartRequested;
}

/* INTERNAL FUNCTIONS *****************************************************************************/

/**
 * @brief Saves the Credentials given by the user to the Flash Memory
 * 
 * @param name Key to store the Data
 * @param value Data to be stored
 */
static void credentialsProcessor(String name, String value)
{
    if (name == "STA_SSID" ||
        name == "STA_Password")
    {
        wlan::saveConfig(name, value);
    }
}
