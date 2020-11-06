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
static void handleBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

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

        Serial.println("URL: ");
        Serial.println(request->url());
        Serial.println("Method: ");

        if (request->method() == 1)
        {
            Serial.println("GET");
        }
        else if (request->method() == 2)
        {
            Serial.println("POST");
        }
        else
        {
            Serial.println("Other");
        }

        Serial.println("Content Type: ");
        Serial.println(request->contentType());
        Serial.println("Content Length: ");
        Serial.println(request->contentLength());
        String temp = request->url();
        Serial.println(request->urlDecode(temp));
        Serial.println(temp);

        if (HTTP_POST == request->method())
        {
            if (request->args() != 0)
            {
                request->send(200, "plain/text", "\n POST - With Params \n");
                Serial.println("SUCCESS");

                int params = request->params();
                for (int i = 0; i < params; i++)
                {
                    AsyncWebParameter *p = request->getParam(i);

                    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
                }
            }
            else
            {
                request->send(200, "plain/text", "\n POST - No params \n");
                Serial.println("POST - No Params");
            }
            const String ssid = request->arg("ssid");
            Serial.println(ssid);
        }
        else if (HTTP_GET == request->method())
        {
            request->send(SPIFFS, "/STACredentials.html", String(), false, captivePageProcessor);
            if (request->args() != 0)
            {
                request->send(200, "plain/text", "\n GET - With Params \n");
                Serial.println("Get-With Params");
            }
            else
            {
                request->send(200, "plain/text", "\n GET - No params \n");
                Serial.println("GET - No Params");
            }
            const String ssid = request->arg("ssid");
            Serial.println(ssid);
        }
        else
        {
            request->send(400, "plain/text", "\n Error. Bad Request");
        }

        Serial.println();
        Serial.println();
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
static CaptiveRequestHandler CaptivePortalReqHandler;
static bool restartRequested = false;

/* EXTERNAL FUNCTIONS *****************************************************************************/

void CaptivePortal::init(AsyncWebServer &server)
{
    server.addHandler(&CaptivePortalReqHandler).setFilter(ON_AP_FILTER);
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

void handleBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    if (!index)
    {
        Serial.printf("BodyStart: %u B\n", total);
    }
    for (size_t i = 0; i < len; i++)
    {
        Serial.write(data[i]);
    }
    if (index + len == total)
    {
        Serial.printf("BodyEnd: %u B\n", total);
    }
}