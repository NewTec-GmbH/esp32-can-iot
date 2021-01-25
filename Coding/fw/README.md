# Firmware Description

- [Software Architecture](#Software-Architecture)
	- [Software Overview](#Software-Overview)
	- [Applicaton Entry Points Processing](#Applicaton-Entry-Points-Processing)
- [Detailed Design](#Detailed-Design)
	- [Main Application](#Main-Application)
	- [Lawicel](#Lawicel)
	- [Web Server](#Web-Server)
	- [Web Socket](#Web-Socket)
- [Software-Hardware Integration](#Software-Hardware-Integration)

# Software Architecture
## Software Overview
![Hierarchy](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/FW_Hierarchy.plantuml)

The Firmware is composed by 4 main layers: Application, Modules, Service and HAL. As the software is built on the Arduino Framework, the Arduino.h Library is found on the HAL as the interfacing class between hardware and software. This library contains a great number of sub-libraries which independently control each piece of hardware.

On the Service Layer we can find the Board Class, as an abstraction from the Arduino library to be able to use only the needed GPIO adn their respective methods. Here we can also find the library for the CAN Controller and the IP Stack used by the Webserver.

On the Modules Layer we find the implemented classes: Lawicel and ESPAsyncWebServer, which use the Service Layer to effectively transmit information. Both these Classes are controlled by the Application Layer, which ultimately defines the behavior of the system.

Detailed information on the implemented libraries can be found in the [Library](./lib/README.md) Documentation, as well as online in the case of the Arduino Library.

## Applicaton Entry Points Processing
The following diagram pictures the Entry Points called by the Application while the programm is running. The code where this sequence can be found is contained in the [main.cpp](./src/main.cpp) file. 

![MainLoop](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Mainloop_Sequence.plantuml)

The process is divided in two main sections, as per Arduino Framework standard:

### Setup
This section is only called once everytime the system reboots. It initializes the different Modules that compose the system, and expects a Boolean **True** return from each Module in order to continue with the normal routine. If any of the Modules returns a **False** value instead, a System Halt is called from the Board Class.

The Board initialization sets up the HAL by defining which pins are going to be use and their respective modes, for example, Pin 2 is configured as an output in order to be used as the Error LED.

The Lawicel Protocol in its initialization routine also configures each of the Adapters passed as arguments on its constructor. This means that here is the CAN Controller started, as well as the Web Server and Socket when the respective adapter is passed. In the case of having Auto-start configured in Lawicel, the saved parameters are retrieved from the NVM and set up accordingly. Each of these processes is expected to return a **True** value. 

### Loop
As its name describes, the loop is called in a cyclic manner every time it finished its routine. Here is the Lawicel Cycle called, where the communication from/to the user occurs. The Loop is also constantly checking on the Wireless connection to the configure network to ensure no data-loss. And finally, it checks if a system restart is called from the Captive Portal. 


# Detailed Design
## Main Application

The system follows the following procedure during the Setup:

![Setup](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/SetUpProcess.plantuml)

it is important to note that the Error LED can also be set during the looped programm if the wireless connection is lost and was not possible to reconnect after a pre-defined time. The states of the system can be seen in the next diagram.

![StateMachine](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/StateMachine.plantuml)

## Lawicel

The Lawicel Module implements one of the most important components of this project. The Lawicel Protocol is used to communicate witha CAN Bus using ASCII symbols, as each command that is sent has a specific format which is interpreted by the module. 

The module is composed by 4 main components: the implementation of the protocol, an interface for serial communication, an interface for CAN communication and an interface for Non-Volatile Memory. These Interfaces define the functions that the adapters must perform and are directly used by the protocol. Through the use of these, it is possible to treat the Lawicel Module as a completely independent component to which different adapters can be connected depending on the case and hardware used.


![Arch_Lawicel](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Architecture_Lawicel.plantuml)

In this case, the adapters are implemented for the ESP32 and the libraries used by it. In the case of the Serial Adapter, it employs directly th Serial hardware from the Arduino Library. For the NVM Adapter, the ESP32 offers a library for managing flash memory using keys, which is called "Preferences". Finally the CAN Adapter is an abstraction from sandeepmistry's [arduino-CAN](https://github.com/sandeepmistry/arduino-CAN), which manages the memory-mapped SJA1000 CAN Controller.

## Web Server
The second most important module is the Webserver. The ESP32 offers the capability of hosting a server that manages the requests asynchron, meaning that it does not block the other tasks that the processor has to complete. This server is an implementation of me-no-dev's [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer).

![Arch_Webserver](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Architecture_Webserver.plantuml)

The server uses 3 service classes: WebConfig to store the credentials on the flash memory, Pages to serve the websites accesible while on Station Mode, and the CaptivePortal which serves only one website. The purpose of the Captive Portal is to provide the users with an interface to change the credentials for the Station Mode. In this module is the Settings class also uused to store the credentials, and the Serial Peripheral Interface Flash File System (SPIFFS) which stores the Webpages as HTML files and sends them to the web clients when requested.


![Arch_Webpages](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Architecture_Webpages.plantuml)

## Web Socket
![Arch_Websocket](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Architecture_Websocket.plantuml)


# Software-Hardware Integration
![UseCaseSoftware](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/UseCaseSoftware.plantuml)

Regarding the software, the device sets different LEDs as to show the state of the system, for example to show when a system critical error has occurred or when the Access Point Mode is enabled. The system also has communication with a CAN Transceiver which performs the connection to the bus. The user plays an important role as the they must configure the bus characteristics as well as the needed credentials for the Station Mode. 