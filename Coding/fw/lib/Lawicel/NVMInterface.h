/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Interfaces
@ingroup Lawicel
@{
@file       NVMInterface.h

NVM Interface for Lawicel Protocol

* @}
***************************************************************************************************/
#ifndef NVM_INTERFACE_H
#define NVM_INTERFACE_H

/* INCLUDES ***************************************************************************************/

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/*
* Interface of the Lawicel Protocol to the NVM of the board. Defines the Methods to save and fetch  
* the initial parameters of the system.
*/
class NVMInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /**
    * Key Definition (Addresses) to be read by NVM Adapter for initialization
    */
    const String INIT_SERIAL_BAUD = "SerialBaud"; /**< Initial Serial Baudrate*/
    const String INIT_TIMESTAMP = "ToggleTime";   /**< Initial State of Timestamp*/
    const String INIT_AUTO_START = "AutoStart";   /**< Initial State of Autostart*/
    const String INIT_CAN_BAUD = "CanBaud";       /**< Initial CAN Baudrate*/
    const String INIT_FILTER_MODE = "FilterMode"; /**< Initial Filter Mode*/
    const String INIT_FILTER_ACN = "FilterACn";   /**< Initial Filter Address*/
    const String INIT_FILTER_AMN = "FilterAMn";   /**< Initial Filter Mask*/

    /* TYPES **********************************************************************************/

    /**
    * Default constructor creates instance of the class using default values.
    */
    NVMInterface()
    {
    }

    /**
    * Default destructor deletes instance of the class.
    */
    virtual ~NVMInterface()
    {
    }

    /**
    * Configures and starts the NVM Controller to use the user values.
    */
    virtual bool begin() = 0;

    /**
    * Stops the NVM Module without destroying the instance.
    */
    virtual bool end() = 0;

    /**
    * Save Data in NVM
    */
    virtual bool save(const String &name, int32_t value) = 0;

    /**
    * Save String in NVM
    */
    virtual bool save(const String &name, const String &value) = 0;

    /**
    * Read Data from NVM
    */
    virtual uint32_t readInt(const String &name) = 0;

    /**
    * Read String from NVM
    */
    virtual String readString(const String &name) = 0;

    /**
     * Delete all NVM Entries.
     */
    virtual bool clearEntries() = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* NVM_INTERFACE_H */