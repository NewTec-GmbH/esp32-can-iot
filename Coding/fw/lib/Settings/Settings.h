/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup SETTINGS
@{
@file       ISETTINGS.h

Handler for ESP32 Preferences in Flash Memory

* @}
***************************************************************************************************/
#ifndef SETTINGS_H_
#define SETTINGS_H_

/* INCLUDES ***************************************************************************************/
#include <Preferences.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/
/*
* Implementation of the Preferences Library for the project. Initial values and commands are
* saved and called through this class.
*/
namespace Settings
{
    bool save(                         /**< Saves uint32_t value to Flash memory */
              const String &directory, /**< Directory where information is stored */
              const String &key,       /**< Name of Memory Location */
              const uint32_t &value);  /**< Value to be stored */

    bool save(                         /**< Saves uint32_t value to Flash memory */
              const String &directory, /**< Directory where information is stored */
              const String &key,       /**< Name of Memory Location */
              const String &value);    /**< String to be stored */

    bool get(                                   /**< Gets uint32_t value from Flash memory */
             const String &directory,           /**< Directory where information is stored */
             const String &key,                 /**< Name of Memory Location */
             uint32_t &value,                   /**< Variable to write the value to */
             const uint32_t defaultValue = 0U); /**< Default value returned if no value stored in memory */

    bool get(                                 /**< Gets uint32_t value from Flash memory */
             const String &directory,         /**< Directory where information is stored */
             const String &key,               /**< Name of Memory Location */
             String &value,                   /**< Variable to write the String to */
             const String defaultValue = ""); /**< Default String returned if no String stored in memory */

    bool clear(const String &directory); /**< Clears all entries on a directory */
};                                       // namespace Settings

    /* INLINE FUNCTIONS ***************************************************************************/

    /* PROTOTYPES *********************************************************************************/

#endif /* SETTINGS_H */