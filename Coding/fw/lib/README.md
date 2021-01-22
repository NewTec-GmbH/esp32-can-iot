# Libraries

- [CAN](#CAN)
- [IO](#IO)
- [Lawicel](#Lawicel)
- [Settings](#Settings)
- [Test](#Test)
- [WebServer](#WebServer)

# CAN
This folder contains an adaptation of the [Arduino-CAN](https://github.com/sandeepmistry/arduino-CAN) Library to be fully compatible with the Project. Changes made include access to the Raw Buffer, Return values when parsing frames and access to writing the registers of the SJA1000 CAN Controller.

# IO
Here is the HAL of the Project, providing an implementation of the Arduino and ESP32 GPIO functions. 

# Lawicel
The Lawicel Protocol can be found here, as well as the 3 Interfaces needed for the correct operation of the protocol.

# Settings
The FlashMem Module interfaces directly with the Preferences Library, native to the ESP32 System. The WLAN Module takes care of the wireless communication for the device.

# Test
This project contains Unit Tests that run on the native environment declared in the .ini file. In this case, it runs on Windows, therefore an implementation of Arduino-Native functions is needed, for example, the implementation of the Class 
WString.

# WebServer
Using the WLAN Module as basis, the WebServer is run and configured in here, running in parallel from the rest of the program. It is an implementation of the [AsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) Library.