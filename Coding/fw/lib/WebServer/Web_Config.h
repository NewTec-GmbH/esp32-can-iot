/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Webserver
@{
@file       Web_config.h

Configuration of ESP32 WebServer

* @}
***************************************************************************************************/
#ifndef WEB_CONFIG_H_
#define WEB_CONFIG_H_

/* INCLUDES ***************************************************************************************/
#include <Settings.h>
/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

const char *DIRECTORY = "Server";

namespace WebConfig
{
    const uint32_t DNS_PORT = 53U;
    const uint32_t WEBSERVER_PORT = 80U;
    const uint8_t WIFI_MODE_BUTTON = 21U;
    const uint16_t WIFI_TIMEOUT_MS = 20000;

    String STA_SSID = "";
    String STA_PASSWORD = "";
    String AP_SSID = "";
    String AP_PASSWORD = "";
    String WEB_USER = "";
    String WEB_PASSWORD = "";

    void importConfig()
    {
        Settings::get(DIRECTORY, "STA_SSID", STA_SSID,"");
        Settings::get(DIRECTORY, "STA_Password", STA_PASSWORD,"");
        Settings::get(DIRECTORY, "AP_SSID", AP_SSID,"ESP32");
        Settings::get(DIRECTORY, "AP_Password", AP_PASSWORD,"hochschuleulm");
        Settings::get(DIRECTORY, "Server_User", WEB_USER,"admin");
        Settings::get(DIRECTORY, "Server_Password", WEB_PASSWORD,"admin");
    }

    void saveConfig(const String &key, const String &value)
    {
        Settings::save(DIRECTORY, key, value);
    }

} // namespace WebConfig

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/
#endif /* WEB_CONFIG_H_ */