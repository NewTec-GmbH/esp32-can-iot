EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
Title "CAN_Bus Analyzer - Power Supply"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 3275 2825 0    50   Input ~ 0
OBD_VDD
Text Notes 4175 2300 2    50   ~ 0
12V-OBD Power Supply
Wire Wire Line
	6850 2825 6850 2875
Wire Wire Line
	6850 3175 6850 3225
$Comp
L Device:C C2
U 1 1 5F6089EB
P 6850 3025
F 0 "C2" H 6965 3071 50  0000 L CNN
F 1 "100n" H 6965 2980 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 6888 2875 50  0001 C CNN
F 3 "~" H 6850 3025 50  0001 C CNN
	1    6850 3025
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 2825 7025 2825
Text HLabel 7950 2825 2    50   Input ~ 0
Ext.5V
$Comp
L power:GND #PWR02
U 1 1 5FA1043A
P 7950 3300
F 0 "#PWR02" H 7950 3050 50  0001 C CNN
F 1 "GND" H 7955 3127 50  0000 C CNN
F 2 "" H 7950 3300 50  0001 C CNN
F 3 "" H 7950 3300 50  0001 C CNN
	1    7950 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 3225 7950 3300
Wire Wire Line
	6850 2825 6775 2825
Connection ~ 6850 2825
Wire Wire Line
	7625 2825 7950 2825
$Comp
L Regulator_Linear:LT1086-5.0 U1
U 1 1 5FA0C017
P 7325 2825
F 0 "U1" H 7325 3067 50  0000 C CNN
F 1 "LT1086-5.0" H 7325 2976 50  0000 C CNN
F 2 "Board:DPAK254P1394X457-4N" H 7325 3075 50  0001 C CIN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/1086ffs.pdf" H 7325 2825 50  0001 C CNN
	1    7325 2825
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3225 7325 3225
Wire Wire Line
	7325 3125 7325 3225
Connection ~ 7325 3225
Wire Wire Line
	7325 3225 7950 3225
$Comp
L Device:R R1
U 1 1 5FAFFDE5
P 5025 3425
F 0 "R1" H 5095 3471 50  0000 L CNN
F 1 "1k" H 5095 3380 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4955 3425 50  0001 C CNN
F 3 "~" H 5025 3425 50  0001 C CNN
	1    5025 3425
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5FB008D2
P 5025 3875
F 0 "R2" H 5095 3921 50  0000 L CNN
F 1 "100" H 5095 3830 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4955 3875 50  0001 C CNN
F 3 "~" H 5025 3875 50  0001 C CNN
	1    5025 3875
	1    0    0    -1  
$EndComp
Wire Wire Line
	5025 3575 5025 3650
Wire Wire Line
	5025 3650 5450 3650
Connection ~ 5025 3650
Wire Wire Line
	5025 3650 5025 3725
Wire Wire Line
	5025 4150 4850 4150
Wire Wire Line
	5025 3275 5025 2825
Connection ~ 5025 2825
Wire Wire Line
	5025 2825 3275 2825
Text HLabel 5450 3650 2    50   Output ~ 0
OBD_Voltage_Check
Wire Wire Line
	5025 4025 5025 4150
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5FB093DE
P 6775 2825
F 0 "#FLG01" H 6775 2900 50  0001 C CNN
F 1 "PWR_FLAG" H 6775 2998 50  0000 C CNN
F 2 "" H 6775 2825 50  0001 C CNN
F 3 "~" H 6775 2825 50  0001 C CNN
	1    6775 2825
	1    0    0    -1  
$EndComp
Connection ~ 6775 2825
Wire Wire Line
	6775 2825 5025 2825
$Comp
L Device:C C1
U 1 1 5FB0CD60
P 4650 3875
F 0 "C1" H 4765 3921 50  0000 L CNN
F 1 "10n" H 4765 3830 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 4688 3725 50  0001 C CNN
F 3 "~" H 4650 3875 50  0001 C CNN
	1    4650 3875
	1    0    0    -1  
$EndComp
Wire Wire Line
	5025 3650 4650 3650
Wire Wire Line
	4650 3650 4650 3725
Wire Wire Line
	4650 4025 4650 4150
$Comp
L power:GND #PWR01
U 1 1 5FB6777E
P 4850 4325
F 0 "#PWR01" H 4850 4075 50  0001 C CNN
F 1 "GND" H 4855 4152 50  0000 C CNN
F 2 "" H 4850 4325 50  0001 C CNN
F 3 "" H 4850 4325 50  0001 C CNN
	1    4850 4325
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4325 4850 4150
Connection ~ 4850 4150
Wire Wire Line
	4850 4150 4650 4150
$EndSCHEMATC
