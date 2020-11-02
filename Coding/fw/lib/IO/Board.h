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
        /** Pin number of onboard LED */
        static const uint8_t onBoardLedPinNo = 2U;

        /** Pin number of user button */
        static const uint8_t userButtonPinNo = 4U;

        /** Pin number of test pin */
        static const uint8_t testPinNo = 23U;

        /** Pin number of LED matrix data out */
        static const uint8_t ledMatrixDataOutPinNo = 27U;

        /** Pin number of LDR in */
        static const uint8_t ldrInPinNo = 34U;
    }; // namespace Pin

    /** Digital output pin: Onboard LED */
    static const DOutPin<Pin::onBoardLedPinNo> onBoardLedOut;

    /** Digital input pin: User button (input with pull-up) */
    static const DInPin<Pin::userButtonPinNo, INPUT_PULLUP> userButtonIn;

    /** Digital output pin: Test pin (only for debug purposes) */
    static const DOutPin<Pin::testPinNo> testPinOut;

    /** Digital output pin: LED matrix data out */
    static const DOutPin<Pin::ledMatrixDataOutPinNo> ledMatrixDataOut;

    /** Analog input pin: LDR in */
    static const AnalogPin<Pin::ldrInPinNo> ldrIn;

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