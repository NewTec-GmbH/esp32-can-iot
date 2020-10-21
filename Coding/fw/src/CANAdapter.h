/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
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
    * Default constructor creates instance of the class using default values.
    * Uses CANInterface constructor as its the implementation of an Interface
    */
    CANAdapter() : CANInterface(), m_baudRate(0), m_currentState(CLOSED)
    {
    }

    /**
    * Default destructor deletes instance of the class.
    */
    ~CANAdapter()
    {
    }

    /** 
    * Configures and starts the CAN Controller to use the user values.
    * @return isError = 0 for OK, 1 for Error 
    */
    uint8_t begin()
    {
        uint8_t isError = 0;
        if (CAN.begin(500E3) == 0)
        {
            isError = 1;
        }
        else
        {
            CAN.sleep();
        }

        return isError;
    }

    /** 
    * Stops the Controller Module without destroying the instance.
    * @return isError = 0 for OK, 1 for Error 
    */
    uint8_t end()
    {
        CAN.end();
        return 0;
    }

    /**
    * Send a Frame from Serial to CAN Channel
    * @param &Frame     Reference to the Frame to be sended
    * @return isError = 0 for OK, 1 for Error 
    */
    uint8_t send(const Frame &frame)
    {
        uint8_t isError = 0;
        if (frame.m_extended)
        {
            if (CAN.beginExtendedPacket(frame.m_id, frame.m_dlc, frame.m_rtr) == 0)
            {
                isError = 1;
            }
        }
        else
        {
            if (CAN.beginPacket(frame.m_id, frame.m_dlc, frame.m_rtr) == 0)
            {
                isError = 1;
            }
        }

        CAN.write(frame.m_data, frame.m_dlc);

        if (CAN.endPacket() == 0)
        {
            isError = 1;
        }

        return isError;
    }

    /**
    * Set the State of the CAN Channel.
    * @param state          BUS_STATE to be set to the CAN Channel
    * @return isError = 0 for OK, 1 for Error 
    */
    uint8_t setState(BUS_STATE state)
    {
        uint8_t isError = 0;
        switch (state)
        {
        case CLOSED:
            CAN.sleep();
            m_currentState = CLOSED;
            break;

        case NORMAL:
            if (m_baudRate == 0)
            {
                isError = 1;
            }
            CAN.wakeup();
            m_currentState = NORMAL;
            break;

        case LISTEN_ONLY:
            if (m_baudRate == 0)
            {
                isError = 1;
            }
            CAN.wakeup();
            m_currentState = LISTEN_ONLY;
            break;

        default:
            isError = 1;
            break;
        }

        return isError;
    }

    /**
    * Set the Baudrate of the CAN Channel.
    * @return isError = 0 for OK, 1 for Error 
    */
    uint8_t setBaudrate(uint32_t baudrate)
    {
        uint8_t isError = 0;
        m_baudRate = baudrate;
        CAN.end();
        if (CAN.begin(m_baudRate) == 0)
        {
            isError = 1;
        }
        CAN.sleep();
        return isError;
    }

    /**
    * Sent the BTR Registers of the CAN Channel.
    * @return 0 for OK, 1 for Error 
    */
    uint8_t setBTR(uint8_t btr0, uint8_t btr1)
    {
        return 1; /**< Must write to register. It returns error as the Controller does not allow it */
    }

    /**
    * Set the Filter Mode of the CAN Channel.
    * @return 0 for OK, 1 for Error 
    */
    uint8_t setFilterMode(uint8_t filter)
    {
        return 1; /**< Must write to register. It returns error as the Controller does not allow it */
    }

    /**
    * Set the Acceptance Code Register.
    * @todo Try to configure this
    */
    uint8_t setACn(const uint8_t *acn)
    {
        return 1;
    }

    /**
    * Set the Acceptance Mask Register.
    * @todo Try to configure this
    */
    uint8_t setAMn(const uint8_t *amn)
    {
        return 1;
    }

    /**
    * Gets the Channel State from the CAN Controller.
    * @return BUS_STATE m_currentState stores the state of the CAN Channel.
    */
    uint8_t getChannelState()
    {
        return m_currentState;
    }

    /**
    * Gets the Status and Error Flags from the CAN Controller.
    * @return 0 for OK, 1 for Error 
    */
    uint8_t getStatusFlags()
    {
        return 1; /**< Must write to register. It returns error as the Controller does not allow it */
    }

    /**
    * Polls one Message from the FIFO Buffer.
    * @return isError = 0 for OK, 1 for Error 
    */
    uint8_t pollSingle(Frame &frame)
    {
        uint8_t availableFrames = CAN.parsePacket();
        if (availableFrames != 0)
        {
            frame.m_id = CAN.packetId();
            frame.m_dlc = CAN.packetDlc();
            frame.m_extended = CAN.packetExtended();
            frame.m_rtr = CAN.packetRtr();

            for (int i = 0; i < frame.m_dlc; i++)
            {
                frame.m_data[i] = CAN.read();
            }
        }

        return availableFrames;
    }

private:
    uint32_t m_baudRate;
    BUS_STATE m_currentState;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* CAN_ADAPTER_H */