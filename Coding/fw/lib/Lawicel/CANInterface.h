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
    enum BUS_STATE
    {
        CLOSED,
        NORMAL,
        LISTEN_ONLY,
    };

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
                  Data(nullptr)
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
    * Gets Interface name.
    */

    virtual const String &getName() const = 0;

    /**
         * Send a Data String.
         */

    virtual uint8_t send(const Frame &Frame) = 0;

    /**
         * Set the State of the CAN Channel.
         */

    virtual uint8_t setState(const int state) = 0;

    /**
         * Set the Baudrate of the CAN Channel.
         */

    virtual uint8_t setBaudrate(const long baudrate) = 0;

    /**
         * Sent the BTR Registers of the CAN Channel.
         */

    virtual uint8_t setBTR(const uint8_t BTR0, const uint8_t BTR1) = 0;

    /**
         * Set the Filter Mode of the CAN Channel.
         */

    virtual uint8_t setFilterMode(const bool Filter) = 0;

    /**
         * Set the Acceptance Code Register.
         */

    virtual uint8_t setACn(const uint8_t *ACn) = 0;

    /**
         * Set the Acceptance Mask Register.
         */

    virtual uint8_t setAMn(const uint8_t *AMn) = 0;

    /**
         * Gets the Channel State from the CAN Controller.
         */

    virtual uint8_t getChannelState() = 0;

    /**
    * Gets the Status and Error Flags from the CAN Controller.
    */
    virtual uint8_t getStatusFlags(bool *_flags) = 0;

    /**
    * Polls one Message from the FIFO Buffer.
    */
    virtual uint8_t pollSingle(CANInterface::Frame *frame) = 0;

    /**
    * Polls all Messages from the FIFO Buffer.
    */
    virtual uint8_t pollAll(CANInterface::Frame *frame) = 0;


private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */