/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup IO
@{
@file       Settings.cpp

Handler for ESP32 Preferences in Flash Memory. @ref Settings.h

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include <Settings.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/
/**************************************************************************************************/
bool Settings::save(const char *directory, const String &key, const uint32_t &value)
{
    bool success = false;
    if (m_memory.begin(directory, false))
    {
        m_memory.putULong(key.c_str(), value);
        m_memory.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/
bool Settings::save(const char *directory, const String &key, const String &value)
{
    bool success = false;
    if (m_memory.begin(directory, false))
    {
        m_memory.putString(key.c_str(), value);
        m_memory.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/
bool Settings::get(const char *directory, const String &key, uint32_t &value, const uint32_t defaultValue)
{
    bool success = false;
    if (m_memory.begin(directory, false))
    {
        value = m_memory.getULong(key.c_str(), defaultValue);
        m_memory.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/
bool Settings::get(const char *directory, const String &key, String &value, const String defaultValue)
{
    bool success = false;
    if (m_memory.begin(directory, false))
    {
        value = m_memory.getString(key.c_str(), defaultValue);
        m_memory.end();
        success = true;
    }
    return success;
}

/**************************************************************************************************/
bool Settings::clear(const char *directory)
{
    bool success = false;
    if (m_memory.begin(directory, false))
    {
        success = m_memory.clear();
    }

    return success;
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/
