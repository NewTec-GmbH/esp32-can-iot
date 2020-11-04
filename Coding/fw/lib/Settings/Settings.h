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
    bool save(const String directory, const String &key, const uint32_t &value);                            /**< Saves uint32_t value to Flash memory on location "key" */
    bool save(const String directory, const String &key, const String &value);                              /**< Saves String to Flash memory on location "key" */
    bool get(const String directory, const String &key, uint32_t &value, const uint32_t defaultValue = 0U); /**< Gets uint32_t value from Flash memory on location "key". Writes it in "value" */
    bool get(const String directory, const String &key, String &value, const String defaultValue = "");     /**< Gets String from Flash memory on location "key". Writes it in "value" */
    bool clear(const String directory);                                                                     /**< Clears all entries on a directory */
};                                                                                                         // namespace Settings

    /* INLINE FUNCTIONS ***************************************************************************/

    /* PROTOTYPES *********************************************************************************/

#endif /* SETTINGS_H */