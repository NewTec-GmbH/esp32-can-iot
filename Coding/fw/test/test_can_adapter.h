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
    bool compareFrames(const Frame &frame1, const Frame &frame2);
    bool enterInputFrame(uint32_t id,   /**< CAN ID */
                         bool rtr,      /**< Identifies a RTR Frame */
                         bool extended, /**< Identifies an Extended Frame */
                         uint8_t dlc,   /**< Data Length */
                         uint8_t byte0, /**< Data of the Frame */
                         uint8_t byte1,
                         uint8_t byte2,
                         uint8_t byte3,
                         uint8_t byte4,
                         uint8_t byte5,
                         uint8_t byte6,
                         uint8_t byte7);

    bool enterOutputFrame(uint32_t id,   /**< CAN ID */
                          bool rtr,      /**< Identifies a RTR Frame */
                          bool extended, /**< Identifies an Extended Frame */
                          uint8_t dlc,   /**< Data Length */
                          uint8_t byte0, /**< Data of the Frame */
                          uint8_t byte1,
                          uint8_t byte2,
                          uint8_t byte3,
                          uint8_t byte4,
                          uint8_t byte5,
                          uint8_t byte6,
                          uint8_t byte7);

    bool checkFilter(Filter inputFilter, Filter adapterFilter);
    bool copyFrames(const Frame &input, Frame &output);

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
        return true;
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

        return true;
    }

    /**
    * Set the State of the CAN Channel.
    * @param state          BUS_STATE to be set to the CAN Channel
    * @return isError = 0 for OK, 1 for Error 
    */
    bool setState(BUS_STATE state)
    {
        bool success = true;
        switch (state)
        {
        case CLOSED:
            m_currentState = CLOSED;
            break;

        case NORMAL:
            m_currentState = NORMAL;
            break;

        case LISTEN_ONLY:
            m_currentState = LISTEN_ONLY;
            break;

        default:
            success = false;
            break;
        }

        return success;
    }

    /**
    * Set the Baudrate of the CAN Channel.
    * @return isError = 0 for OK, 1 for Error 
    */
    bool setBaudrate(uint32_t baudrate)
    {
        bool success = true;
        m_baudRate = baudrate;
        return success;
    }

    /**
    * Sent the BTR Registers of the CAN Channel.
    * @return 0 for OK, 1 for Error 
    */
    bool setBTR(uint8_t btr0, uint8_t btr1)
    {
        bool success = true;
        m_btr0 = btr0;
        m_btr1 = btr1;
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
        switch (filter)
        {
        case DUAL_FILTER:
            m_filterMode = 0;
            break;

        case SINGLE_FILTER:
            m_filterMode = 1;
            break;

        default:
            break;
        }
        return success;
    }

    /**
    * Set the Acceptance Code Register.
    */
    bool setACn(const Filter &acn)
    {
        bool success = true;

        for (uint8_t i = 0; i < FILTER_DATA_SIZE; i++)
        {
            m_ACRn.m_filterBytes[i] = acn.m_filterBytes[i];
        }

        return success;
    }

    /**
    * Set the Acceptance Mask Register.
    */
    bool setAMn(const Filter &amn)
    {
        bool success = true;

        for (uint8_t i = 0; i < FILTER_DATA_SIZE; i++)
        {
            m_AMRn.m_filterBytes[i] = amn.m_filterBytes[i];
        }

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
        
        copyFrames(m_inputFrame, frame);

        return success;
    }

    /**************************************************************************************************/

    /**
    *   Edit input Frame for Testing
    */
    bool enterInputFrame(uint32_t id,   /**< CAN ID */
                         bool rtr,      /**< Identifies a RTR Frame */
                         bool extended, /**< Identifies an Extended Frame */
                         uint8_t dlc,   /**< Data Length */
                         uint8_t byte0, /**< Data of the Frame */
                         uint8_t byte1,
                         uint8_t byte2,
                         uint8_t byte3,
                         uint8_t byte4,
                         uint8_t byte5,
                         uint8_t byte6,
                         uint8_t byte7)
    {
        bool success = true;

        m_inputFrame.m_id = id;
        m_inputFrame.m_rtr = rtr;
        m_inputFrame.m_extended = extended;
        m_inputFrame.m_dlc = dlc;
        m_inputFrame.m_data[0] = byte0;
        m_inputFrame.m_data[1] = byte1;
        m_inputFrame.m_data[2] = byte2;
        m_inputFrame.m_data[3] = byte3;
        m_inputFrame.m_data[4] = byte4;
        m_inputFrame.m_data[5] = byte5;
        m_inputFrame.m_data[6] = byte6;
        m_inputFrame.m_data[7] = byte7;

        return success;
    }

    /**************************************************************************************************/

    /**
    *   Edit output (expected) Frame for Testing
    */
    bool enterOutputFrame(uint32_t id,   /**< CAN ID */
                          bool rtr,      /**< Identifies a RTR Frame */
                          bool extended, /**< Identifies an Extended Frame */
                          uint8_t dlc,   /**< Data Length */
                          uint8_t byte0, /**< Data of the Frame */
                          uint8_t byte1,
                          uint8_t byte2,
                          uint8_t byte3,
                          uint8_t byte4,
                          uint8_t byte5,
                          uint8_t byte6,
                          uint8_t byte7)
    {
        bool success = true;

        m_outputFrame.m_id = id;
        m_outputFrame.m_rtr = rtr;
        m_outputFrame.m_extended = extended;
        m_outputFrame.m_dlc = dlc;
        m_outputFrame.m_data[0] = byte0;
        m_outputFrame.m_data[1] = byte1;
        m_outputFrame.m_data[2] = byte2;
        m_outputFrame.m_data[3] = byte3;
        m_outputFrame.m_data[4] = byte4;
        m_outputFrame.m_data[5] = byte5;
        m_outputFrame.m_data[6] = byte6;
        m_outputFrame.m_data[7] = byte7;

        return success;
    }

    /**************************************************************************************************/

    /**
    *   Clears input Frame
    */
    bool clearInputFrame()
    {
        return enterInputFrame(0, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    /**************************************************************************************************/

    /**
    *   Compared Frames
    */
    bool compareFrames(const Frame &frame1, const Frame &frame2)
    {
        bool success = true;

        if (frame1.m_id == frame2.m_id)
        {
            success = false;
        }
        else if (frame1.m_rtr == frame2.m_rtr)
        {
            success = false;
        }
        else if (frame1.m_extended == frame2.m_extended)
        {
            success = false;
        }
        else if (frame1.m_dlc == frame2.m_dlc)
        {
            success = false;
        }
        else
        {
            for (uint8_t i = 0; i < frame1.m_dlc; i++)
            {
                if (frame1.m_data[i] != frame2.m_data[i])
                {
                    success = false;
                    break;
                }
            }
        }

        return success;
    }

    bool checkFilter(Filter inputFilter, Filter adapterFilter)
    {
        bool success = true;

        for (uint8_t i = 0; i < FILTER_DATA_SIZE; i++)
        {
            if (inputFilter.m_filterBytes[i] != adapterFilter.m_filterBytes[i])
            {
                success = false;
                break;
            }
        }

        return success;
    }

    bool copyFrames(const Frame &input, Frame &output)
    {
        output.m_id = input.m_id;
        output.m_rtr = input.m_rtr;
        output.m_extended = input.m_extended;
        output.m_dlc = input.m_dlc;

        for (uint8_t i = 0; i < FRAME_DATA_SIZE; i++)
        {
            output.m_data[i] = input.m_data[i];
        }
    }

private:
    uint32_t m_baudRate;
    uint8_t m_btr0;
    uint8_t m_btr1;
    uint8_t m_filterMode;
    BUS_STATE m_currentState;
    Frame m_inputFrame;
    Frame m_outputFrame;
    Filter m_ACRn;
    Filter m_AMRn;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* TEST_CAN_ADAPTER_H */