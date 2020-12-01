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
#include "Settings.h"
/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

namespace WebConfig
{
  static const uint32_t DNS_PORT = 53U;
  static const uint32_t WEBSERVER_PORT = 80U;
  static const uint8_t WIFI_MODE_BUTTON = 21U;
  static const uint16_t WIFI_TIMEOUT_MS = 20000;

  String getSTA_SSID();
  String getSTA_PASS();
  String getAP_SSID();
  String getAP_PASS();
  String getWEB_USER();
  String getWEB_PASS();

  void importConfig();
  void saveConfig(const String &key, const String &value);

} // namespace WebConfig

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/
#endif /* WEB_CONFIG_H_ */