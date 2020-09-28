EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 8
Title "CAN_Bus Analyzer - USB-Interface"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2775 4850 1    50   Output ~ 0
USB_VDD
Text HLabel 2775 6225 3    50   Output ~ 0
USB_GND
Text HLabel 1600 2325 0    50   Input ~ 0
Tx
Text HLabel 1600 2525 0    50   Output ~ 0
Rx
$Comp
L Isolator:ADuM1201AR U4
U 1 1 5F5CE1F8
P 3000 2425
F 0 "U4" H 3000 2892 50  0000 C CNN
F 1 "ADuM1201AR" H 3000 2801 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3000 2025 50  0001 C CIN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/ADuM1200_1201.pdf" H 3000 2325 50  0001 C CNN
	1    3000 2425
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2500 2325 1600 2325
Wire Wire Line
	2500 2525 1600 2525
Text GLabel 1850 2225 0    50   Input ~ 0
VCC
Text GLabel 1850 2625 0    50   Input ~ 0
GND
Wire Wire Line
	1850 2625 2500 2625
Wire Wire Line
	2500 2225 1850 2225
$Comp
L Interface_USB:FT232RL U5
U 1 1 5F5D16EC
P 8100 2925
F 0 "U5" H 8100 4106 50  0000 C CNN
F 1 "FT232RL" H 8100 4015 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 9200 2025 50  0001 C CNN
F 3 "https://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT232R.pdf" H 8100 2925 50  0001 C CNN
	1    8100 2925
	-1   0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J4
U 1 1 5F5D738E
P 4875 5375
F 0 "J4" H 4645 5364 50  0000 R CNN
F 1 "USB_B_Micro" H 4645 5273 50  0000 R CNN
F 2 "" H 5025 5325 50  0001 C CNN
F 3 "~" H 5025 5325 50  0001 C CNN
	1    4875 5375
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4875 5775 4875 5900
Wire Wire Line
	2775 5175 2775 4850
Wire Wire Line
	2775 6225 2775 5900
Wire Wire Line
	4975 5775 4975 5900
Wire Wire Line
	4975 5900 4875 5900
Connection ~ 4875 5900
NoConn ~ 4575 5575
Wire Wire Line
	4575 5375 3650 5375
Wire Wire Line
	4575 5475 3650 5475
Text Label 3650 5375 0    50   ~ 0
D+
Text Label 3650 5475 0    50   ~ 0
D-
Text Label 2400 5175 0    50   ~ 0
V_USB
Text Label 2400 5900 0    50   ~ 0
GND_USB
Wire Wire Line
	8900 2525 9500 2525
Wire Wire Line
	8900 2625 9500 2625
Text Label 9500 2525 2    50   ~ 0
D+
Text Label 9500 2625 2    50   ~ 0
D-
Wire Wire Line
	8000 1925 8000 1650
Wire Wire Line
	8200 1925 8200 1650
Wire Wire Line
	8200 1650 8000 1650
Connection ~ 8000 1650
Wire Wire Line
	8000 1300 8000 1650
Text Label 8000 1300 3    50   ~ 0
V_USB
Wire Wire Line
	7900 3925 7900 4200
Wire Wire Line
	7900 4200 8000 4200
Wire Wire Line
	8100 3925 8100 4200
Wire Wire Line
	8000 3925 8000 4200
Connection ~ 8000 4200
Wire Wire Line
	8000 4200 8100 4200
Text Label 8000 4625 1    50   ~ 0
GND_USB
Wire Wire Line
	8000 4200 8000 4625
Wire Wire Line
	8300 3925 8300 4200
Wire Wire Line
	8300 4200 8100 4200
Connection ~ 8100 4200
Wire Wire Line
	8900 2925 9500 2925
Text Label 9500 2925 2    50   ~ 0
V_USB
Wire Wire Line
	8900 3625 8900 4200
Wire Wire Line
	8900 4200 8300 4200
Connection ~ 8300 4200
NoConn ~ 8900 3125
NoConn ~ 8900 3325
Wire Wire Line
	3500 2225 4100 2225
Wire Wire Line
	3500 2625 4100 2625
Text Label 4100 2225 2    50   ~ 0
V_USB
Text Label 4100 2625 2    50   ~ 0
GND_USB
Wire Wire Line
	3500 2325 7300 2325
Wire Wire Line
	4250 2225 4250 2525
Wire Wire Line
	4250 2225 7300 2225
Wire Wire Line
	3500 2525 4250 2525
NoConn ~ 7300 3225
NoConn ~ 7300 3325
NoConn ~ 7300 3425
NoConn ~ 7300 3525
NoConn ~ 7300 3625
NoConn ~ 7300 2425
NoConn ~ 7300 2525
NoConn ~ 7300 2625
NoConn ~ 7300 2725
NoConn ~ 7300 2825
NoConn ~ 7300 2925
$Comp
L Device:C C2
U 1 1 5F5F5B6F
P 9150 1775
F 0 "C2" H 9265 1821 50  0000 L CNN
F 1 "100n" H 9265 1730 50  0000 L CNN
F 2 "" H 9188 1625 50  0001 C CNN
F 3 "~" H 9150 1775 50  0001 C CNN
	1    9150 1775
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 5675 3150 5900
Wire Wire Line
	3150 5375 3150 5175
Connection ~ 3150 5175
Connection ~ 3150 5900
Wire Wire Line
	2400 5900 2775 5900
Wire Wire Line
	2400 5175 2775 5175
Wire Wire Line
	8900 2225 9150 2225
Wire Wire Line
	9150 2225 9150 1925
Wire Wire Line
	9150 1625 9150 1125
Text Label 9150 1125 3    50   ~ 0
GND_USB
Connection ~ 2775 5175
Wire Wire Line
	2775 5175 3150 5175
Wire Wire Line
	3150 5175 4575 5175
Connection ~ 2775 5900
Wire Wire Line
	2775 5900 3150 5900
Wire Wire Line
	3150 5900 4875 5900
Text Notes 3500 4400 0    50   ~ 0
USB Connector
Text Notes 2400 1700 0    50   ~ 0
Isolation of Serial Data Lines
Text Notes 7675 1000 0    50   ~ 0
USB-Serial Interface
$Comp
L Device:C C?
U 1 1 5F60A2AC
P 3150 5525
AR Path="/5F52EFB7/5F60A2AC" Ref="C?"  Part="1" 
AR Path="/5F52F0E2/5F60A2AC" Ref="C1"  Part="1" 
F 0 "C1" H 3265 5571 50  0000 L CNN
F 1 "100n" H 3265 5480 50  0000 L CNN
F 2 "" H 3188 5375 50  0001 C CNN
F 3 "~" H 3150 5525 50  0001 C CNN
	1    3150 5525
	1    0    0    -1  
$EndComp
$EndSCHEMATC
