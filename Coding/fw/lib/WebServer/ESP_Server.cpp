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
#include <ESP_Server.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/
const uint32_t DNS_PORT = 53U;
const uint32_t WEBSERVER_PORT = 80U;
const uint8_t WIFI_MODE_BUTTON = 21U;
static AsyncWebServer server(WEBSERVER_PORT);
static DNSServer dnsServer;
static Preferences flash;
const uint16_t WIFI_TIMEOUT_MS = 20000;

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
static void notFound(AsyncWebServerRequest *request);
static String pageProcessor(const String &var);
static void credentialsProcessor(String name, String value);
static bool importConfig();
static bool setSTAMode();

/* VARIABLES **************************************************************************************/

bool defaultValues = true;
char STA_SSID[32] = "";
char STA_PASSWORD[32] = "";
char AP_SSID[32] = "";
char AP_PASSWORD[32] = "";
char WEB_USER[32] = "";
char WEB_PASSWORD[32] = "";
bool reboot = false;
IPAddress serverIP;

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/
bool ESPServer::init()
{
    bool success = false;
    if (importConfig())
    {
        pinMode(WIFI_MODE_BUTTON, INPUT); /* @todo  IO Class */

        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
            if (!request->authenticate(WEB_USER, WEB_PASSWORD))
                return request->requestAuthentication();
            request->send(SPIFFS, "/index.html", String(), false, pageProcessor);
        });

        server.on("/css/w3.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            request->send(SPIFFS, "/css/w3.css", "text/css");
        });

        server.on("/pictures/NewTec_Logo.png", HTTP_GET, [](AsyncWebServerRequest *request) {
            request->send(SPIFFS, "/pictures/NewTec_Logo.png", "image/png");
        });

        server.on("/STACredentials.html", HTTP_GET, [](AsyncWebServerRequest *request) {
            if (!request->authenticate(WEB_USER, WEB_PASSWORD))
                return request->requestAuthentication();
            request->send(SPIFFS, "/STACredentials.html", String(), false, pageProcessor);
        });

        server.on("/APCredentials.html", HTTP_GET, [](AsyncWebServerRequest *request) {
            if (!request->authenticate(WEB_USER, WEB_PASSWORD))
                return request->requestAuthentication();
            request->send(SPIFFS, "/APCredentials.html", String(), false, pageProcessor);
        });

        server.on("/WEBCredentials.html", HTTP_GET, [](AsyncWebServerRequest *request) {
            if (!request->authenticate(WEB_USER, WEB_PASSWORD))
                return request->requestAuthentication();
            request->send(SPIFFS, "/WEBCredentials.html", String(), false, pageProcessor);
        });

        server.on("/setCredentials.html", HTTP_GET, [](AsyncWebServerRequest *request) {
            int params = request->params();
            for (int i = 0; i < params; i++)
            {
                AsyncWebParameter *p = request->getParam(i);
                Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
                credentialsProcessor(p->name(), p->value());
            }
            if (!request->authenticate(WEB_USER, WEB_PASSWORD))
                return request->requestAuthentication();
            request->send(SPIFFS, "/setCredentials.html", String(), false, pageProcessor);
        });

        server.onNotFound(notFound);

        success = true;
    }

    return success;
}

/**************************************************************************************************/
bool ESPServer::begin()
{
    bool success = true;

    if (setSTAMode())
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(STA_SSID, STA_PASSWORD);

        unsigned long startAttempTime = millis();

        while (WiFi.status() != WL_CONNECTED && (millis() - startAttempTime) < WIFI_TIMEOUT_MS)
        {
        }

        if (WiFi.status() != WL_CONNECTED)
        {
            success = false;
        }
        else
        {
            serverIP = WiFi.localIP();
        }
    }
    else
    {
        WiFi.softAP(AP_SSID, AP_PASSWORD);
        serverIP = WiFi.softAPIP();
    }

    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);

    if (!dnsServer.start(DNS_PORT, "*", serverIP))
    {
        success = false;
    }
    else if (!SPIFFS.begin())
    {
        success = false;
    }

    server.begin();

    return success;
}

/**************************************************************************************************/
bool ESPServer::end()
{
    server.end();
    SPIFFS.end();
    dnsServer.stop();
    return WiFi.disconnect(true, true);
}

/**************************************************************************************************/
bool ESPServer::handleNextRequest()
{
    dnsServer.processNextRequest();
    return reboot;
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/
/**************************************************************************************************/
static void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not Found");
}

/**************************************************************************************************/
static String pageProcessor(const String &var)
{
    String temp;

    if (var == "STATION_SSID")
    {
        temp = STA_SSID;
    }
    else if (var == "AP_SSID")
    {
        temp = AP_SSID;
    }
    else if (var == "AP_PASS")
    {
        temp = AP_PASSWORD;
    }
    else if (var == "SERVER_USER")
    {
        temp = WEB_USER;
    }
    else if (var == "SERVER_PASS")
    {
        temp = WEB_PASSWORD;
    }
    return temp;
}

/**************************************************************************************************/
static void credentialsProcessor(String name, String value)
{
    flash.begin("Startup", false);
    if (name == "STA_SSID")
    {
        flash.putString("STA_SSID", value);
    }
    else if (name == "STA_Password")
    {
        flash.putString("STA_PASSWORD", value);
    }
    else if (name == "AP_SSID")
    {
        flash.putString("AP_SSID", value);
    }
    else if (name == "AP_Password")
    {
        flash.putString("AP_PASSWORD", value);
    }
    else if (name == "Server_User")
    {
        flash.putString("WEB_USER", value);
    }
    else if (name == "Server_Password")
    {
        flash.putString("WEB_PASSWORD", value);
    }
    flash.end();
    reboot = true;
}

/**************************************************************************************************/
static bool importConfig()
{
    bool success = false;
    if (flash.begin("Startup", false))
    {
        strcpy(STA_SSID, flash.getString("STA_SSID", "").c_str());
        strcpy(STA_PASSWORD, flash.getString("STA_PASSWORD", "").c_str());
        strcpy(AP_SSID, flash.getString("AP_SSID", "ESP32").c_str());
        strcpy(AP_PASSWORD, flash.getString("AP_PASSWORD", "hochschuleulm").c_str());
        strcpy(WEB_USER, flash.getString("WEB_USER", "admin").c_str());
        strcpy(WEB_PASSWORD, flash.getString("WEB_PASSWORD", "admin").c_str());
        flash.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/
static bool setSTAMode()
{
    bool staMode = false;

    return staMode;
}