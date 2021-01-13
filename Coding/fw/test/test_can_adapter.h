/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Test
@{
@file       test_can_adapter.h

Native Test CAN Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef TEST_CAN_ADAPTER_H
#define TEST_CAN_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include "CANInterface.h"
#include <stdint.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
*  Native Adapter as implementation of CANInterface for the Lawicel Protocol.
*/
class TestCANAdapter : public CANInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
    * Default constructor creates instance of the class using default values.
    * Uses CANInterface constructor as its the implementation of an Interface.
    * @param m_baudrate         Defines the Default baudrate of the CAN Channel
    */
    TestCANAdapter() : CANInterface()
    {
    }

    /**
    * Default destructor deletes instance of the class.
    */
    ~TestCANAdapter()
    {
    }

    /** 
    * Configures and starts the CAN Controller to use the user values.
    * @return isError = 0 for OK, 1 for Error 
    */
    bool begin()
    {
        bool success = true;
        return success;
    }

    /** 
    * Stops the Controller Module without destroying the instance.
    * @return isError = 0 for OK, 1 for Error 
    */
    bool end()
    {
        return true;
    }

    /**
    * Send a Frame from Serial to CAN Channel
    * @param &Frame     Reference to the Frame to be sended
    * @return isError = 0 for OK, 1 for Error 
    */
    bool send(const Frame &frame)
    {
        bool success = true;
        return success;
    }

    /**
    * Set the State of the CAN Channel.
    * @param state          BUS_STATE to be set to the CAN Channel
    * @return isError = 0 for OK, 1 for Error 
    */
    bool setState(BUS_STATE state)
    {
        bool success = true;
        return success;
    }

    /**
    * Set the Baudrate of the CAN Channel.
    * @return isError = 0 for OK, 1 for Error 
    */
    bool setBaudrate(uint32_t baudrate)
    {
        bool success = true;
        return success;
    }

    /**
    * Sent the BTR Registers of the CAN Channel.
    * @return 0 for OK, 1 for Error 
    */
    bool setBTR(uint8_t btr0, uint8_t btr1)
    {
        bool success = true;
        return success;
    }

    /**
    * Set the Filter Mode of the CAN Channel.
    * @param filter       Defines Filter based on FILTER_MODE Enum.
    * @return 0 for OK, 1 for Error 
    */
    bool setFilterMode(FILTER_MODE filter)
    {
        bool success = true;
        return success;
    }

    /**
    * Set the Acceptance Code Register.
    */
    bool setACn(const Filter &acn)
    {
        bool success = true;
        return success;
    }

    /**
    * Set the Acceptance Mask Register.
    */
    bool setAMn(const Filter &amn)
    {
        bool success = true;
        return success;
    }

    /**
    * Gets the Channel State from the CAN Controller.
    * @return BUS_STATE m_currentState stores the state of the CAN Channel.
    */
    BUS_STATE getChannelState()
    {
        return m_currentState;
    }

    /**
    * Gets the Status and Error Flags from the CAN Controller.
    * @return 0 for OK, 1 for Error 
    */
    uint8_t getStatusFlags()
    {
        return 0;
    }

    /**
    * Polls one Message from the FIFO Buffer.
    * @return availableFrames. 0 for No new Frames.
    */
    bool pollSingle(Frame &frame)
    {
        bool success = false;
        return success;
    }

private:
    uint32_t m_baudRate;
    BUS_STATE m_currentState;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* TEST_CAN_ADAPTER_H */