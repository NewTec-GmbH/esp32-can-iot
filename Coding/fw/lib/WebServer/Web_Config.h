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

static const String DIRECTORY = "Server";

namespace WebConfig
{
    const uint32_t DNS_PORT = 53U;
    const uint32_t WEBSERVER_PORT = 80U;
    const uint8_t WIFI_MODE_BUTTON = 21U;
    const uint16_t WIFI_TIMEOUT_MS = 20000;

    static String STA_SSID = "";
    static String STA_PASSWORD = "";
    static String AP_SSID = "";
    static String AP_PASSWORD = "";
    static String WEB_USER = "";
    static String WEB_PASSWORD = "";

    void importConfig();
    void saveConfig(const String &key, const String &value);

} // namespace WebConfig

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/
#endif /* WEB_CONFIG_H_ */