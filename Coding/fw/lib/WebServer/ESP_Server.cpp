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
static AsyncWebServer server(WEBSERVER_PORT);
static DNSServer dnsServer;
static Preferences flash;

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
static void notFound(AsyncWebServerRequest *request);
static String pageProcessor(const String &var);
static void credentialsProcessor(String name, String value);
static void importConfig();

/* VARIABLES **************************************************************************************/

bool defaultValues = true;
char STA_SSID[32] = "";
char STA_PASSWORD[32] = "";
char AP_SSID[32] = "";
char AP_PASSWORD[32] = "";
char WEB_USER[32] = "";
char WEB_PASSWORD[32] = "";
bool reboot = false;

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/
void ESPServer::init()
{
    importConfig();
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
}

/**************************************************************************************************/
void ESPServer::begin()
{
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    SPIFFS.begin();
    server.begin();
}

/**************************************************************************************************/
void ESPServer::end()
{
    server.end();
    SPIFFS.end();
    dnsServer.stop();
    WiFi.disconnect(true, true);
}

/**************************************************************************************************/
void ESPServer::handle()
{
    dnsServer.processNextRequest();
    if (reboot)
    {
        ESP.restart();
    }
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
static void importConfig()
{
    flash.begin("Startup", false);

    strcpy(STA_SSID, flash.getString("STA_SSID", "").c_str());
    strcpy(STA_PASSWORD, flash.getString("STA_PASSWORD", "").c_str());
    strcpy(AP_SSID, flash.getString("AP_SSID", "ESP32").c_str());
    strcpy(AP_PASSWORD, flash.getString("AP_PASSWORD", "hochschuleulm").c_str());
    strcpy(WEB_USER, flash.getString("WEB_USER", "admin").c_str());
    strcpy(WEB_PASSWORD, flash.getString("WEB_PASSWORD", "admin").c_str());

    flash.end();
}