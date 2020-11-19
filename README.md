# ESP CAN-Analyzer
An ESP32 based interface between CAN-Bus and IoT environments.

- [Technical Specifications](#Technical-Specifications)
	- [Software Requirements](#Software-Requirements)
	- [Hardware Requirements](#Hardware-Requirements)
	- [Extra/Optional Requirements](#Extra/Optional-Requirements)
- [Use Case](#Use-Case)
- [Architecture](#Architecture)
	- [Hardware Overview](#Hardware-Overview)
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
	- [Hardware](#Hardware)


# Technical Specifications 
## Software Requirements
* Support Standard and Extended frame formats
* WiFi Mode Selection (AP or STA)
* Support *Lawicel* Protocol
* HTTP Server over WiFi
* Server shall support authentication
* AP credentials changed through Server
* STA credentials changed through Server
* Bit Timing and Filters changed through Server
* CAN monitoring page (depending on available memory)
* Send CAN frame on demand
* Send CAN frame periodically
* CAN BUS Termination on Demand

## Hardware Requirements
* ESP32-based
* ISO 11898 Compliant (CAN up to 1 Mbps)
* CAN Bus Termination on Demand
* Support CAN through DSUB-9
* Support OBD through DSUB-9
* Bus-off State
* ISO 7637 compliant (Road vehicles -- Electrical disturbances from conduction and coupling)
* Control Button
* Red Error LED
* 4 GPIOs via Clamps

## Extra/Optional Requirements
* Identification of Error Message
* Reset through Webserver (Save and Restart)
* View OBD Messages (.dbc file?)
* LAWICEL over websocket/mqtt (to nodejs/node-red)

# Use Case
![UseCaseAnalyzer](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/UseCaseAnalyzer.plantuml)

The use case for this project is based on the direct connection to a CAN Bus, in order to obtain the information being sent between the members of this bus. On the other side of this communication we find a Serial Interface or a Websocket Interface which presents the information to the user. The user has to provide the device with the characteristics of the Bus it is connected to, in order to correctly acquire the data.

![UseCaseSoftware](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/UseCaseSoftware.plantuml)

Regarding the software, the device sets different LEDs as to show the state of the system, for example to show when a system critical error has occurred or when the Access Point Mode is enabled. The system also has communication with a CAN Transceiver which performs the connection to the bus. The user plays an important role as the they must configure the bus characteristics as well as the needed credentials for the Station Mode. 

# Architecture
## Hardware Overview
![Hardware_Overview](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Hardware_Overview.plantuml)

This deviced is based on the ESP32­-WROOM-­32E processor, which has a diverse number of interfaces such as digital and analog inputs and output, as well as an integrated CAN bus controller and WiFi capabilities, between many other characteristics. The ESP32 additionally needs a CAN Transceiver to receive the data from the CAN-H and CAN-L lines. 

The connection to the CAN Bus is done through a DSUB-9 connector, which is the standard for CAN busses. This connector can also provide a the device with power, but with a 12V voltage which has to be reduced to 5V before going into the ESP32 DevKit, where it will be transformed again into 3.3V.

As user interfaces we use an USB connection for serial communication with a computer, or alternatively, a wireless connection to the integrated server and Websocket. Both perform the same function of communicating information from/to the CAN bus. JTAG pins have also been included to facilitate debugging. Finally we have a button to define the WiFi mode setting and 3 LED indicators to show the state of the system.

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
![Setup](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/SetUpProcess.plantuml)

![StateMachine](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/StateMachine.plantuml)

## Lawicel
![Arch_Lawicel](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Architecture_Lawicel.plantuml)

## Web Server
![Arch_Webserver](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Architecture_Webserver.plantuml)

![Arch_Webpages](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Architecture_Webpages.plantuml)

## Web Socket
![Arch_Websocket](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Architecture_Websocket.plantuml)

# Implementation
## Lawicel

## Web Server

## Web Socket
