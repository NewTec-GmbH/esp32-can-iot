/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
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
