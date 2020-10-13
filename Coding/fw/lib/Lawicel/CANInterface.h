/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Lawicel
@{
@file       CANInterface.h

CAN-Controller Interface for Lawicel Protocol

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

class CANInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /** Enum of Possible States of the CAN Channel
     */
    enum BUS_STATE
    {
        CLOSED,
        NORMAL,
        LISTEN_ONLY,
    };

    /**
    * Format of a CAN Frame with an empty constructor
    */
    struct Frame
    {
        uint32_t ID;   //CAN ID
        bool RTR;      //Identifies a RTR Frame
        bool Extended; //Identifies an Extended Frame
        uint8_t DLC;   //Data Length
        uint8_t *Data; //Data of the Frame

        Frame() : ID(0),
                  RTR(false),
                  Extended(false),
                  DLC(0),
                  Data(0)
        {
        }
    };

    /**
    * Default constructor.
    */
    CANInterface()
    {
    }

    /**
    * Default destructor.
    */
    virtual ~CANInterface()
    {
    }

    /**
    * Send a Data String.
    * @param[in] Frame         Frame to be sended via CAN BUS
    */
    virtual uint8_t send(const Frame &Frame) = 0;

    /**
    * Set the State of the CAN Channel.
    * @param[in] state         Channel State to be set
    */
    virtual uint8_t setState(const BUS_STATE state) = 0;

    /**
    * Set the Baudrate of the CAN Channel.
    * @param[in] baudrate      Channel Baudrate to be set
    */
    virtual uint8_t setBaudrate(const long baudrate) = 0;

    /**
    * Sent the BTR Registers of the CAN Channel.
    * @param[in] BTR0, BTR1       Registers that set a Channel Baudrate directly
    */
    virtual uint8_t setBTR(const uint8_t BTR0, const uint8_t BTR1) = 0;

    /**
    * Set the Filter Mode of the CAN Channel.
    * @param[in] Filter        When FALSE (default), set to Dual Filter Mode. When TRUE, Single Filter Mode
    */
    virtual uint8_t setFilterMode(const bool Filter) = 0;

    /**
    * Set the Acceptance Code Register.
    * @param[in] ACn        Byte Array of 4 Registers that define the Filter Aceptance Code Register
    */
    virtual uint8_t setACn(const uint8_t *ACn) = 0;

    /**
    * Set the Acceptance Mask Register.
    * @param[in] AMn        Byte Array of 4 Registers that define the Filter Mask Register
    */
    virtual uint8_t setAMn(const uint8_t *AMn) = 0;

    /**
    * Gets the Channel State from the CAN Controller.
    */
    virtual uint8_t getChannelState() = 0;

    /**
    * Gets the Status and Error Flags from the CAN Controller.
    * @param[in] _flags         Array that contains the state of each Flag
    */
    virtual uint8_t getStatusFlags(bool *_flags) = 0;

    /**
    * Polls one Message from the FIFO Buffer.
    * @todo
    */
    virtual Frame pollSingle() = 0;


private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */

/** @} */