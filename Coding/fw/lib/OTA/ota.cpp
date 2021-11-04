/**************************************************************************************************
* File: ota.cpp
* Brief: Implementation of ota.h
* Author: Gabryel Reyes (gabryelrdiaz@gmail.com)
**************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "ota.h"
#include <ArduinoOTA.h>

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

void executeCycle(void *parameter);

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
*   Initialization of OTA
*   @return success
*/
bool esp_OTA::setup()
{
    bool success = true;

    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            Serial.println("Start updating " + type);
        })
        .onEnd([]() {
            Serial.println("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR)
                Serial.println("End Failed");
        });

    //ArduinoOTA.setHostname(hostname);

    ArduinoOTA.begin();

    xTaskCreate(
        executeCycle, /* Task function. */
        "OTA Cycle",  /* String with name of task. */
        10000,        /* Stack size in bytes. */
        NULL,         /* Parameter passed as input of the task */
        1,            /* Priority of the task. */
        NULL);        /* Task handle. */

    return success;
}

/**************************************************************************************************/

/**
*   Loop Handle of OTA
*   @return success
*/
void executeCycle(void *parameter)
{
    for (;;)
    {
        ArduinoOTA.handle();
        delay(1000);
    }
    vTaskDelete(NULL);
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/