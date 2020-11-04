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
namespace WebConfig
{
    const uint32_t DNS_PORT = 53U;
    const uint32_t WEBSERVER_PORT = 80U;
    const uint8_t WIFI_MODE_BUTTON = 21U;
    const uint16_t WIFI_TIMEOUT_MS = 20000;

    const char STA_SSID[32] = "";
    const char STA_PASSWORD[32] = "";
    const char AP_SSID[32] = "";
    const char AP_PASSWORD[32] = "";
    const char WEB_USER[32] = "";
    const char WEB_PASSWORD[32] = "";

} // namespace WebConfig

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/
#endif /* WEB_CONFIG_H_ */