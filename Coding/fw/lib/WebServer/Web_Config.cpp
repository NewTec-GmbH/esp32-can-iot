#include <Web_Config.h>

void WebConfig::importConfig()
    {
        Settings::get(DIRECTORY, "STA_SSID", STA_SSID,"");
        Settings::get(DIRECTORY, "STA_Password", STA_PASSWORD,"");
        Settings::get(DIRECTORY, "AP_SSID", AP_SSID,"ESP32");
        Settings::get(DIRECTORY, "AP_Password", AP_PASSWORD,"hochschuleulm");
        Settings::get(DIRECTORY, "Server_User", WEB_USER,"admin");
        Settings::get(DIRECTORY, "Server_Password", WEB_PASSWORD,"admin");
    }

    void WebConfig::saveConfig(const String &key, const String &value)
    {
        Settings::save(DIRECTORY, key, value);
    }