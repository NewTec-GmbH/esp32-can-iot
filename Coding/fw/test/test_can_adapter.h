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
    /**************************************************************************************************/

    /**
     *  Write information on simulated Input Frame 
     * 
     *  @param id Frame ID
     *  @param rtr True if Frame is RTR. False otherwise.
     *  @param extended True if Frame is Extended. False otherwise.
     *  @param dlc Frame DLC
     *  @param byte0 Frame Data Byte 0
     *  @param byte1 Frame Data Byte 1
     *  @param byte2 Frame Data Byte 2
     *  @param byte3 Frame Data Byte 3
     *  @param byte4 Frame Data Byte 4
     *  @param byte5 Frame Data Byte 5
     *  @param byte6 Frame Data Byte 6
     *  @param byte7 Frame Data Byte 7
     *  @return success
     */
    bool enterInputFrame(uint32_t id,
                         bool rtr,
                         bool extended,
                         uint8_t dlc,
                         uint8_t byte0,
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
     *  Write information on simulated Output Frame
     * 
     *  @param[in] id Frame ID
     *  @param[in] rtr True if Frame is RTR. False otherwise.
     *  @param[in] extended True if Frame is Extended. False otherwise.
     *  @param[in] dlc Frame DLC
     *  @param[in] byte0 Frame Data Byte 0
     *  @param[in] byte1 Frame Data Byte 1
     *  @param[in] byte2 Frame Data Byte 2
     *  @param[in] byte3 Frame Data Byte 3
     *  @param[in] byte4 Frame Data Byte 4
     *  @param[in] byte5 Frame Data Byte 5
     *  @param[in] byte6 Frame Data Byte 6
     *  @param[in] byte7 Frame Data Byte 7
     *  @return success
     */
    bool enterOutputFrame(uint32_t id,
                          bool rtr,
                          bool extended,
                          uint8_t dlc,
                          uint8_t byte0,
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
     *  Clears input Frame
     * 
     *  @return success
     */
    bool clearInputFrame()
    {
        return enterInputFrame(0, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    /**************************************************************************************************/

    /**
     *  Clears output Frame
     * 
     *  @return success
     */
    bool clearOutputFrame()
    {
        return enterOutputFrame(0, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    /**************************************************************************************************/

    /**
     *  Compare Frames
     * 
     *  @param[in] frame1 First Frame to compare
     *  @param[in] frame2 Second Frame to compare
     *  @return success
     */
    bool compareFrames(const Frame &frame1, const Frame &frame2)
    {
        bool success = true;

        if (frame1.m_id != frame2.m_id)
        {
            success = false;
        }
        else if (frame1.m_rtr != frame2.m_rtr)
        {
            success = false;
        }
        else if (frame1.m_extended != frame2.m_extended)
        {
            success = false;
        }
        else if (frame1.m_dlc != frame2.m_dlc)
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

    /**************************************************************************************************/

    /**
     *  Copies CAN Frames
     * 
     *  @param[in] input Frame to be copied
     *  @param[in,out] output Copied Frame
     */
    void copyFrames(const Frame &input, Frame &output)
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

    /**
     *  Default constructor creates instance of the class using default values.
     *  Uses CANInterface constructor as its the implementation of an Interface.
     */
    TestCANAdapter() : CANInterface()
    {
    }

    /**
     *  Default destructor deletes instance of the class.
     */
    ~TestCANAdapter()
    {
    }

    /** 
     *  Configures and starts the CAN Controller to use the user values.
     * 
     *  @return success
     */
    bool begin()
    {
        return true;
    }

    /** 
     *  Stops the Controller Module without destroying the instance.
     * 
     *  @return success 
     */
    bool end()
    {
        return true;
    }

    /**
     *  Send a Frame from Serial to CAN Channel
     * 
     *  @param[in] frame     Reference to the Frame to be sended
     *  @return success 
     */
    bool send(const Frame &frame)
    {
        copyFrames(frame, m_outputFrame);
        return true;
    }

    /**
     *  Set the State of the CAN Channel.
     * 
     *  @param[in] state          BUS_STATE to be set to the CAN Channel
     *  @return success
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
     *  Set the Baudrate of the CAN Channel.
     * 
     *  @param[in] baudrate Baudrate of the CAN Channel
     *  @return success
     */
    bool setBaudrate(uint32_t baudrate)
    {
        bool success = true;
        m_baudRate = baudrate;
        return success;
    }

    /**
     *  Sent the BTR Registers of the CAN Channel.
     * 
     *  @param BTR0             Register 0 to set a Channel Baudrate directly
     *  @param BTR1             Register 1 to set a Channel Baudrate directly
     *  @return success
     */
    bool setBTR(uint8_t btr0, uint8_t btr1)
    {
        bool success = true;
        m_btr0 = btr0;
        m_btr1 = btr1;
        return success;
    }

    /**
     *  Set the Filter Mode of the CAN Channel.
     * 
     *  @param[in] filter       Defines Filter based on FILTER_MODE Enum.
     *  @return success
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
     *  Set the Acceptance Code Register.
     * 
     *  @param[in] ACn        Byte Array of 4 Registers that define the Filter Aceptance Code Register
     *  @return success 
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
     *  Set the Acceptance Mask Register.
     * 
     *  @param[in] AMn        Byte Array of 4 Registers that define the Filter Mask Register
     *  @return success
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
     *  Gets the Channel State from the CAN Controller.
     * 
     *  @return BUS_STATE m_currentState of the CAN-Bus Channel.
     */
    BUS_STATE getChannelState()
    {
        return m_currentState;
    }

    /**
     *  Gets the Status and Error Flags from the CAN Controller.
     * 
     *  @return  One Byte BCD hex value
     */
    uint8_t getStatusFlags()
    {
        return 0;
    }

    /**
     *  Polls one Message from the FIFO Buffer.
     * 
     *  @param[in,out] frame  Received frame from CAN Bus
     *  @return success  
     */
    bool pollSingle(Frame &frame)
    {
        bool success = false;

        copyFrames(m_inputFrame, frame);

        return success;
    }

    /**
     *  Get CAN Channel Baudrate
     * 
     *  @return m_baudrate
     */
    uint32_t getBaudrate()
    {
        return m_baudRate;
    }

    uint32_t m_baudRate;      /**< CAN Channel Baudrate */
    uint8_t m_btr0;           /**< BTR0 Byte */
    uint8_t m_btr1;           /**< BTR1 Byte */
    uint8_t m_filterMode;     /**< Filter Mode */
    BUS_STATE m_currentState; /**< CAN Channel State */
    Frame m_inputFrame;       /**< Simulated Input Frame */
    Frame m_outputFrame;      /**< Simulated Output Frame */
    Filter m_ACRn;            /**< ACRn Filter Bytes */
    Filter m_AMRn;            /**< AMRn FIlter Bytes */
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* TEST_CAN_ADAPTER_H */