/***************************************************************************************************
BSD 3-Clause License


Copyright (c) 2020-2021, NewTec GmbH - www.newtec.de
All rights reserved.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:


1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.


2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.


3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************************************/
/**
@addtogroup Settings
@{
@file       WLAN.cpp

WiFi configuration of ESP32

***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "FlashMem.h"
#include "WLAN.h"
#include <WiFi.h>
#include "Board.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

static const uint16_t WIFI_TIMEOUT_MS = 20000;     /**< Maximum wait time to establish the WiFi connection */
static const String DIRECTORY = "WLAN";            /**< NVM Directory for STA Credentials */
static const String AP_SSID = "ESP32";             /**< SSID of ESP Access Point. */
static const String AP_PASSWORD = "hochschuleulm"; /**< Password of ESP Access Point. */

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/**
 *  Determines the state of the WiFiModeSelect Button to enter AP Mode
 *  @return True if AP mode requested. False otherwise.
 */
static bool readWiFiMode();

/**
 *  Connects to the WiFi AP when requested
 *  @return true when succesfully connected. False otherwise.
 */
static bool connectWiFi();

/* VARIABLES **************************************************************************************/

static String gStaSsid = "";     /**< SSID of user-configured network. */
static String gStaPassword = ""; /**< Password of user-configured network. */

static IPAddress gServerIP; /**< Stores the IP Address of the ESP32 */
static bool gAPMode = true; /**< Defines True if AP Mode should be activated; or False for STA Mode */

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
 *  Get saved Station SSID
 * 
 *  @return Saved Station SSID 
 */
const String &wlan::getSTA_SSID()
{
    return gStaSsid;
}

/**************************************************************************************************/

/**
 *  Get saved Station Password
 * 
 *  @return Saved Station Password 
 */
const String &wlan::getSTA_PASS()
{
    return gStaPassword;
}

/**************************************************************************************************/

/**
 *  Get saved Access Point SSID
 * 
 *  @return Saved Access Point SSID
 */
const String &wlan::getAP_SSID()
{
    return AP_SSID;
}

/**************************************************************************************************/

/**
 *  Get saved Access Point Password
 * 
 *  @return Saved Access Point Password
 */
const String &wlan::getAP_PASS()
{
    return AP_PASSWORD;
}

/**************************************************************************************************/

/**
 *  Get Access Point Mode Status
 * 
 *  @return True if AP Mode should be activated; or False for STA Mode
 */
bool wlan::getAP_MODE()
{
    return gAPMode;
}

/**************************************************************************************************/

/**
 *  Start the WiFi Conenction
 * 
 *  @return success
 */
bool wlan::begin()
{
    bool success = true;
    Board::apLED.write(HIGH);
    Board::staLED.write(HIGH);

    Settings::get(DIRECTORY, "STA_SSID", gStaSsid, "");
    Settings::get(DIRECTORY, "STA_Password", gStaPassword, "");

    gAPMode = readWiFiMode();
    if (gAPMode)
    {
        Board::staLED.write(LOW);
        if (!WiFi.softAP(AP_SSID.c_str(), AP_PASSWORD.c_str()))
        {
            success = false;
        }

        gServerIP = WiFi.softAPIP();
    }
    else
    {
        Board::apLED.write(LOW);
        if (!WiFi.mode(WIFI_STA))
        {
            success = false;
        }
        else if (WiFi.begin(gStaSsid.c_str(), gStaPassword.c_str()) == WL_CONNECT_FAILED)
        {
            success = false;
        }
        else if (!connectWiFi())
        {
            success = false;
        }

        gServerIP = WiFi.localIP();
    }
    return success;
}

/**************************************************************************************************/

/**
 *   Checks WiFi Connection
 * 
 *   @return true if a restart is requested
 */
bool wlan::checkConnection()
{
    bool success = true;
    if ((WiFi.getMode() == WIFI_STA) && (WiFi.status() != WL_CONNECTED))
    {
        if (!connectWiFi())
        {
            success = false;
        }
    }
    return success;
}

/**************************************************************************************************/

/**
 *  Get the IP Address of the ESP
 * 
 *  @return IPAddress
 */
const IPAddress &wlan::getIPAddress()
{
    return gServerIP;
}

/**************************************************************************************************/

/**
 *  Saves the desired value in the memory "key"
 * 
 *  @param key  Memory Address to store information to
 *  @param value String to be stored
 */
void wlan::saveConfig(const String &key, const String &value)
{
    Settings::save(DIRECTORY, key, value);
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

/**************************************************************************************************/

/**
 *  Read Button State
 * 
 *  @return  True if Button is pressed
 */
static bool readWiFiMode()
{
    bool pressedButton = false;

    uint8_t btnState1 = LOW;
    uint8_t btnState2 = LOW;

    const uint8_t DEBOUNCE_DELAY = 100;
    const uint32_t SETUP_TIME = 2000;
    const uint32_t START_TIME = millis();

    while ((millis() - START_TIME) < SETUP_TIME)
    {
        btnState1 = Board::wifiModeSelect.read();

        delay(DEBOUNCE_DELAY);

        btnState2 = Board::wifiModeSelect.read();

        if (btnState1 == btnState2)
        {
            if (LOW == btnState1)
            {
                pressedButton = true;
            }
            else
            {
                pressedButton = false;
            }
        }
    }

    return pressedButton;
}

/**************************************************************************************************/

/**
 *  Connects to the WiFi AP when requested
 *  @return true when succesfully connected. False otherwise.
 */
static bool connectWiFi()
{
    bool success = true;

    unsigned long startAttempTime = millis();

    while ((WiFi.status() != WL_CONNECTED) && ((millis() - startAttempTime) < WIFI_TIMEOUT_MS))
    {
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        success = false;
    }
    else
    {
        gServerIP = WiFi.localIP();
    }

    return success;
}

/** @} */