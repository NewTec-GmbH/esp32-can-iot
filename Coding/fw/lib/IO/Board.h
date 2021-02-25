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
@file       Board.h

* @}
***************************************************************************************************/
#ifndef __BOARD_H__
#define __BOARD_H__

/* INCLUDES ***************************************************************************************/
#include "io.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/** Electronic board abstraction */
namespace Board
{

    /* FORWARD DECLARATIONS ***************************************************************************/

    /* CONSTANTS **************************************************************************************/

    /* TYPES ******************************************************************************************/

    /** Pin number of all used pins. */
    namespace Pin
    {
        /** Pin number of Error LED */
        static const uint8_t indicatorError = 2U;

        /** Pin number of AP-Mode LED */
        static const uint8_t indicatorAPMode = 19U;

        /** Pin number of STA-Mode LED */
        static const uint8_t indicatorSTAMode = 18U;

        /** Pin number of WiFi-Mode Button */
        static const uint8_t userButton = 21U;

        /** GPIO */
        static const uint8_t GPIO_1 = 27U;
        static const uint8_t GPIO_2 = 26U;
        static const uint8_t GPIO_3 = 25U;
        static const uint8_t GPIO_4 = 33U;

        /** Pin number of OBD/CAN Control */
        static const uint8_t canSelector = 32U;

        /** Pin number of OBD Supply in */
        static const uint8_t analogSupplyCheck = 35U;

    }; /** namespace Pin */

    /** Digital output pin: Error Indicator */
    static const DOutPin<Pin::indicatorError> errorLED;

    /** Digital output pin: AP-Mode LED */
    static const DOutPin<Pin::indicatorAPMode> apLED;

    /** Digital output pin: STA-Mode LED */
    static const DOutPin<Pin::indicatorSTAMode> staLED;

    /** Digital input pin: User button (input with pull-up) */
    static const DInPin<Pin::userButton, INPUT_PULLUP> wifiModeSelect;

    /** Digital output pin: GPIO_1 */
    static const DOutPin<Pin::GPIO_1> gpio1;

    /** Digital output pin: GPIO_2 */
    static const DOutPin<Pin::GPIO_2> gpio2;

    /** Digital output pin: GPIO_3 */
    static const DOutPin<Pin::GPIO_3> gpio3;

    /** Digital output pin: GPIO_4 */
    static const DOutPin<Pin::GPIO_4> gpio4;

    /** Digital output pin: Bus Selector LED */
    static const DOutPin<Pin::canSelector> obdSwitch;

    /** Analog input pin: Analog Voltage in */
    static const AnalogPin<Pin::analogSupplyCheck> obdSupply;

    /** ADC resolution in digits */
    static const uint16_t adcResolution = 4096U;

    /** ADC reference voltage in mV */
    static const uint16_t adcRefVoltage = 3300U;

    /** Initialize all i/o pins */
    extern void init();

    /** Execute a hard reset! */
    extern void reset();

    /** Turn on Error LED and halt system until manual reset */
    extern void haltSystem();

    /** Turn on Error LED for a period of time */
    extern void blinkError(uint32_t duration);

}; /** namespace Board */

    /* INLINE FUNCTIONS *******************************************************************************/

    /* PROTOTYPES *************************************************************************************/

#endif /* __BOARD_H__ */

/** @} */