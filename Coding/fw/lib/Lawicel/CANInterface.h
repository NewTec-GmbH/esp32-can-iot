/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
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
    static const uint8_t FRAME_DATA_SIZE = 8;

    /* TYPES **********************************************************************************/

    /** Enum of Possible States of the CAN Channel
     */
    enum BUS_STATE
    {
        CLOSED = 0, /**< No messages are received or transmitted to the Bus from the controller. */
        NORMAL,     /**< Messages are received and transmitted to the Bus from the controller. */
        LISTEN_ONLY /**< Controller is limited to receiving messages only. */
    };

    /**
    * Format of a CAN Frame with an empty constructor
    */
    struct Frame
    {
        uint32_t m_id;                   /**< CAN ID */
        bool m_rtr;                      /**< Identifies a RTR Frame */
        bool m_extended;                 /**< Identifies an Extended Frame */
        uint8_t m_dlc;                   /**< Data Length */
        uint8_t m_data[FRAME_DATA_SIZE]; /**< Data of the Frame */

        Frame() : m_id(0),               /**< Initialize Frame with default values*/
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
    * @return 0 for OK, 1 for Error
    */
    virtual uint8_t begin() = 0;

    /** 
    * Stops the Controller Module without destroying the instance.
    * @return 0 for OK, 1 for Error 
    */
    virtual uint8_t end() = 0;

    /**
    * Send a Data String.
    * @param[in] Frame         Frame to be sended via CAN BUS
    * @return 0 for OK, 1 for Error
    */
    virtual uint8_t send(const Frame &frame) = 0;

    /**
    * Set the State of the CAN Channel.
    * @param[in] state         Channel State to be set
    * @return 0 for OK, 1 for Error
    */
    virtual uint8_t setState(BUS_STATE state) = 0;

    /**
    * Set the Baudrate of the CAN Channel.
    * @param[in] baudrate      Channel Baudrate to be set
    * @return 0 for OK, 1 for Error
    */
    virtual uint8_t setBaudrate(uint32_t baudrate) = 0;

    /**
    * Sent the BTR Registers of the CAN Channel.
    * @param[in] BTR0, BTR1       Registers that set a Channel Baudrate directly
    * @return 0 for OK, 1 for Error
    */
    virtual uint8_t setBTR(uint8_t btr0, uint8_t btr1) = 0;

    /**
    * Set the Filter Mode of the CAN Channel.
    * @param[in] Filter        When FALSE (default), set to Dual Filter Mode. When TRUE, Single Filter Mode
    * @return 0 for OK, 1 for Error
    */
    virtual uint8_t setFilterMode(uint8_t filter) = 0;

    /**
    * Set the Acceptance Code Register.
    * @param[in] ACn        Byte Array of 4 Registers that define the Filter Aceptance Code Register
    * @return 0 for OK, 1 for Error
    */
    virtual uint8_t setACn(const uint8_t *acn) = 0;

    /**
    * Set the Acceptance Mask Register.
    * @param[in] AMn        Byte Array of 4 Registers that define the Filter Mask Register
    * @return 0 for OK, 1 for Error
    */
    virtual uint8_t setAMn(const uint8_t *acn) = 0;

    /**
    * Gets the Channel State from the CAN Controller.
    * @return BUS_STATE m_currentState of the CAN-Bus Channel.
    */
    virtual uint8_t getChannelState() = 0;

    /**
    * Gets the Status and Error Flags from the CAN Controller.
    * @return  One Byte BCD hex value
    */
    virtual uint8_t getStatusFlags() = 0;

    /**
    * Polls one Message from the FIFO Buffer.
    * @return availableFrames. 0 for No new Frames.  
    */
    virtual uint8_t pollSingle(Frame &frame) = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */

/** @} */