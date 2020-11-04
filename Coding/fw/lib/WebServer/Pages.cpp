/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Webserver
@{
@file       Pages.cpp

Web Pages for ESP32 WebServer @ref Pages.h

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include <Pages.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/
const char *DIRECTORY = "Server";

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
static String pageProcessor(const String &var);
static void credentialsProcessor(String name, String value);
static void indexPage(AsyncWebServerRequest *request);
static void staPage(AsyncWebServerRequest *request);
static void apPage(AsyncWebServerRequest *request);
static void srvPage(AsyncWebServerRequest *request);
static void setCredentialsPage(AsyncWebServerRequest *request);
static void errorPage(AsyncWebServerRequest *request);

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/
/**************************************************************************************************/
void Pages::init(AsyncWebServer &server)
{
    server.on("/", HTTP_GET, indexPage);
    server.on("/STACredentials.html", HTTP_GET, staPage);
    server.on("/APCredentials.html", HTTP_GET, apPage);
    server.on("/WEBCredentials.html", HTTP_GET, srvPage);
    server.on("/setCredentials.html", HTTP_GET, setCredentialsPage);


    server.serveStatic("/css/w3.css", SPIFFS, "/css/w3.css", "max-age = 3600");
    server.serveStatic("/pictures/NewTec_Logo.png", SPIFFS, "/pictures/NewTec_Logo.png", "max-age = 3600");

    server.onNotFound(errorPage);
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/
static String pageProcessor(const String &var)
{
    String temp;

    if (var == "STATION_SSID")
    {
        temp = WebConfig::STA_SSID;
    }
    else if (var == "AP_SSID")
    {
        temp = WebConfig::AP_SSID;
    }
    else if (var == "AP_PASS")
    {
        temp = WebConfig::AP_PASSWORD;
    }
    else if (var == "SERVER_USER")
    {
        temp = WebConfig::WEB_USER;
    }
    else if (var == "SERVER_PASS")
    {
        temp = WebConfig::WEB_PASSWORD;
    }
    return temp;
}

static void credentialsProcessor(String name, String value)
{    
    if (name == "STA_SSID" ||
        name == "STA_Password" ||
        name == "AP_SSID" ||
        name == "AP_Password" ||
        name == "Server_User"||
        name == "Server_Password"    
    )
    {
        Settings::save(DIRECTORY, name, value);
    }   
}

static void indexPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }

    if (!request->authenticate(WebConfig::WEB_USER, WebConfig::WEB_PASSWORD))
    {
        return request->requestAuthentication();
    }

    return request->send(SPIFFS, "/index.html", String(), false, pageProcessor);
}

static void staPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }

    if (!request->authenticate(WebConfig::WEB_USER, WebConfig::WEB_PASSWORD))
    {
        return request->requestAuthentication();
    }

    return request->send(SPIFFS, "/STACredentials.html", String(), false, pageProcessor);
}

static void apPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }

    if (!request->authenticate(WebConfig::WEB_USER, WebConfig::WEB_PASSWORD))
    {
        return request->requestAuthentication();
    }

    return request->send(SPIFFS, "/APCredentials.html", String(), false, pageProcessor);
}

static void srvPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }

    if (!request->authenticate(WebConfig::WEB_USER, WebConfig::WEB_PASSWORD))
    {
        return request->requestAuthentication();
    }

    return request->send(SPIFFS, "/WEBCredentials.html", String(), false, pageProcessor);
}

static void setCredentialsPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }

    if (!request->authenticate(WebConfig::WEB_USER, WebConfig::WEB_PASSWORD))
    {
        return request->requestAuthentication();
    }

    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
        credentialsProcessor(p->name(), p->value());
    }

    return request->send(SPIFFS, "/setCredentials.html", String(), false, pageProcessor);
}

static void errorPage(AsyncWebServerRequest *request)
{
    if (nullptr == request)
    {
        return;
    }
    
    request->send(404, "text/plain", "Not Found");
}