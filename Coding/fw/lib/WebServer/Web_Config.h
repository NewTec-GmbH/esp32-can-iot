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
#include "FlashMem.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

namespace WebConfig
{
  static const uint32_t DNS_PORT = 53U;          /**< DNS Port */
  static const uint32_t WEBSERVER_PORT = 80U;    /**< HTTP Port */
  
  const String &getWEB_USER(); /**< Returns saved Webserver Username */
  const String &getWEB_PASS(); /**< Returns saved Webserver Password */

  enum StatusCodes
  {
    HTTP_OK = 200,           /**< OK */
    HTTP_BAD_REQUEST = 400,  /**< Bad Request */
    HTTP_UNAUTHORIZED = 401, /**< Unauthorized */
    HTTP_NOT_FOUND = 404     /**< Not Found */
  };

} // namespace WebConfig

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/
#endif /* WEB_CONFIG_H_ */