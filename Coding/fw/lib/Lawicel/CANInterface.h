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
@addtogroup Interfaces
@ingroup Lawicel
@{
@file       CANInterface.h

CAN interface for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

/* INCLUDES ***************************************************************************************/

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
 *  Interface of the Lawicel Protocol to the CAN Controller of the board. Defines the Methods to be 
 *  implemented on the Adapter so that the Protocol works as expected.
 */
class CANInterface
{
public:
    /* CONSTANTS ******************************************************************************/
    static const uint8_t FRAME_DATA_SIZE = 8;  /**< Maximum Data size of a Frame */
    static const uint8_t FILTER_DATA_SIZE = 4; /**< Standard Data size of a Filter */

    /* TYPES **********************************************************************************/

    /** 
    * Enum of Possible States of the CAN Channel
    */
    enum BUS_STATE
    {
        CLOSED = 0, /**< No messages are received or transmitted to the Bus from the controller. */
        NORMAL,     /**< Messages are received and transmitted to the Bus from the controller. */
        LISTEN_ONLY /**< Controller is limited to receiving messages only. */
    };

    /**
    * Format of a CAN Frame with an empty structure
    */
    struct Frame
    {
        uint32_t m_id;                   /**< CAN ID */
        bool m_rtr;                      /**< Identifies a RTR Frame */
        bool m_extended;                 /**< Identifies an Extended Frame */
        uint8_t m_dlc;                   /**< Data Length */
        uint8_t m_data[FRAME_DATA_SIZE]; /**< Data of the Frame */

        Frame() : m_id(0), /**< Initialize Frame with default values*/
                  m_rtr(false),
                  m_extended(false),
                  m_dlc(0)
        {
            for (int i = 0; i < FRAME_DATA_SIZE; i++)
            {
                m_data[i] = 0;
            }
        }
    };

    /** 
    * Array for the Definition of Filter Registers ACn and AMn
    */
    struct Filter
    {
        uint8_t m_filterBytes[FILTER_DATA_SIZE];
    };

    /** 
    * Enum of Possible CAN Frame Filters. See SJA1000 Datasheet for explanation
    */
    enum FILTER_MODE
    {
        DUAL_FILTER = 0,
        SINGLE_FILTER
    };

    /**
    * Default constructor creates instance of the class using default values.
    */
    CANInterface()
    {
    }

    /**
    * Default destructor deletes instance of the class.
    */
    virtual ~CANInterface()
    {
    }

    /**
    * Configures and starts the CAN Controller to use the user values.
    * @return bool
    */
    virtual bool begin() = 0;

    /** 
    * Stops the Controller Module without destroying the instance.
    * @return bool
    */
    virtual bool end() = 0;

    /**
    * Send a Data String.
    * @param[in] Frame         Frame to be sended via CAN BUS
    * @return bool
    */
    virtual bool send(const Frame &frame) = 0;

    /**
    * Set the State of the CAN Channel.
    * @param[in] state         Channel State to be set
    * @return bool
    */
    virtual bool setState(BUS_STATE state) = 0;

    /**
    * Set the Baudrate of the CAN Channel.
    * @param[in] baudrate      Channel Baudrate to be set
    * @return bool
    */
    virtual bool setBaudrate(uint32_t baudrate) = 0;

    /**
    * Sent the BTR Registers of the CAN Channel.
    * @param BTR0             Register 0 to set a Channel Baudrate directly
    * @param BTR1             Register 1 to set a Channel Baudrate directly
    * @return bool
    */
    virtual bool setBTR(uint8_t btr0, uint8_t btr1) = 0;

    /**
    * Set the Filter Mode of the CAN Channel.
    * @param[in] filter       Defines Filter based on FILTER_MODE Enum.
    * @return bool
    */
    virtual bool setFilterMode(FILTER_MODE filter) = 0;

    /**
    * Set the Acceptance Code Register.
    * @param[in] ACn        Byte Array of 4 Registers that define the Filter Aceptance Code Register
    * @return bool 
    */
    virtual bool setACn(const Filter &acn) = 0;

    /**
    * Set the Acceptance Mask Register.
    * @param[in] AMn        Byte Array of 4 Registers that define the Filter Mask Register
    * @return bool
    */
    virtual bool setAMn(const Filter &acn) = 0;

    /**
    * Gets the Channel State from the CAN Controller.
    * @return BUS_STATE m_currentState of the CAN-Bus Channel.
    */
    virtual BUS_STATE getChannelState() = 0;

    /**
    * Gets the Status and Error Flags from the CAN Controller.
    * @return  One Byte BCD hex value
    */
    virtual uint8_t getStatusFlags() = 0;

    /**
    * Polls one Message from the FIFO Buffer.
    * @return number of available Frames. 0 for No new Frames.  
    */
    virtual bool pollSingle(Frame &frame) = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */

/** @} */