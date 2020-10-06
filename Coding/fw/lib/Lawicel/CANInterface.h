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
#include <Lawicel.h>

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

    /**
         * Default constructor.
         */

    CANInterface();

    /**
         * Default destructor.
         */

    virtual ~CANInterface();

    /**
         * Send a Data String.
         */

    virtual void send(const Lawicel::Frame &Frame) = 0;

    /**
         * Set the State of the CAN Channel.
         */

    virtual void setState(const int state) = 0;

    /**
         * Set the Baudrate of the CAN Channel.
         */

    virtual void setBaudrate(const long baudrate) = 0;

    /**
         * Sent the BTR Registers of the CAN Channel.
         */

    virtual void setBTR(const uint8_t BTR0, const uint8_t BTR1) = 0;

    /**
         * Set the Filter Mode of the CAN Channel.
         */

    virtual void setFilterMode(const bool Filter) = 0;

    /**
         * Set the Acceptance Code Register.
         */

    virtual void setACn(const uint8_t *ACn) = 0;

    /**
         * Set the Acceptance Mask Register.
         */

    virtual void setAMn(const uint8_t *AMn) = 0;

    /**
         * Gets the Channel State from the CAN Controller.
         */

    virtual uint8_t getChannelState() = 0;

    /**
         * Gets the Status and Error Flags from the CAN Controller.
         */

    virtual void getStatusFlags(bool *_flags) = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */