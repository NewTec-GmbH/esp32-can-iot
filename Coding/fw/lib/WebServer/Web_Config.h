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
  static const uint32_t DNS_PORT = 53U;          /**< DNS Port */
  static const uint32_t WEBSERVER_PORT = 80U;    /**< HTTP Port */
  static const uint16_t WIFI_TIMEOUT_MS = 20000; /**< Maximum wait time to establish the WiFi connection */

  String &getSTA_SSID(); /**< Returns saved Station SSID */
  String &getSTA_PASS(); /**< Returns saved Station Password */
  String &getAP_SSID();  /**< Returns saved Access Point SSID */
  String &getAP_PASS();  /**< Returns saved Access Point Password */
  String &getWEB_USER(); /**< Returns saved Webserver Username */
  String &getWEB_PASS(); /**< Returns saved Webserver Password */

  void importConfig();                                     /**< Loads the saved configuration from the flash memory */
  void saveConfig(const String &key, const String &value); /**< Saves the desired value in the memory "key" */

  enum stausCodes
  {
    HTTP_OK = 200,           /**< OK */
    HTTP_BAD_REQUEST = 400,  /**< Bad Request */
    HTTP_UNAUTHORIZED = 401, /**< Unathorized */
    HTTP_NOT_FOUND = 404     /**< Not Found */
  };

} // namespace WebConfig

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/
#endif /* WEB_CONFIG_H_ */