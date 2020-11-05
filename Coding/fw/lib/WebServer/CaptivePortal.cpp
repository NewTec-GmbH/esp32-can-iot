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
#include <CaptivePortal.h>
#include <Web_Config.h>
#include <SPIFFS.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/
static void reqRestart();                                    /*< Changes the value of restartRequested to True*/
static void credentialsProcessor(String name, String value); /*< Processor to save the required credentials */

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
            int params = request->params();
            for (int i = 0; i < params; i++)
            {
                AsyncWebParameter *p = request->getParam(i);
                Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
                credentialsProcessor(p->name(), p->value());
            }
            request->send(200, "plain/text", "Ok.");
            reqRestart();
        }
        else if (HTTP_GET == request->method())
        {
            request->send(SPIFFS, "/STACredentials.html", String(), false, captivePageProcessor);
        }
        else
        {
            request->send(400, "plain/text", "Error. Bad Request");
        }
    }

private:
    static String captivePageProcessor(const String &var)
    {
        String temp;
        return temp;
    }
};

/* PUBLIC METHODES ********************************************************************************/

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
static CaptiveRequestHandler CaptivePortalReqHandler;
static bool restartRequested = false;

/* EXTERNAL FUNCTIONS *****************************************************************************/

void CaptivePortal::init(AsyncWebServer &server)
{
    server.serveStatic("/css/w3.css", SPIFFS, "/css/w3.css", "max-age = 3600");
    server.serveStatic("/pictures/NewTec_Logo.png", SPIFFS, "/pictures/NewTec_Logo.png", "max-age = 3600");
    server.addHandler(&CaptivePortalReqHandler).setFilter(ON_AP_FILTER);

    return;
}

bool CaptivePortal::isRestartRequested()
{
    return restartRequested;
}

/* INTERNAL FUNCTIONS *****************************************************************************/

/**
 * Request restart.
 */
static void reqRestart()
{
    restartRequested = true;
}

static void credentialsProcessor(String name, String value)
{
    if (name == "STA_SSID" ||
        name == "STA_Password" ||
        name == "AP_SSID" ||
        name == "AP_Password" ||
        name == "Server_User" ||
        name == "Server_Password")
    {
        WebConfig::saveConfig(name, value);
    }
}