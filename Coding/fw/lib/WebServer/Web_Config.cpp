#include <Web_Config.h>

static const String DIRECTORY = "Server";

static String STA_SSID = "";
static String STA_PASSWORD = "";
static String AP_SSID = "";
static String AP_PASSWORD = "";
static String WEB_USER = "";
static String WEB_PASSWORD = "";

void WebConfig::importConfig()
{
    Settings::get(DIRECTORY, "STA_SSID", STA_SSID, "OnePlus 6");
    Settings::get(DIRECTORY, "STA_Password", STA_PASSWORD, "alejoreyes");
    Settings::get(DIRECTORY, "AP_SSID", AP_SSID, "ESP32");
    Settings::get(DIRECTORY, "AP_Password", AP_PASSWORD, "hochschuleulm");
    Settings::get(DIRECTORY, "Server_User", WEB_USER, "admin");
    Settings::get(DIRECTORY, "Server_Password", WEB_PASSWORD, "admin");
}

String WebConfig::getSTA_SSID()
{
    return STA_SSID;
}

String WebConfig::getSTA_PASS()
{
    return STA_PASSWORD;
}

String WebConfig::getAP_SSID()
{
    return AP_SSID;
}

String WebConfig::getAP_PASS()
{
    return AP_PASSWORD;
}

String WebConfig::getWEB_USER()
{
    return WEB_USER;
}

String WebConfig::getWEB_PASS()
{
    return WEB_PASSWORD;
}

void WebConfig::saveConfig(const String &key, const String &value)
{
    Settings::save(DIRECTORY, key, value);
}