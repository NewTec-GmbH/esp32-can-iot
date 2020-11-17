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
![UseCase](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/UseCase.plantuml)

# Architecture
## Hardware Overview
![Hardware_Overview](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Hardware_Overview.plantuml)

## Software Overview
![Hierarchy](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/FW_Hierarchy.plantuml)

## Sequence Diagram
![MainLoop](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Mainloop.plantuml)


# Detailed Design
## Main Application
![Setup](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/SetUpProcess.plantuml)

![StateMachine](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/State_Machine.plantuml)

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
