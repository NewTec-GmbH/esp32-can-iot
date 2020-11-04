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
#include <Pages.h>
#include <DNSServer.h>
#include <SPIFFS.h>
#include <FS.h>
#include <Board.h>
#include <Web_config.h>
#include <CaptivePortal.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

static AsyncWebServer server(WebConfig::WEBSERVER_PORT);
static DNSServer dnsServer;

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
static bool setAPMode();

/* VARIABLES **************************************************************************************/

bool defaultValues = true;
bool reboot = false;
IPAddress serverIP;

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/
bool ESPServer::init(bool apModeRequested)
{
    bool success = true;

    if(apModeRequested)
    {
        CaptivePortal::init(server);
    }
    else
    {
        Pages::init(server);
    }

    return success;
}

/**************************************************************************************************/
bool ESPServer::begin()
{
    bool success = true;
    WebConfig::importConfig();

    if (setAPMode())
    {
        WiFi.softAP(WebConfig::getAP_SSID().c_str(), WebConfig::getAP_PASS().c_str());
        serverIP = WiFi.softAPIP();

        ESPServer::init(true);
    }
    else
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(WebConfig::getSTA_SSID().c_str(), WebConfig::getSTA_PASS().c_str());

        unsigned long startAttempTime = millis();

        while (WiFi.status() != WL_CONNECTED && (millis() - startAttempTime) < WebConfig::WIFI_TIMEOUT_MS)
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

        ESPServer::init(false);
    }

    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);

    if (!dnsServer.start(WebConfig::DNS_PORT, "*", serverIP))
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
static bool setAPMode()
{

    bool apMode = false;

    uint8_t currentBtnState = LOW;
    uint8_t previousBtnState = LOW;
    uint32_t lastDebounceTime = 0;
    const uint8_t DEBOUNCE_DELAY = 50;
    const uint32_t SETUP_TIME = 2000;
    uint32_t startTime = millis();

    while ((millis() - startTime) < SETUP_TIME)
    {
        currentBtnState = Board::wifiModeSelect.read();

        if (currentBtnState != previousBtnState)
        {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
        {
            apMode = currentBtnState;
        }

        previousBtnState = currentBtnState;
    }

    return apMode;
}