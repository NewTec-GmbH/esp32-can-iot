# Hardware Description

- [Architecture](#Architecture)
- [Implementation](#Implementation)
    - [Components](#Components)
    - [Version 1.0](#Version-1.0)
    - [Version 1.1](#Version-1.1)

# Architecture
![Hardware_Overview](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/NewTec-GmbH/esp32-can-iot/Playground/Coding/fw/doc/design/Hardware_Overview.plantuml)

This deviced is based on the ESP32­-WROOM-­32E processor, which has a diverse number of interfaces such as digital and analog inputs and output, as well as an integrated CAN bus controller and WiFi capabilities, between many other characteristics. The ESP32 additionally needs a CAN Transceiver to receive the data from the CAN-H and CAN-L lines. 

The connection to the CAN Bus is done through a DSUB-9 connector, which is the standard for CAN busses. This connector can also provide a the device with power, but with a 12V voltage which has to be reduced to 5V before going into the ESP32 DevKit, where it will be transformed again into 3.3V.

# Implementation
The Project was developed using KiCad and all its Toolchain. This includes Eeschema, Pcbnew and GerbView.

## Components

The following components were selected for this project's PCB. Smaller components such as resistors and capacitors are not included in this list, but can be found on the [BOM](./010_Implementation/BOM.xlsx).

| Component | Description |
| :---------------: | :---------------: |
| ESP32-DEVKITC-32D | Microprocessor used. Connected using socket strips |
| SS24 | Safety diode for Microprocessor in case more than one power supply is being used |
| TPS62160DGK | 12V 1A Step-down Converter |
| R452002 | 12V Fuse |
| SMAJ16A | Protective Diode at 12V input |
| G5V-2-DC5 | Relay for "smart" switching between CAN and OBD Pinout |
| BC817 | Transistor for Relay control |
| 1N4148 | Diodes for Relay protection |
| DSUB9 | Standard connector for CAN-Bus |
| SN65HVD233-HT | CAN Transceiver |
| 744242220 | Toroid for CAN-Bus Filtering |
| PESD1CAN | Diode for CAN-Bus Filtering |
| AST 045-08 | 8-position connector with latches for GPIO |

## Version 1.0
![Version 1.0_Front](..\Coding\fw\doc\Media\PCB_Front.png) 
![Version 1.0_Back](..\Coding\fw\doc\Media\PCB_Back.png)

## Version 1.1
2 Main Errors were found on Version 1.0:
* Tx and Rx Signals from the CAN Transceiver were inverted
* The 5V Supply for the Relays was located after a diode, which prevented the use of the relays when connected only through USB Supply. 

In the new version were these two changes made and after testing it resolved in success.

Other minor errors were also repaired, such as the size of the holes for AST 045-08 Connector which were too small. 