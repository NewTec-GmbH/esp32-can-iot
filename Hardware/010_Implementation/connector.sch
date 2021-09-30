EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title "CAN_Bus Analyzer - Connector"
Date "2021-02-04"
Rev "1.1"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 4235 2450 2    50   Output ~ 0
VCC
$Comp
L power:GND #PWR021
U 1 1 5FB4D7F5
P 4895 2550
F 0 "#PWR021" H 4895 2300 50  0001 C CNN
F 1 "GND" H 4900 2377 50  0000 C CNN
F 2 "" H 4895 2550 50  0001 C CNN
F 3 "" H 4895 2550 50  0001 C CNN
	1    4895 2550
	1    0    0    -1  
$EndComp
Text HLabel 4235 2650 2    50   BiDi ~ 0
BUS_L
Text HLabel 4235 2750 2    50   BiDi ~ 0
BUS_H
$Comp
L Connector:Conn_01x04_Female J2
U 1 1 615EF38D
P 3595 2550
F 0 "J2" H 3487 2835 50  0000 C CNN
F 1 "Conn_01x04_Female" H 3487 2744 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3595 2550 50  0001 C CNN
F 3 "~" H 3595 2550 50  0001 C CNN
	1    3595 2550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3795 2750 4235 2750
Wire Wire Line
	3795 2650 4235 2650
Wire Wire Line
	3795 2450 4235 2450
Wire Wire Line
	3795 2550 4895 2550
$EndSCHEMATC
