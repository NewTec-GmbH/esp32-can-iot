/* MIT License
 *
 * Copyright (c) 2019 - 2020 Andreas Merkle <web@blue-andi.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/****************************************************************************************************/
/**
@brief  Board Abstraction
@author Andreas Merkle <web@blue-andi.de>
@addtogroup HAL
@{
@file       Board.cpp

@ref io.h

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "Board.h"

#include <esp_int_wdt.h>
#include <esp_task_wdt.h>

using namespace Board;

/* CONSTANTS **************************************************************************************/

static const uint16_t OBD_SUPPLY_THRESHOLD = 800; /**< Voltage [mv] measured to change to OBD Mode */

/* MACROS *****************************************************************************************/
#define UTIL_ARRAY_NUM(__arr) (sizeof(__arr) / sizeof((__arr)[0]))

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

static void setBusMode(); /**< Switch between CAN or OBD Modes */

/* VARIABLES **************************************************************************************/

/** A list of all used i/o pins, used for intializaton. */
static const IoPin *ioPinList[] =
    {
        &errorLED,
        &apLED,
        &staLED,
        &wifiModeSelect,
        &gpio1,
        &gpio2,
        &gpio3,
        &gpio4,
        &obdSwitch,
        &obdSupply};

/* PUBLIC METHODES ********************************************************************************/

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/**************************************************************************************************/

/**
 *   Initialize all i/o pins
 */
extern void Board::init()
{
    uint8_t index = 0U;

    /* Initialize all i/o pins */
    for (index = 0U; index < UTIL_ARRAY_NUM(ioPinList); ++index)
    {
        if (nullptr != ioPinList[index])
        {
            ioPinList[index]->init();
        }
    }

    setBusMode();
    return;
}

/**************************************************************************************************/

/**
 *   Execute a hard reset!
 */
extern void Board::reset()
{
    esp_task_wdt_init(1, true);
    esp_task_wdt_add(nullptr);

    for (;;)
    {
        /* Wait for reset. */
        ;
    }

    return;
}

/**************************************************************************************************/

/**
 *   Turn on Error LED and halt system until manual reset
 */
extern void Board::haltSystem()
{
    errorLED.write(HIGH);
    while (true)
    {
        /* Wait for reset */
    }
}

/**************************************************************************************************/

/**
 *   Turn on Error LED for a period of time
 *   @param[in] duration    Milliseconds to keep Error LED ON.
 */
extern void Board::blinkError(uint32_t duration)
{
    errorLED.write(HIGH);

    uint32_t startTime = millis();

    while (millis() < (startTime + duration))
    {
    }
    errorLED.write(LOW);
}

/* INTERNAL FUNCTIONS *****************************************************************************/

/**************************************************************************************************/

/**
 *   Switch between CAN or OBD Modes
 */
static void setBusMode()
{
    uint16_t supplyVoltage = obdSupply.read();
    const uint16_t threshold = (OBD_SUPPLY_THRESHOLD * (adcResolution - 1U)) / adcRefVoltage;

    if (threshold <= supplyVoltage)
    {
        /**
        * There is a voltage greater than the threshold on the Power Supply, meaning that the
        * System is connected to an OBD Bus
        */

        obdSwitch.write(LOW); /**< In OBD Mode, the Relays should be in a Open State */
    }
    else
    {
        obdSwitch.write(HIGH); /**< In CAN Mode, the Relays should be in a Closed State */
    }
}
