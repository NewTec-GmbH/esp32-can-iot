# Main Application

- [Main Loop](#Main-Loop)
- [Adapters](#Adapters)
    - [CAN Adapter](#CAN-Adapter)
    - [NVM Adapter](#NVM-Adapter)
    - [Serial Adapter](#Serial-Adapter)

# Main Loop
This contains the standard Arduino "Setup" and "Loop" functions, which control the whole program. The instances of the Adapters and the Lawicel Protocol are also defined in this file. It is important to note that the application stops running if a catastrophioc error is encountered, for example, being unable to connect to the user-given Wireless Network

# Adapters
These are the implementations of the Lawicel Interfaces. The Protocol required one adapter of each kind to work properly:

## CAN Adapter
This file contains the methods used by the CAN Controller. 

Its objetive is to receive the Frames from the Bus and write them in the format of the Frame Struct, which gets passed onto the Lawicel Protocol for its processing. 

On the other side, it also receives the Frames from the Lawicel Protocol which get sent onto the connected Bus.

This section is also responsible for setting the user-selected configuration of the CAN Device, such as Baudrate, Filters, and current Status.

For this project, the Adapter wraps around the [Arduino-CAN](https://github.com/sandeepmistry/arduino-CAN) Library, but it has been copied onto the libs folder to be able to fully implement the Lawicel Commands for the integrated SJA1000 Controller.

## NVM Adapter
This file contains the methods for saving and retrieving data from the non-volatile memory of the ESP32, using the Preferences Library as base.

As there are some parameters that need to be saved between power cycles, such as the wireless credentials, this adapter simplifies and centralizes the access to the saved data. This is achieved using keys and directories to order and store the data, as well as the easy retrieval when requested.

## Serial Adapter
Here is the interface between the Device and Humans found. The Serial Adapter trasmits the output of the Lawicel Protocol, as well as the user input into Lawicel. For the project, two versions of the Serial Adapter have been developed: serialAdapter and WSAdapter. SerialAdapter interfaces with the Arduino Serial (UART) interface, while the WSAdapter connects to the WebSocket, so the system can be used through a Wireless network. By default, the WSAdapter is configured.