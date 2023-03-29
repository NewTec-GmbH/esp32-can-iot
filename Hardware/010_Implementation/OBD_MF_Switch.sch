EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title "CAN_Bus Analyzer - Power Supply - OBD MF Switch"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 3125 1950 0    50   Input ~ 0
V_IN
Text HLabel 5950 4675 3    50   Input ~ 0
GND
Text HLabel 7725 1950 2    50   Output ~ 0
V_OUT
$Comp
L Device:R R2
U 1 1 5F5750B9
P 5950 3400
F 0 "R2" H 6020 3446 50  0000 L CNN
F 1 "220" H 6020 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 5880 3400 50  0001 C CNN
F 3 "~" H 5950 3400 50  0001 C CNN
	1    5950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3550 5950 3675
Wire Wire Line
	3125 1950 4525 1950
Connection ~ 5950 1950
Wire Wire Line
	5950 3675 6925 3675
Wire Wire Line
	6925 3675 6925 2250
Connection ~ 5950 3675
Wire Wire Line
	6925 2250 5100 2250
Wire Wire Line
	5550 3375 4525 3375
Wire Wire Line
	4525 3375 4525 2800
Wire Wire Line
	5550 3375 5550 2850
Connection ~ 4525 1950
Wire Wire Line
	4525 1950 4900 1950
$Comp
L Device:R R1
U 1 1 5F5806DB
P 4525 2650
AR Path="/5F52EFB7/5F56212F/5F5806DB" Ref="R1"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5806DB" Ref="R?"  Part="1" 
F 0 "R1" H 4595 2696 50  0000 L CNN
F 1 "220" H 4595 2605 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 4455 2650 50  0001 C CNN
F 3 "~" H 4525 2650 50  0001 C CNN
	1    4525 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4525 2500 4525 1950
$Comp
L Board:FDV304P U3
U 1 1 5F5BC3D1
P 5100 2050
F 0 "U3" V 5232 1906 50  0000 R CNN
F 1 "FDV304P" H 5100 2050 50  0001 L BNN
F 2 "Board:SOT23-3" H 5100 2050 50  0001 L BNN
F 3 "" H 5100 2050 50  0001 C CNN
	1    5100 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5100 2150 5100 2250
Wire Wire Line
	5200 1950 5950 1950
$Comp
L Board:FDV304P U5
U 1 1 5F5C0F63
P 6925 2050
F 0 "U5" H 6925 2050 50  0001 L BNN
F 1 "FDV304P" H 6925 2050 50  0001 L BNN
F 2 "Board:SOT23-3" H 6925 2050 50  0001 L BNN
F 3 "" H 6925 2050 50  0001 C CNN
	1    6925 2050
	0    1    -1   0   
$EndComp
Wire Wire Line
	7125 1950 7725 1950
Wire Wire Line
	6925 2150 6925 2250
Connection ~ 6925 2250
Wire Wire Line
	5950 1950 6825 1950
$Comp
L Board:FDV304P U4
U 1 1 5F5C2DDB
P 5850 2850
F 0 "U4" H 5850 2850 50  0001 L BNN
F 1 "FDV304P" H 5850 2850 50  0001 L BNN
F 2 "Board:SOT23-3" H 5850 2850 50  0001 L BNN
F 3 "" H 5850 2850 50  0001 C CNN
	1    5850 2850
	1    0    0    1   
$EndComp
Wire Wire Line
	5950 3050 5950 3250
Wire Wire Line
	5550 2850 5750 2850
Wire Wire Line
	5950 1950 5950 2750
$Comp
L Board:2N7002 Q1
U 1 1 5F5C5255
P 5750 3975
F 0 "Q1" H 5750 4287 50  0000 C CNN
F 1 "2N7002" H 5750 4196 50  0000 C CNN
F 2 "Board:SOT23-3" H 5750 3975 50  0001 L BNN
F 3 "" H 5750 3975 50  0001 C CNN
	1    5750 3975
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3675 5950 3875
Wire Wire Line
	5950 4075 5950 4675
Wire Wire Line
	5550 3375 5550 4075
Connection ~ 5550 3375
$EndSCHEMATC
