/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Settings
@{
@file       WLAN.h

WiFi configuration of ESP32

* @}
***************************************************************************************************/
#ifndef WLAN_H_
#define WLAN_H_

/* INCLUDES ***************************************************************************************/
/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

namespace wlan
{
    const String &getSTA_SSID();                             /**< Returns saved Station SSID */
    const String &getSTA_PASS();                             /**< Returns saved Station Password */
    const String &getAP_SSID();                              /**< Returns saved Access Point SSID */
    const String &getAP_PASS();                              /**< Returns saved Access Point Password */
    const bool &getAP_MODE();                                /**< Returns Access Point Mode Status */
    bool checkConnection(void);                              /**< Calls next request on DNS Server */
    IPAddress getIPAddress(void);                            /**< Returns the IP Address of the ESP */
    void saveConfig(const String &key, const String &value); /**< Saves the desired value in the memory "key" */
    bool begin();                                            /**< Starts the WiFi Connection */
} // namespace wlan

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/
#endif /* WEB_CONFIG_H_ */