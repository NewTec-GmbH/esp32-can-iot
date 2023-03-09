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
@addtogroup Adapters
@{
@file       CANAdapter.h

ESP32SJA1000 Adapter for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef CAN_ADAPTER_H
#define CAN_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include <CANInterface.h>
#include <CAN.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
 *  ESP-32 Adapter as implementation of CANInterface for the Lawicel Protocol.
 */
class CANAdapter : public CANInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
     *  Default constructor creates instance of the class using default values.
     *  Uses CANInterface constructor as its the implementation of an Interface.
     */
    CANAdapter() : CANInterface(),
                   m_baudRate(500000),
                   m_currentState(CLOSED),
                   m_Can_Controller(CAN)
    {
    }

    /**
     *  Default destructor deletes instance of the class.
     */
    ~CANAdapter() override
    {
    }

    /** 
     *  Configures and starts the CAN Controller to use the user values.
     * 
     *  @return success
     */
    bool begin() override
    {
        bool success = true;

        if (0 == m_Can_Controller.begin(m_baudRate))
        {
            success = false;
        }
        else
        {
            m_Can_Controller.sleep();
        }

        return success;
    }

    /** 
     *  Stops the Controller Module without destroying the instance.
     * 
     *  @return success 
     */
    bool end() override
    {
        m_Can_Controller.end();
        return true;
    }

    /**
     *  Send a Frame from Serial to CAN Channel
     * 
     *  @param[in] frame     Reference to the Frame to be sended
     *  @return success 
     */
    bool send(const Frame &frame) override
    {
        bool success = true;
        if (frame.m_extended)
        {
            if (0 == m_Can_Controller.beginExtendedPacket(frame.m_id, frame.m_dlc, frame.m_rtr))
            {
                success = false;
            }
        }
        else
        {
            if (0 == m_Can_Controller.beginPacket(frame.m_id, frame.m_dlc, frame.m_rtr))
            {
                success = false;
            }
        }

        if (success)
        {
            if (0 != frame.m_dlc)
            {
                if (0 == m_Can_Controller.write(frame.m_data, frame.m_dlc))
                {
                    success = false;
                }
            }
            if (0 == m_Can_Controller.endPacket())
            {
                success = false;
            }
        }

        return success;
    }

    /**
     *  Set the State of the CAN Channel.
     * 
     *  @param[in] state          BUS_STATE to be set to the CAN Channel
     *  @return success
     */
    bool setState(BUS_STATE state) override
    {
        bool success = true;
        switch (state)
        {
        case CLOSED:
            m_Can_Controller.sleep();
            m_currentState = CLOSED;
            break;

        case NORMAL:
            if (0 == m_baudRate)
            {
                success = false;
            }
            else
            {
                m_Can_Controller.wakeup();
                m_currentState = NORMAL;
            }
            break;

        case LISTEN_ONLY:
            if (0 == m_baudRate)
            {
                success = false;
            }
            else
            {
                m_Can_Controller.wakeup();
                m_currentState = LISTEN_ONLY;
            }
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
    bool setBaudrate(uint32_t baudrate) override
    {
        bool success = true;
        m_baudRate = baudrate;
        m_Can_Controller.end();
        if (0 == m_Can_Controller.begin(m_baudRate))
        {
            success = false;
        }
        m_Can_Controller.sleep();
        return success;
    }

    /**
     *  Sent the BTR Registers of the CAN Channel.
     * 
     *  @param btr0             Register 0 to set a Channel Baudrate directly
     *  @param btr1             Register 1 to set a Channel Baudrate directly
     *  @return success
     */
    bool setBTR(uint8_t btr0, uint8_t btr1) override
    {
        return false; // Must write to register. It returns error as the Controller does not allow it. Not possible to implement it.
    }

    /**
     *  Set the Filter Mode of the CAN Channel.
     * 
     *  @param[in] filter       Defines Filter based on FILTER_MODE Enum.
     *  @return success
     */
    bool setFilterMode(FILTER_MODE filter) override
    {
        return false;
    }

    /**
     *  Set the Acceptance Code Register.
     * 
     *  @param[in] acn        Byte Array of 4 Registers that define the Filter Aceptance Code Register
     *  @return success 
     */
    bool setACn(const Filter &acn) override
    {
        return false;
    }

    /**
     *  Set the Acceptance Mask Register.
     * 
     *  @param[in] amn        Byte Array of 4 Registers that define the Filter Mask Register
     *  @return success
     */
    bool setAMn(const Filter &amn) override
    {
        return false;
    }

    /**
     *  Gets the Channel State from the CAN Controller.
     * 
     *  @return BUS_STATE m_currentState of the CAN-Bus Channel.
     */
    BUS_STATE getChannelState() const override
    {
        return m_currentState;
    }

    /**
     *  Gets the Status and Error Flags from the CAN Controller.
     * 
     *  @return  One Byte BCD hex value
     */
    uint8_t getStatusFlags() const override
    {
        return 0; // Must read register. It returns error as the Controller does not allow it.
    }

    /**
     *  Polls one Message from the FIFO Buffer.
     * 
     *  @param[in,out] frame  Received frame from CAN Bus
     *  @return success  
     */
    bool pollSingle(Frame &frame) override
    {
        bool success = false;

        if (-1 != m_Can_Controller.parsePacket())
        {
            frame.m_id = m_Can_Controller.packetId();
            frame.m_dlc = m_Can_Controller.packetDlc();
            frame.m_extended = m_Can_Controller.packetExtended();
            frame.m_rtr = m_Can_Controller.packetRtr();

            for (int i = 0; i < frame.m_dlc; i++)
            {
                frame.m_data[i] = m_Can_Controller.read();
            }
            success = true;
        }

        return success;
    }

private:
    uint32_t m_baudRate;                 /**< Baudrate of CAN Channel */
    BUS_STATE m_currentState;            /**< Current Channel State */
    ESP32SJA1000Class &m_Can_Controller; /**< Instance of CAN Controller */
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* CAN_ADAPTER_H */