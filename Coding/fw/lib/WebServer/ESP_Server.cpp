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
static AsyncWebServer server(WEBSERVER_PORT);
static DNSServer dnsServer;

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
static void notFound(AsyncWebServerRequest *request);
static String pageProcessor(const String &var);
static void credentialsProcessor(String name, String value);

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/
void ESPServer::init()
{
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
    WiFi.softAP(AP_SSID,AP_PASSWORD);
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
    WiFi.disconnect(true,true);
}

/**************************************************************************************************/
void ESPServer::handle()
{
    dnsServer.processNextRequest();
    if (reboot)
    {
        delay(5000);
        ESP.restart();
    }
}

/**************************************************************************************************/
static void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not Found");
}

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

static void credentialsProcessor(String name, String value)
{
    if (name == "STA_SSID")
    {
        strcpy(STA_SSID, value.c_str());
    }
    else if (name == "STA_Password")
    {
        strcpy(STA_PASSWORD, value.c_str());
    }
    else if (name == "AP_SSID")
    {
        strcpy(AP_SSID, value.c_str());
    }
    else if (name == "AP_Password")
    {
        strcpy(AP_PASSWORD, value.c_str());
    }
    else if (name == "Server_User")
    {
        strcpy(WEB_USER, value.c_str());
    }
    else if (name == "Server_Password")
    {
        strcpy(WEB_PASSWORD, value.c_str());
    }

    reboot = false;
}