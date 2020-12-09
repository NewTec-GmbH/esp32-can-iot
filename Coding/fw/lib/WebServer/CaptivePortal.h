/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Webserver
@{
@file       CaptivePOrtal.h

Captive Portal for ESP32 WebServer

* @}
***************************************************************************************************/
#ifndef CAPTIVE_PORTAL_H_
#define CAPTIVE_PORTAL_H_

/* INCLUDES ***************************************************************************************/
#include <ESPAsyncWebServer.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* FORWARD DECLARATIONS **************************************************************************/
namespace CaptivePortal
{
    /**
    * Initialize Captive Portal and register it on the web server.
    * @param[in] server   Web server
    */
    void init(AsyncWebServer &server);

    /**
    * Is restart requested by captive portal?
    * @return If restart is requested it will return true otherwise false.
    */
    bool isRestartRequested();

} // namespace CaptivePortal

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/

#endif /* CAPTIVE_PORTAL_H_ */