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

/* MACROS *****************************************************************************************/
#define UTIL_ARRAY_NUM(__arr) (sizeof(__arr) / sizeof((__arr)[0]))

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

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
        &gpio4};

/* PUBLIC METHODES ********************************************************************************/

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

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

    return;
}

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

/* INTERNAL FUNCTIONS *****************************************************************************/
