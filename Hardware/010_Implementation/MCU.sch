EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title "CAN_Bus Analyzer - MCU"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 4950 2075 2    50   ~ 0
WiFi_Mode
Text Label 4950 2375 2    50   ~ 0
Indicator_AP_Mode
Text Label 4950 2275 2    50   ~ 0
Indicator_STA_Mode
Text Label 4950 2975 2    50   ~ 0
Indicator_Error
Wire Wire Line
	3525 5775 4150 5775
Text Label 4950 5775 2    50   ~ 0
WiFi_Mode
$Comp
L Switch:SW_Push SW1
U 1 1 5F54C857
P 3525 6050
F 0 "SW1" V 3571 6002 50  0000 R CNN
F 1 "SW_Push" V 3480 6002 50  0000 R CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_CK_KSC7xxJ" H 3525 6250 50  0001 C CNN
F 3 "~" H 3525 6250 50  0001 C CNN
	1    3525 6050
	0    -1   -1   0   
$EndComp
Text Notes 4000 1100 2    50   ~ 0
ESP-WROOM-32 Micro-Controller
Text Notes 8540 1140 2    50   ~ 0
Status LEDs
Text Notes 4050 4775 2    50   ~ 0
WiFi-Mode Button
Text HLabel 4950 2775 2    50   Output ~ 0
CAN_Tx
Text HLabel 4950 2475 2    50   Input ~ 0
CAN_Rx
Text Label 1700 2475 0    50   ~ 0
GPIO_2
Text Label 1700 2575 0    50   ~ 0
GPIO_1
Text Label 1700 2375 0    50   ~ 0
GPIO_3
Text Label 2275 2875 2    50   ~ 0
GND
Text Label 2125 2775 0    50   ~ 0
MTDI
Text Label 2125 2975 0    50   ~ 0
MTCK
Text Label 2125 2675 0    50   ~ 0
MTMS
Text Label 4950 3075 2    50   ~ 0
MTDO
$Comp
L Device:C C7
U 1 1 5F5C9535
P 4150 6025
F 0 "C7" H 4265 6071 50  0000 L CNN
F 1 "100n" H 4265 5980 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 4188 5875 50  0001 C CNN
F 3 "~" H 4150 6025 50  0001 C CNN
	1    4150 6025
	1    0    0    -1  
$EndComp
Wire Wire Line
	3525 5775 3525 5850
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J1
U 1 1 5F5CC4A5
P 9100 5025
F 0 "J1" H 9150 4600 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 9150 4691 50  0000 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_2x05_P1.00mm_Vertical" H 9100 5025 50  0001 C CNN
F 3 "~" H 9100 5025 50  0001 C CNN
	1    9100 5025
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 5F5CD98B
P 7675 4625
F 0 "R6" V 7468 4625 50  0000 C CNN
F 1 "100" V 7559 4625 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7605 4625 50  0001 C CNN
F 3 "~" H 7675 4625 50  0001 C CNN
	1    7675 4625
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5F5CE17F
P 7675 4925
F 0 "R7" V 7468 4925 50  0000 C CNN
F 1 "100" V 7559 4925 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7605 4925 50  0001 C CNN
F 3 "~" H 7675 4925 50  0001 C CNN
	1    7675 4925
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 5F5CEA23
P 7675 5250
F 0 "R8" V 7882 5250 50  0000 C CNN
F 1 "100" V 7791 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7605 5250 50  0001 C CNN
F 3 "~" H 7675 5250 50  0001 C CNN
	1    7675 5250
	0    1    -1   0   
$EndComp
$Comp
L Device:R R9
U 1 1 5F5CF402
P 7675 5600
F 0 "R9" V 7882 5600 50  0000 C CNN
F 1 "100" V 7791 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7605 5600 50  0001 C CNN
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
	9500 4825 9725 4825
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
$Comp
L Board:2716-106 X1
U 1 1 5F649C8C
P 1125 5925
F 0 "X1" H 1075 4559 50  0000 C CNN
F 1 "2716-106" H 1075 4650 50  0000 C CNN
F 2 "Board:P-2716-106" H 1125 5925 50  0001 L BNN
F 3 "" H 1125 5925 50  0001 C CNN
	1    1125 5925
	-1   0    0    1   
$EndComp
Wire Wire Line
	2625 2375 1700 2375
NoConn ~ 2625 1975
NoConn ~ 2625 1875
NoConn ~ 4225 3375
NoConn ~ 4225 3275
NoConn ~ 4225 3175
Wire Wire Line
	4225 3075 4950 3075
Wire Wire Line
	4225 2975 4950 2975
NoConn ~ 4225 2875
Wire Wire Line
	4950 2775 4225 2775
NoConn ~ 4225 2675
NoConn ~ 4225 2575
NoConn ~ 2625 1775
Wire Wire Line
	4225 2475 4950 2475
Wire Wire Line
	4950 2375 4225 2375
Wire Wire Line
	4225 2275 4950 2275
Wire Wire Line
	4225 2075 4950 2075
NoConn ~ 4225 1975
NoConn ~ 4225 1875
NoConn ~ 4225 1775
NoConn ~ 2625 1675
NoConn ~ 2625 3275
NoConn ~ 2625 3175
NoConn ~ 2625 3075
Wire Wire Line
	2625 2975 2125 2975
Wire Wire Line
	2625 2775 2125 2775
Wire Wire Line
	2625 2675 2125 2675
Wire Wire Line
	2625 2575 1700 2575
Wire Wire Line
	2625 2475 1700 2475
Wire Wire Line
	2625 2275 1700 2275
Text Label 1700 2275 0    50   ~ 0
GPIO_4
Wire Wire Line
	1325 5425 1925 5425
Wire Wire Line
	1325 5025 1925 5025
$Comp
L power:GND #PWR08
U 1 1 5F86CB8D
P 1925 5425
F 0 "#PWR08" H 1925 5175 50  0001 C CNN
F 1 "GND" H 1930 5252 50  0000 C CNN
F 2 "" H 1925 5425 50  0001 C CNN
F 3 "" H 1925 5425 50  0001 C CNN
	1    1925 5425
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR07
U 1 1 5F86D27D
P 1925 4975
F 0 "#PWR07" H 1925 4825 50  0001 C CNN
F 1 "+3.3V" H 1940 5148 50  0000 C CNN
F 2 "" H 1925 4975 50  0001 C CNN
F 3 "" H 1925 4975 50  0001 C CNN
	1    1925 4975
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5F86D925
P 1950 2925
F 0 "#PWR09" H 1950 2675 50  0001 C CNN
F 1 "GND" H 1955 2752 50  0000 C CNN
F 2 "" H 1950 2925 50  0001 C CNN
F 3 "" H 1950 2925 50  0001 C CNN
	1    1950 2925
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2875 2625 2875
Wire Wire Line
	4225 2175 5400 2175
$Comp
L power:GND #PWR013
U 1 1 5F875863
P 5400 2200
F 0 "#PWR013" H 5400 1950 50  0001 C CNN
F 1 "GND" H 5405 2027 50  0000 C CNN
F 2 "" H 5400 2200 50  0001 C CNN
F 3 "" H 5400 2200 50  0001 C CNN
	1    5400 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 5F892230
P 7925 2325
F 0 "D4" V 7964 2207 50  0000 R CNN
F 1 "RED" V 7873 2207 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 7925 2325 50  0001 C CNN
F 3 "~" H 7925 2325 50  0001 C CNN
	1    7925 2325
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D5
U 1 1 5F8932AC
P 8350 2325
F 0 "D5" V 8389 2207 50  0000 R CNN
F 1 "GREEN" V 8298 2207 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8350 2325 50  0001 C CNN
F 3 "~" H 8350 2325 50  0001 C CNN
	1    8350 2325
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D6
U 1 1 5F895083
P 8775 2325
F 0 "D6" V 8814 2207 50  0000 R CNN
F 1 "GREEN" V 8723 2207 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8775 2325 50  0001 C CNN
F 3 "~" H 8775 2325 50  0001 C CNN
	1    8775 2325
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R10
U 1 1 5F8967E0
P 7925 2800
F 0 "R10" H 7995 2846 50  0000 L CNN
F 1 "500" H 7995 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7855 2800 50  0001 C CNN
F 3 "~" H 7925 2800 50  0001 C CNN
	1    7925 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5F8972E5
P 8350 2800
F 0 "R11" H 8420 2846 50  0000 L CNN
F 1 "500" H 8420 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8280 2800 50  0001 C CNN
F 3 "~" H 8350 2800 50  0001 C CNN
	1    8350 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 5F898BC6
P 8775 2800
F 0 "R12" H 8845 2846 50  0000 L CNN
F 1 "500" H 8845 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8705 2800 50  0001 C CNN
F 3 "~" H 8775 2800 50  0001 C CNN
	1    8775 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7925 2475 7925 2650
Wire Wire Line
	8350 2475 8350 2650
Wire Wire Line
	8775 2475 8775 2650
Wire Wire Line
	7925 2950 7925 3100
Wire Wire Line
	7925 3100 8350 3100
Wire Wire Line
	8775 3100 8775 2950
Wire Wire Line
	8350 2950 8350 3100
Connection ~ 8350 3100
Wire Wire Line
	8350 3100 8775 3100
$Comp
L power:GND #PWR014
U 1 1 5F8A2636
P 8350 3150
F 0 "#PWR014" H 8350 2900 50  0001 C CNN
F 1 "GND" H 8355 2977 50  0000 C CNN
F 2 "" H 8350 3150 50  0001 C CNN
F 3 "" H 8350 3150 50  0001 C CNN
	1    8350 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7925 2175 7925 1250
Wire Wire Line
	8350 2175 8350 1250
Wire Wire Line
	8775 2175 8775 1250
Text Label 7925 1250 3    50   ~ 0
Indicator_Error
Text Label 8350 1250 3    50   ~ 0
Indicator_AP_Mode
Text Label 8775 1250 3    50   ~ 0
Indicator_STA_Mode
NoConn ~ 1125 4825
NoConn ~ 1325 4825
NoConn ~ 1125 5025
NoConn ~ 1125 5225
NoConn ~ 1325 5225
NoConn ~ 1125 5425
NoConn ~ 1125 5625
NoConn ~ 1325 5625
NoConn ~ 1125 5825
NoConn ~ 1125 6025
NoConn ~ 1125 6225
NoConn ~ 1325 6025
NoConn ~ 1125 6425
NoConn ~ 1125 6625
NoConn ~ 1325 6425
NoConn ~ 1125 6825
NoConn ~ 1325 6825
NoConn ~ 1125 7025
Wire Wire Line
	4150 5875 4150 5775
Connection ~ 4150 5775
Wire Wire Line
	4150 5775 4950 5775
Wire Wire Line
	3525 6250 3525 6425
Wire Wire Line
	4150 6425 4150 6175
$Comp
L power:GND #PWR011
U 1 1 5F8F6B0F
P 3825 6475
F 0 "#PWR011" H 3825 6225 50  0001 C CNN
F 1 "GND" H 3830 6302 50  0000 C CNN
F 2 "" H 3825 6475 50  0001 C CNN
F 3 "" H 3825 6475 50  0001 C CNN
	1    3825 6475
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR016
U 1 1 5F90AFB8
P 10025 5225
F 0 "#PWR016" H 10025 5075 50  0001 C CNN
F 1 "+3.3V" H 10040 5398 50  0000 C CNN
F 2 "" H 10025 5225 50  0001 C CNN
F 3 "" H 10025 5225 50  0001 C CNN
	1    10025 5225
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5F90B7D2
P 9725 4875
F 0 "#PWR015" H 9725 4625 50  0001 C CNN
F 1 "GND" H 9730 4702 50  0000 C CNN
F 2 "" H 9725 4875 50  0001 C CNN
F 3 "" H 9725 4875 50  0001 C CNN
	1    9725 4875
	1    0    0    -1  
$EndComp
Wire Wire Line
	3525 6425 3825 6425
Wire Wire Line
	3825 6475 3825 6425
Connection ~ 3825 6425
Wire Wire Line
	3825 6425 4150 6425
Wire Wire Line
	5400 2200 5400 2175
Wire Wire Line
	1950 2875 1950 2925
Wire Wire Line
	8350 3150 8350 3100
$Comp
L Board:ESP32-DEVKITC-32D U2
U 1 1 5F52F5CE
P 3425 2475
F 0 "U2" H 3425 3642 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 3425 3551 50  0000 C CNN
F 2 "Board:MODULE_ESP32-DEVKITC-32D" H 3425 2475 50  0001 L BNN
F 3 "Espressif Systems" H 3425 2475 50  0001 L BNN
F 4 "4" H 3425 2475 50  0001 L BNN "Field4"
	1    3425 2475
	1    0    0    -1  
$EndComp
NoConn ~ 4225 1675
Wire Wire Line
	4225 1575 5400 1575
$Comp
L power:GND #PWR012
U 1 1 5FA15FD5
P 5400 1575
F 0 "#PWR012" H 5400 1325 50  0001 C CNN
F 1 "GND" H 5405 1402 50  0000 C CNN
F 2 "" H 5400 1575 50  0001 C CNN
F 3 "" H 5400 1575 50  0001 C CNN
	1    5400 1575
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR06
U 1 1 5FA181FD
P 1850 1575
F 0 "#PWR06" H 1850 1425 50  0001 C CNN
F 1 "+3.3V" H 1865 1748 50  0000 C CNN
F 2 "" H 1850 1575 50  0001 C CNN
F 3 "" H 1850 1575 50  0001 C CNN
	1    1850 1575
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1575 2175 1575
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5FA2F843
P 2175 1575
F 0 "#FLG02" H 2175 1650 50  0001 C CNN
F 1 "PWR_FLAG" H 2175 1748 50  0000 C CNN
F 2 "" H 2175 1575 50  0001 C CNN
F 3 "~" H 2175 1575 50  0001 C CNN
	1    2175 1575
	1    0    0    -1  
$EndComp
Connection ~ 2175 1575
Wire Wire Line
	2175 1575 2625 1575
Wire Notes Line
	3100 4600 5325 4600
Wire Notes Line
	5325 4600 5325 6800
Wire Notes Line
	5325 6800 3100 6800
Wire Notes Line
	3100 6800 3100 4600
Wire Notes Line
	10450 4075 10450 5900
Wire Notes Line
	10450 5900 6475 5900
Wire Notes Line
	6475 5900 6475 4075
Wire Notes Line
	6475 4075 10450 4075
Wire Notes Line
	7525 900  9200 900 
Wire Notes Line
	9200 900  9200 3550
Wire Notes Line
	9200 3550 7525 3550
Wire Notes Line
	7525 3550 7525 900 
Wire Notes Line
	2125 4400 2125 7375
Wire Notes Line
	2125 7375 775  7375
Wire Notes Line
	775  7375 775  4400
Wire Notes Line
	775  4400 2125 4400
Wire Wire Line
	1325 5825 1925 5825
Wire Wire Line
	1325 6225 1925 6225
Wire Wire Line
	1325 6625 1925 6625
Wire Wire Line
	1325 7025 1925 7025
Text Label 1925 5825 2    50   ~ 0
GPIO_4
Text Label 1925 6225 2    50   ~ 0
GPIO_3
Text Label 1925 6625 2    50   ~ 0
GPIO_2
Text Label 1925 7025 2    50   ~ 0
GPIO_1
Wire Wire Line
	3525 5700 3525 5775
Connection ~ 3525 5775
$Comp
L power:+3.3V #PWR010
U 1 1 5FAED6AE
P 3525 5300
F 0 "#PWR010" H 3525 5150 50  0001 C CNN
F 1 "+3.3V" H 3540 5473 50  0000 C CNN
F 2 "" H 3525 5300 50  0001 C CNN
F 3 "" H 3525 5300 50  0001 C CNN
	1    3525 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3525 5300 3525 5400
Wire Wire Line
	2625 2075 1700 2075
Wire Wire Line
	2625 2175 1700 2175
Text HLabel 1700 2075 0    50   Input ~ 0
OBD_Voltage_Check
Text HLabel 1700 2175 0    50   Output ~ 0
OBD-CAN_Switch
$Comp
L Device:R R5
U 1 1 5FB6A40E
P 3525 5550
F 0 "R5" H 3595 5596 50  0000 L CNN
F 1 "2.2k" H 3595 5505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3455 5550 50  0001 C CNN
F 3 "~" H 3525 5550 50  0001 C CNN
	1    3525 5550
	1    0    0    -1  
$EndComp
$Comp
L Board:SS24 D3
U 1 1 5FB70E5B
P 2200 3375
F 0 "D3" H 2200 3592 50  0000 C CNN
F 1 "SS24" H 2200 3501 50  0000 C CNN
F 2 "Board:DIOM5336X265N" H 2200 3375 50  0001 L BNN
F 3 "IPC 7351B" H 2200 3375 50  0001 L BNN
F 4 "2.65 mm" H 2200 3375 50  0001 L BNN "Field4"
F 5 "ON Semiconductor" H 2200 3375 50  0001 L BNN "Field5"
F 6 "1.1.2" H 2200 3375 50  0001 L BNN "Field6"
	1    2200 3375
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3375 2525 3375
Wire Wire Line
	2000 3375 1625 3375
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5FB78D65
P 2525 3375
F 0 "#FLG0101" H 2525 3450 50  0001 C CNN
F 1 "PWR_FLAG" H 2525 3548 50  0000 C CNN
F 2 "" H 2525 3375 50  0001 C CNN
F 3 "~" H 2525 3375 50  0001 C CNN
	1    2525 3375
	1    0    0    -1  
$EndComp
Connection ~ 2525 3375
Wire Wire Line
	2525 3375 2625 3375
$Comp
L power:+5V #PWR022
U 1 1 5FA19D37
P 1625 3375
F 0 "#PWR022" H 1625 3225 50  0001 C CNN
F 1 "+5V" H 1640 3548 50  0000 C CNN
F 2 "" H 1625 3375 50  0001 C CNN
F 3 "" H 1625 3375 50  0001 C CNN
	1    1625 3375
	1    0    0    -1  
$EndComp
Wire Wire Line
	1925 4975 1925 5025
Wire Wire Line
	9725 4825 9725 4875
$EndSCHEMATC
