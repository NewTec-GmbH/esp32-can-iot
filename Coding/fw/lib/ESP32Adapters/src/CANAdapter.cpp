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
@file       CANAdapter.cpp

ESP32SJA1000 Adapter for Lawicel Protocol. @ref CANAdapter.h

***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include "CANAdapter.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/

CANAdapter::CANAdapter() : CANInterface(),
                           m_baudRate(500000),
                           m_currentState(CLOSED),
                           m_Can_Controller(CAN)
{
}

CANAdapter::~CANAdapter()
{
}

bool CANAdapter::begin()
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

bool CANAdapter::end()
{
    m_Can_Controller.end();
    return true;
}

bool CANAdapter::send(const Frame &frame)
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

bool CANAdapter::setState(BUS_STATE state)
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

bool CANAdapter::setBaudrate(uint32_t baudrate)
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

bool CANAdapter::setBTR(uint8_t btr0, uint8_t btr1)
{
    return false; // Must write to register. It returns error as the Controller does not allow it. Not possible to implement it.
}

bool CANAdapter::setFilterMode(FILTER_MODE filter)
{
    return false;
}

bool CANAdapter::setACn(const Filter &acn)
{
    return false;
}

bool CANAdapter::setAMn(const Filter &amn)
{
    return false;
}

CANInterface::BUS_STATE CANAdapter::getChannelState() const
{
    return m_currentState;
}

uint8_t CANAdapter::getStatusFlags() const
{
    return 0; // Must read register. It returns error as the Controller does not allow it.
}

bool CANAdapter::pollSingle(Frame &frame)
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

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

/** @} */