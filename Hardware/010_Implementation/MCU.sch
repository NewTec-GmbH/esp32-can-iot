EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
Title "CAN_Bus Analyzer - MCU"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4225 2075 4950 2075
Text Label 4950 2075 2    50   ~ 0
WiFi_Mode
Wire Wire Line
	4225 2975 4950 2975
Wire Wire Line
	4950 2375 4225 2375
Wire Wire Line
	4225 2275 4950 2275
Text Label 2375 2275 2    50   ~ 0
GPIO_4
Text Label 4950 2375 2    50   ~ 0
Ind_AP_Mode
Text Label 4950 2275 2    50   ~ 0
Ind_STA_Mode
Text Label 4950 2975 2    50   ~ 0
Ind_Error
NoConn ~ 2625 1775
NoConn ~ 2625 1875
NoConn ~ 4225 3375
NoConn ~ 4225 3275
NoConn ~ 4225 3175
NoConn ~ 4225 2875
NoConn ~ 4225 2675
NoConn ~ 4225 2575
NoConn ~ 4225 2175
$Comp
L Device:LED D3
U 1 1 5F53E298
P 7865 2140
F 0 "D3" V 7904 2022 50  0000 R CNN
F 1 "LED" V 7813 2022 50  0000 R CNN
F 2 "LED_SMD:LED_1806_4516Metric_Pad1.57x1.80mm_HandSolder" H 7865 2140 50  0001 C CNN
F 3 "~" H 7865 2140 50  0001 C CNN
	1    7865 2140
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D4
U 1 1 5F540592
P 8365 2140
F 0 "D4" V 8404 2022 50  0000 R CNN
F 1 "LED" V 8313 2022 50  0000 R CNN
F 2 "LED_SMD:LED_1806_4516Metric_Pad1.57x1.80mm_HandSolder" H 8365 2140 50  0001 C CNN
F 3 "~" H 8365 2140 50  0001 C CNN
	1    8365 2140
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D5
U 1 1 5F5426B6
P 8865 2140
F 0 "D5" V 8904 2022 50  0000 R CNN
F 1 "LED" V 8813 2022 50  0000 R CNN
F 2 "LED_SMD:LED_1806_4516Metric_Pad1.57x1.80mm_HandSolder" H 8865 2140 50  0001 C CNN
F 3 "~" H 8865 2140 50  0001 C CNN
	1    8865 2140
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R15
U 1 1 5F542B92
P 7865 1740
F 0 "R15" H 7935 1786 50  0000 L CNN
F 1 "220" H 7935 1695 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 7795 1740 50  0001 C CNN
F 3 "~" H 7865 1740 50  0001 C CNN
	1    7865 1740
	1    0    0    -1  
$EndComp
$Comp
L Device:R R16
U 1 1 5F5436A0
P 8365 1740
F 0 "R16" H 8435 1786 50  0000 L CNN
F 1 "220" H 8435 1695 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 8295 1740 50  0001 C CNN
F 3 "~" H 8365 1740 50  0001 C CNN
	1    8365 1740
	1    0    0    -1  
$EndComp
$Comp
L Device:R R17
U 1 1 5F543C42
P 8865 1740
F 0 "R17" H 8935 1786 50  0000 L CNN
F 1 "220" H 8935 1695 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 8795 1740 50  0001 C CNN
F 3 "~" H 8865 1740 50  0001 C CNN
	1    8865 1740
	1    0    0    -1  
$EndComp
Wire Wire Line
	7865 1890 7865 1990
Wire Wire Line
	8365 1890 8365 1990
Wire Wire Line
	8865 1890 8865 1990
Wire Wire Line
	7865 1490 7865 1590
Wire Wire Line
	7365 1490 7865 1490
Wire Wire Line
	8865 1490 8865 1590
Connection ~ 7865 1490
Wire Wire Line
	7865 1490 8365 1490
Wire Wire Line
	8365 1490 8365 1590
Connection ~ 8365 1490
Wire Wire Line
	8365 1490 8865 1490
Text Label 7865 3090 1    50   ~ 0
Ind_Error
Text Label 8365 3090 1    50   ~ 0
Ind_AP_Mode
Text Label 8865 3090 1    50   ~ 0
Ind_STA_Mode
Wire Wire Line
	7865 2290 7865 3090
Wire Wire Line
	8365 2290 8365 3090
Wire Wire Line
	8865 2290 8865 3090
Wire Wire Line
	3050 5650 3775 5650
Text Label 3775 5650 2    50   ~ 0
WiFi_Mode
$Comp
L Device:R R10
U 1 1 5F54B0C7
P 3050 5875
F 0 "R10" H 3120 5921 50  0000 L CNN
F 1 "220" H 3120 5830 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 2980 5875 50  0001 C CNN
F 3 "~" H 3050 5875 50  0001 C CNN
	1    3050 5875
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 6025 3050 6050
$Comp
L Switch:SW_Push SW1
U 1 1 5F54C857
P 3050 5350
F 0 "SW1" V 3096 5302 50  0000 R CNN
F 1 "SW_Push" V 3005 5302 50  0000 R CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_CK_KSC7xxJ" H 3050 5550 50  0001 C CNN
F 3 "~" H 3050 5550 50  0001 C CNN
	1    3050 5350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3050 5550 3050 5650
Wire Wire Line
	3050 5150 3050 4950
Text Notes 4000 1100 2    50   ~ 0
ESP-WROOM-32 Micro-Controller
Text Notes 8565 1215 2    50   ~ 0
Status LEDs
Text Notes 3350 4650 2    50   ~ 0
WiFi-Mode Button
NoConn ~ 4225 1775
Wire Wire Line
	4225 2475 4950 2475
Wire Wire Line
	4950 2775 4225 2775
Text HLabel 4950 2775 2    50   Output ~ 0
CAN_Tx
Text HLabel 4950 2475 2    50   Input ~ 0
CAN_Rx
Text GLabel 3050 4950 1    50   Input ~ 0
VCC
Text GLabel 3050 6725 3    50   Input ~ 0
GND
Text GLabel 7365 1490 0    50   Input ~ 0
GND
Wire Wire Line
	4225 1575 4850 1575
$Comp
L Board:ESP32-DEVKITC-32D U14
U 1 1 5F52F5CE
P 3425 2475
F 0 "U14" H 3425 3642 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 3425 3551 50  0000 C CNN
F 2 "Board:MODULE_ESP32-DEVKITC-32D" H 3425 2475 50  0001 L BNN
F 3 "Espressif Systems" H 3425 2475 50  0001 L BNN
F 4 "4" H 3425 2475 50  0001 L BNN "Field4"
	1    3425 2475
	1    0    0    -1  
$EndComp
Text Label 2375 2475 2    50   ~ 0
GPIO_2
Text Label 2375 2575 2    50   ~ 0
GPIO_1
Text Label 2375 2375 2    50   ~ 0
GPIO_3
Wire Wire Line
	1350 2275 2625 2275
Wire Wire Line
	1900 2675 1900 2875
Wire Wire Line
	1350 2775 1625 2775
Wire Wire Line
	1625 2775 1625 1750
Text Label 2275 2875 2    50   ~ 0
GND
Wire Wire Line
	2625 2775 2125 2775
Wire Wire Line
	2625 2675 2125 2675
Wire Wire Line
	2625 2975 2125 2975
Wire Wire Line
	4225 3075 4950 3075
Text Label 2125 2775 0    50   ~ 0
MTDI
Text Label 2125 2975 0    50   ~ 0
MTCK
Text Label 2125 2675 0    50   ~ 0
MTMS
Text Label 4950 3075 2    50   ~ 0
MTDO
NoConn ~ 2625 3075
NoConn ~ 2625 3175
NoConn ~ 2625 3275
NoConn ~ 2625 2075
NoConn ~ 2625 1975
NoConn ~ 2625 1675
NoConn ~ 4225 1875
NoConn ~ 4225 1975
$Comp
L Device:C C7
U 1 1 5F5C9535
P 3050 6200
F 0 "C7" H 3165 6246 50  0000 L CNN
F 1 "100n" H 3165 6155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 3088 6050 50  0001 C CNN
F 3 "~" H 3050 6200 50  0001 C CNN
	1    3050 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 6725 3050 6350
Connection ~ 3050 5650
Wire Wire Line
	3050 5650 3050 5725
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J4
U 1 1 5F5CC4A5
P 9100 5025
F 0 "J4" H 9150 4600 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 9150 4691 50  0000 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_2x05_P1.00mm_Vertical" H 9100 5025 50  0001 C CNN
F 3 "~" H 9100 5025 50  0001 C CNN
	1    9100 5025
	-1   0    0    1   
$EndComp
$Comp
L Device:R R11
U 1 1 5F5CD98B
P 7675 4625
F 0 "R11" V 7468 4625 50  0000 C CNN
F 1 "100" V 7559 4625 50  0000 C CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 7605 4625 50  0001 C CNN
F 3 "~" H 7675 4625 50  0001 C CNN
	1    7675 4625
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 5F5CE17F
P 7675 4925
F 0 "R12" V 7468 4925 50  0000 C CNN
F 1 "100" V 7559 4925 50  0000 C CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 7605 4925 50  0001 C CNN
F 3 "~" H 7675 4925 50  0001 C CNN
	1    7675 4925
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 5F5CEA23
P 7675 5250
F 0 "R13" V 7882 5250 50  0000 C CNN
F 1 "100" V 7791 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 7605 5250 50  0001 C CNN
F 3 "~" H 7675 5250 50  0001 C CNN
	1    7675 5250
	0    1    -1   0   
$EndComp
$Comp
L Device:R R14
U 1 1 5F5CF402
P 7675 5600
F 0 "R14" V 7882 5600 50  0000 C CNN
F 1 "100" V 7791 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 7605 5600 50  0001 C CNN
F 3 "~" H 7675 5600 50  0001 C CNN
	1    7675 5600
	0    1    -1   0   
$EndComp
Wire Wire Line
	7525 4625 6775 4625
Wire Wire Line
	7525 4925 6775 4925
Wire Wire Line
	7525 5250 6775 5250
Wire Wire Line
	7525 5600 6775 5600
Wire Wire Line
	8800 5025 8225 5025
Wire Wire Line
	8225 5025 8225 4925
Wire Wire Line
	8225 4925 7825 4925
Wire Wire Line
	8800 5125 8200 5125
Wire Wire Line
	8200 5125 8200 5250
Wire Wire Line
	8200 5250 7825 5250
Wire Wire Line
	7825 5600 8300 5600
Wire Wire Line
	8300 5600 8300 5225
Wire Wire Line
	8300 5225 8800 5225
Wire Wire Line
	7825 4625 8300 4625
Wire Wire Line
	8300 4625 8300 4925
Wire Wire Line
	8300 4925 8800 4925
NoConn ~ 8800 4825
Wire Wire Line
	9300 5225 10025 5225
Wire Wire Line
	9300 5125 9500 5125
Wire Wire Line
	9500 5125 9500 5025
Wire Wire Line
	9300 4825 9500 4825
Connection ~ 9500 4825
Wire Wire Line
	9500 4825 10025 4825
Wire Wire Line
	9300 4925 9500 4925
Connection ~ 9500 4925
Wire Wire Line
	9500 4925 9500 4825
Wire Wire Line
	9300 5025 9500 5025
Connection ~ 9500 5025
Wire Wire Line
	9500 5025 9500 4925
Text GLabel 10025 4825 2    50   Input ~ 0
GND
Text GLabel 10025 5225 2    50   Input ~ 0
VCC
Text Label 6775 4625 0    50   ~ 0
MTDI
Text Label 6775 4925 0    50   ~ 0
MTDO
Text Label 6775 5250 0    50   ~ 0
MTCK
Text Label 6775 5600 0    50   ~ 0
MTMS
Text Notes 8300 4275 0    50   ~ 0
JTAG Connection
Text HLabel 4850 1575 2    50   Output ~ 0
USB_GND
Text HLabel 1850 1575 0    50   Output ~ 0
USB_VDD
Wire Wire Line
	1850 1575 2400 1575
$Comp
L power:PWR_FLAG #FLG04
U 1 1 5F6C09A7
P 2400 1575
F 0 "#FLG04" H 2400 1650 50  0001 C CNN
F 1 "PWR_FLAG" H 2400 1748 50  0000 C CNN
F 2 "" H 2400 1575 50  0001 C CNN
F 3 "~" H 2400 1575 50  0001 C CNN
	1    2400 1575
	1    0    0    -1  
$EndComp
Connection ~ 2400 1575
Wire Wire Line
	2400 1575 2625 1575
Text HLabel 2425 2175 0    50   Output ~ 0
EN_Transceiver
Wire Wire Line
	2625 2175 2425 2175
NoConn ~ 2625 3375
Wire Wire Line
	1625 1750 2400 1750
Wire Wire Line
	2400 1750 2400 1575
Wire Wire Line
	1900 2875 2625 2875
Text Label 2100 1750 2    50   ~ 0
3.3V
$Comp
L Board:2716-106 X1
U 1 1 5F649C8C
P 825 2850
F 0 "X1" H 775 1484 50  0000 C CNN
F 1 "2716-106" H 775 1575 50  0000 C CNN
F 2 "Board:P-2716-106" H 825 2850 50  0001 L BNN
F 3 "" H 825 2850 50  0001 C CNN
	1    825  2850
	-1   0    0    1   
$EndComp
Wire Wire Line
	1350 2275 1350 1750
Wire Wire Line
	1350 1750 1025 1750
Wire Wire Line
	1025 2375 1025 2350
Wire Wire Line
	1025 2375 2625 2375
Wire Wire Line
	1025 2475 1025 2550
Wire Wire Line
	1025 2475 2625 2475
Wire Wire Line
	1150 2575 1150 2950
Wire Wire Line
	1150 2950 1025 2950
Wire Wire Line
	1150 2575 2625 2575
Wire Wire Line
	1225 2675 1225 3350
Wire Wire Line
	1225 3350 1025 3350
Wire Wire Line
	1225 2675 1900 2675
Wire Wire Line
	1350 2775 1350 3750
Wire Wire Line
	1350 3750 1025 3750
Wire Wire Line
	825  1750 1025 1750
Connection ~ 1025 1750
Wire Wire Line
	1025 1950 1025 1750
Wire Wire Line
	1025 1950 825  1950
Connection ~ 1025 1950
Connection ~ 1025 2350
Wire Wire Line
	825  2150 825  2350
Wire Wire Line
	825  2150 1025 2150
Connection ~ 825  2150
Connection ~ 1025 2150
Wire Wire Line
	825  1750 825  1950
Connection ~ 825  1750
Connection ~ 825  1950
Wire Wire Line
	825  2350 1025 2350
Connection ~ 825  2350
Wire Wire Line
	1025 2550 1025 2750
Connection ~ 1025 2550
Wire Wire Line
	825  2550 1025 2550
Wire Wire Line
	1025 2325 1025 2350
Wire Wire Line
	1025 2150 1025 2350
Wire Wire Line
	825  2750 825  2550
Connection ~ 825  2550
Wire Wire Line
	825  2750 1025 2750
Connection ~ 825  2750
Connection ~ 1025 2750
Wire Wire Line
	825  2950 825  3150
Wire Wire Line
	1025 3150 1025 2950
Wire Wire Line
	1025 2950 825  2950
Connection ~ 1025 2950
Connection ~ 825  2950
Wire Wire Line
	825  3150 1025 3150
Connection ~ 825  3150
Connection ~ 1025 3150
Wire Wire Line
	825  3350 825  3550
Wire Wire Line
	1025 3550 1025 3350
Connection ~ 1025 3350
Wire Wire Line
	825  3550 1025 3550
Connection ~ 825  3550
Connection ~ 1025 3550
Wire Wire Line
	825  3350 1025 3350
Connection ~ 825  3350
Wire Wire Line
	825  3950 1025 3950
Wire Wire Line
	825  3750 825  3950
Connection ~ 825  3950
Wire Wire Line
	825  3750 1025 3750
Connection ~ 825  3750
Connection ~ 1025 3750
Wire Wire Line
	1025 3950 1025 3750
Connection ~ 1025 3950
Text HLabel 4850 1675 2    50   Input ~ 0
EN_CAN
Wire Wire Line
	4850 1675 4225 1675
$EndSCHEMATC
