# Connection to CANHacker Software

CANHacker is a Graphical Interface for CAN Adapters that communicate using the Lawicel Protocol, such as this project.

In order to connect to this application, the Serial Adapter must be used instead of the WebSocket.

## Main.cpp
The correct "main.cpp" would look like this:

```cpp

// Includes
#include <Arduino.h>
#include "Lawicel.h"
#include "Board.h"
#include "SerialAdapter.h"
#include "CANAdapter.h"
#include "NVMAdapter.h"

static SerialAdapter gSerialAdapter; /**< Serial Adapter Instance */
static CANAdapter gSja1000Adapter;   /**< CAN Adapter Instance */
static NVMAdapter gFlashAdapter;     /**< NVM Adapter Instance */

/** Lawicel Protocol Instance */
static Lawicel gProtocolLawicel(gSerialAdapter, gSja1000Adapter, gFlashAdapter);

/**
 *  Initialization of Application
 */
void setup()
{
    Board::init();
    if (!gProtocolLawicel.begin())
    {
        Board::haltSystem();
    }
}

/**
 *  Application Loop
 */
void loop()
{   
    gProtocolLawicel.executeCycle();
}
```

## CANHAcker

Using the latest CANHacker Version (V.2.00.02), the connection is performed in two steps:

- Settings Windows: Set the `COM Port`, `Serial Baudrate` (default. 115200 bit/s), and `CAN Baudrate`. Other options such as "Listen Only" and "Timestamp" can be selected here too.

- Connect Button: Performs the connection to the device itself.

To check if your device is succesfully connected, the bottom bar should display the current state as "Connected to <<`CAN Baudrate`>> kbit/s" and the current Firmware Version (current: V1.01)