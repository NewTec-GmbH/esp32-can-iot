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
            if (request->args() != 0)
            {
                request->send(200, "plain/text", "\n POST - With Params \n");

                int params = request->params();
                for (int i = 0; i < params; i++)
                {
                    AsyncWebParameter *p = request->getParam(i);
                }
            }
            else
            {
                request->send(200, "plain/text", "\n POST - No params \n");
            }
        }
        else if (HTTP_GET == request->method())
        {
            request->send(SPIFFS, "/STACredentials.html", String(), false, captivePageProcessor);
            if (request->args() != 0)
            {
                request->send(200, "plain/text", "\n GET - With Params \n");
            }
            else
            {
                request->send(200, "plain/text", "\n GET - No params \n");
            }
        }
        else
        {
            request->send(400, "plain/text", "\n Error. Bad Request");
        }
    }

    bool isRequestHandlerTrivial() override
    {
        return false;
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
static CaptiveRequestHandler CaptivePortalReqHandler; /**< Instance of Handler */
static bool restartRequested = false; /**<  Variable to call Restart */

/* EXTERNAL FUNCTIONS *****************************************************************************/
/**
 * @brief Links the Captive Portal handler to the Server
 * 
 * @param server AsyncWebserver Instance to initialize to
 */
void CaptivePortal::init(AsyncWebServer &server)
{
    server.addHandler(&CaptivePortalReqHandler).setFilter(ON_AP_FILTER);
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
 * Request restart.
 */
static void reqRestart()
{
    restartRequested = true;
}

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
        WebConfig::saveConfig(name, value);
    }
}
