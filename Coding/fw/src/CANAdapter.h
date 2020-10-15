/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Application
@{
@file       CANAdapter.h

ESP32SJA1000 CAN-Controller Adapter for Lawicel Protocol

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

class CANAdapter : public CANInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
    * Default constructor.
    */
    CANAdapter() : CANInterface(), m_baudrate(0), m_currentstate(CLOSED)
    {
    }

    /**
    * Default destructor.
    */
    ~CANAdapter()
    {
    }

    /** 
    * Initialize Module.
    */
    uint8_t begin()
    {
        return 0;
    }

    /** 
    * Terminate Module. 
    */
    uint8_t end()
    {
        return 0;
    }

    /**
    * Send a Frame.
    */
    uint8_t send(const Frame &Frame)
    {
        if (Frame.Extended)
        {
            CAN.beginExtendedPacket(Frame.ID, Frame.DLC, Frame.RTR);
        }
        else
        {
            CAN.beginPacket(Frame.ID, Frame.DLC, Frame.RTR);
        }

        CAN.write(Frame.Data, Frame.DLC);

        if (CAN.endPacket() == 1)
        {
            return 0;
        }

        return 1;
    }

    /**
    * Set the State of the CAN Channel.
    */
    uint8_t setState(const BUS_STATE state)
    {
        switch (state)
        {
        case CLOSED:
            CAN.end();
            m_currentstate = CLOSED;
            return 0;

        case NORMAL:
            if (m_baudrate == 0)
            {
                return 1;
            }
            CAN.begin(m_baudrate);
            m_currentstate = NORMAL;
            return 0;

        case LISTEN_ONLY:
            if (m_baudrate == 0)
            {
                return 1;
            }
            CAN.begin(m_baudrate);
            m_currentstate = LISTEN_ONLY;
            return 0;

        default:
            return 1;
        }
    }

    /**
    * Set the Baudrate of the CAN Channel.
    */
    uint8_t setBaudrate(const long baudrate)
    {
        m_baudrate = baudrate;
        return 0;
    }

    /**
    * Sent the BTR Registers of the CAN Channel.
    */
    uint8_t setBTR(const uint8_t BTR0, const uint8_t BTR1)
    {
        return 1; //Must write to register
    }

    /**
    * Set the Filter Mode of the CAN Channel.
    */
    uint8_t setFilterMode(const bool Filter)
    {
        return 1; //Must write to register
    }

    /**
    * Set the Acceptance Code Register.
    */
    uint8_t setACn(const uint8_t *ACn)
    {
        return 1;
    }

    /**
    * Set the Acceptance Mask Register.
    */
    uint8_t setAMn(const uint8_t *AMn)
    {
        return 1;
    }

    /**
    * Gets the Channel State from the CAN Controller.
    */
    uint8_t getChannelState()
    {
        return m_currentstate;
    }

    /**
    * Gets the Status and Error Flags from the CAN Controller.
    */
    uint8_t getStatusFlags(bool *_flags)
    {
        return 1; //Must read register
    }

    /**
    * Polls one Message from the FIFO Buffer.
    */
    Frame pollSingle()
    {
        Frame frame;
        if (CAN.parsePacket() == 0)
        {
            frame.ID = 0xFFF;
            return frame;
        }

        frame.ID = CAN.packetId();
        frame.DLC = CAN.packetDlc();
        frame.Extended = CAN.packetExtended();
        frame.RTR = CAN.packetRtr();

        for (int i = 0; i < frame.DLC; i++)
        {
            frame.Data[i] = CAN.read();
        }

        return frame;
    }

private:
    long m_baudrate;
    BUS_STATE m_currentstate;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* CAN_ADAPTER_H */