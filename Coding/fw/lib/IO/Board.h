/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
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
        static const uint8_t indicatorAPMode = 18U;

        /** Pin number of STA-Mode LED */
        static const uint8_t indicatorSTAMode = 19U;

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
        static const uint8_t analogSupplyCheck = 34U;

    }; // namespace Pin

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

    /** Digital output pin: AP-Mode LED */
    static const DOutPin<Pin::canSelector> obdSwitch;

    /** Analog input pin: LDR in */
    static const AnalogPin<Pin::analogSupplyCheck> obdSupply;

    /** ADC resolution in digits */
    static const uint16_t adcResolution = 4096U;

    /** ADC reference voltage in mV */
    static const uint16_t adcRefVoltage = 3300U;

    /**
    * Initialize all i/o pins.
    */
    extern void init();

    /**
    * Execute a hard reset!
    */
    extern void reset();

}; // namespace Board

    /* INLINE FUNCTIONS *******************************************************************************/

    /* PROTOTYPES *************************************************************************************/

#endif /* __BOARD_H__ */

/** @} */