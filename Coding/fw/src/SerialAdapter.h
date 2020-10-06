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
#ifndef SERIAL_ADAPTER_H
#define SERIAL_ADAPTER_H

/* INCLUDES ***************************************************************************************/
#include <Lawicel.h>

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

class SerialAdapter : public SerialInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /**
         * Default constructor.
         */
    SerialAdapter() : m_name() 
    {

    }

    /**
         * Default destructor.
         */
    ~SerialAdapter();

    void send(char *str);

    void setBaudrate(long *_baudrate);

    uint8_t read(char *Buffer);

protected:
private:
    String  m_name;
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* XXXXX_H */