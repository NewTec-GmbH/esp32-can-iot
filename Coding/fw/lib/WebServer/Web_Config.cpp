#include <Web_Config.h>

static const String DIRECTORY = "Server";

static String STA_SSID = "";
static String STA_PASSWORD = "";
static String AP_SSID = "ESP32";
static String AP_PASSWORD = "hochschuleulm";
static String WEB_USER = "admin";
static String WEB_PASSWORD = "admin";

void WebConfig::importConfig()
{
    Settings::get(DIRECTORY, "STA_SSID", STA_SSID, "");
    Settings::get(DIRECTORY, "STA_Password", STA_PASSWORD, "");
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