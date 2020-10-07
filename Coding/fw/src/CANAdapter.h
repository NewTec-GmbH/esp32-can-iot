/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup gggggModule_group gggggModule
@{
@file       Xxxxx.h

Enter short description here.

Enter detailed description here.

@version    %$Id: CppTemplate.h 8740 2018-05-05 12:46:37Z link $
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
    * Constructs a empty Serial Adapter.
    **/
    CANAdapter() : m_name(), m_baudrate(), m_currentstate()
    {
    }

    /**
         * Default constructor.
         */

    CANAdapter(const String name, long baudrate) : m_name(name), m_baudrate(baudrate), m_currentstate(CLOSED)
    {
    }

    /**
         * Default destructor.
         */

    ~CANAdapter();

    /**
  * Get Adapter name
  */
    const String &getName() const
    {
        return m_name;
    }

    /**
         * Send a Data String.
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

        if (CAN.endPacket())
        {
            return 0;
        }

        return 1;
    }

    /**
         * Set the State of the CAN Channel.
         */

    uint8_t setState(const int state)
    {
        switch (state)
        {
        case CLOSED:
            CAN.end();
            m_currentstate = CLOSED;
            return 0;

        case NORMAL:
            CAN.begin(m_baudrate);
            m_currentstate = NORMAL;
            return 0;

        case LISTEN_ONLY:
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
    }

    /**
         * Set the Acceptance Mask Register.
         */

    uint8_t setAMn(const uint8_t *AMn)
    {
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

private:
    String m_name;
    long m_baudrate;
    BUS_STATE m_currentstate;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */