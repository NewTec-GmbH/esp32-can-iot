# Firmware Description

- [Use Case](#Use-Case)
- [Architecture](#Architecture)
	- [Software Overview](#Software-Overview)
	- [Sequence Diagram](#Sequence-Diagram)
- [Detailed Design](#Detailed-Design)
	- [Main Application](#Main-Application)
	- [Lawicel](#Lawicel)
	- [Web Server](#Web-Server)
	- [Web Socket](#Web-Socket)
- [Implementation](#Implementation)
	- [Lawicel](#Lawicel)
	- [Web Server](#Web-Server)
	- [Web Socket](#Web-Socket)

# Use-Case
![UseCaseSoftware](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/UseCaseSoftware.plantuml)

Regarding the software, the device sets different LEDs as to show the state of the system, for example to show when a system critical error has occurred or when the Access Point Mode is enabled. The system also has communication with a CAN Transceiver which performs the connection to the bus. The user plays an important role as the they must configure the bus characteristics as well as the needed credentials for the Station Mode. 

# Architecture
## Software Overview
![Hierarchy](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/FW_Hierarchy.plantuml)

The Firmware is composed by 4 main layers: Application, Modules, Service and HAL. As the software is built on the Arduino Framework, the Arduino.h Library is found on the HAL as the connection between hardware and the rest of the software. This library contains a great number of sub-libraries which independently control each piece of hardware.

On the Service Layer we can find the Board Class, as an abstraction from the Arduino library to be able to use only the needed GPIO. here we can also find the library for the CAN Controller and the IP Stack used by the Webserver.

On the Modules Layer we find the implemented classes: Lawicel and Webserver, which use the Service Layer to effectively transmit information. Both these Classes are finaly controlled by the Application Layer, which ultimately defines the behavior of the system.

## Sequence Diagram
![MainLoop](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Mainloop_Sequence.plantuml)

This Diagram shows the sequence that the application follows, starting by initializing each individual module. The setup process expects a "true" response from each module initilization in order to be able to start. If any module fails to start, the error LED will be set and the system will not continue working. 

During the loop sequence, the system calls the Lawicel Cycle to read the CAN bus and the Serial interface. It also handles the requests of the DNS Server, even when the Webserver is running and managing the requests in a parallel task.


# Detailed Design
## Main Application

The system follows the following procedure during the module setup:

![Setup](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/SetUpProcess.plantuml)

it is important to note that the Error LED can alo be set during the looped programm if the wireless connection is lost and was not possible to reconnect after a pre-defined time. The states of the system can be seen in the next diagram.

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

# Implementation
## Lawicel

## Web Server

## Web Socket
