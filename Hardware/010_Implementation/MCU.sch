EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title "CAN_Bus Analyzer - MCU"
Date "2021-02-04"
Rev "1.1"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 5125 3280 2    50   ~ 0
WiFi_Mode
Text Label 5125 3180 2    50   ~ 0
Indicator_AP_Mode
Text Label 5125 2580 2    50   ~ 0
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
F 4 "Yes" H 3525 6050 50  0001 C CNN "Vorhanden"
	1    3525 6050
	0    -1   -1   0   
$EndComp
Text Notes 4205 1095 2    50   ~ 0
ESP-WROOM-32 Micro-Controller
Text Notes 8540 1140 2    50   ~ 0
Status LEDs
Text Notes 4050 4775 2    50   ~ 0
WiFi-Mode Button
Text HLabel 5125 2980 2    50   Output ~ 0
CAN_Tx
Text HLabel 5125 2680 2    50   Input ~ 0
CAN_Rx
Text Label 1875 2880 0    50   ~ 0
GPIO_2
Text Label 1875 2780 0    50   ~ 0
GPIO_1
Text Label 1875 2980 0    50   ~ 0
GPIO_3
Text Label 2450 2380 2    50   ~ 0
GND
Text Label 2300 2580 0    50   ~ 0
MTDI
Text Label 2300 2480 0    50   ~ 0
MTCK
Text Label 2300 2680 0    50   ~ 0
MTMS
Text Label 5125 2480 2    50   ~ 0
MTDO
$Comp
L Device:C C8
U 1 1 5F5C9535
P 4150 6025
F 0 "C8" H 4265 6071 50  0000 L CNN
F 1 "100n" H 4265 5980 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4188 5875 50  0001 C CNN
F 3 "~" H 4150 6025 50  0001 C CNN
	1    4150 6025
	1    0    0    -1  
$EndComp
Wire Wire Line
	3525 5775 3525 5850
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J2
U 1 1 5F5CC4A5
P 9100 5025
F 0 "J2" H 9150 4600 50  0000 C CNN
F 1 "JTAG Jumper Pins" H 9150 4691 50  0000 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_2x05_P1.00mm_Vertical" H 9100 5025 50  0001 C CNN
F 3 "~" H 9100 5025 50  0001 C CNN
F 4 "Yes" H 9100 5025 50  0001 C CNN "Vorhanden"
	1    9100 5025
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 5F5CD98B
P 7675 4625
F 0 "R9" V 7468 4625 50  0000 C CNN
F 1 "100" V 7559 4625 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7605 4625 50  0001 C CNN
F 3 "~" H 7675 4625 50  0001 C CNN
	1    7675 4625
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 5F5CE17F
P 7675 4925
F 0 "R10" V 7468 4925 50  0000 C CNN
F 1 "100" V 7559 4925 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7605 4925 50  0001 C CNN
F 3 "~" H 7675 4925 50  0001 C CNN
	1    7675 4925
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 5F5CEA23
P 7675 5250
F 0 "R11" V 7882 5250 50  0000 C CNN
F 1 "100" V 7791 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7605 5250 50  0001 C CNN
F 3 "~" H 7675 5250 50  0001 C CNN
	1    7675 5250
	0    1    -1   0   
$EndComp
$Comp
L Device:R R12
U 1 1 5F5CF402
P 7675 5600
F 0 "R12" V 7882 5600 50  0000 C CNN
F 1 "100" V 7791 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7605 5600 50  0001 C CNN
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
Wire Wire Line
	2800 2980 1875 2980
Wire Wire Line
	4400 2480 5125 2480
Wire Wire Line
	4400 2580 5125 2580
Wire Wire Line
	5125 2980 4400 2980
Wire Wire Line
	4400 2680 5125 2680
Wire Wire Line
	5125 3180 4400 3180
Wire Wire Line
	4400 3280 5125 3280
Wire Wire Line
	2800 2480 2300 2480
Wire Wire Line
	2800 2580 2300 2580
Wire Wire Line
	2800 2680 2300 2680
Wire Wire Line
	2800 2780 1875 2780
Wire Wire Line
	2800 2880 1875 2880
Wire Wire Line
	2800 3080 1875 3080
Text Label 1875 3080 0    50   ~ 0
GPIO_4
Wire Wire Line
	1325 5275 1925 5275
Wire Wire Line
	1325 5175 1925 5175
$Comp
L power:GND #PWR012
U 1 1 5F86CB8D
P 1925 5275
F 0 "#PWR012" H 1925 5025 50  0001 C CNN
F 1 "GND" H 1930 5102 50  0000 C CNN
F 2 "" H 1925 5275 50  0001 C CNN
F 3 "" H 1925 5275 50  0001 C CNN
	1    1925 5275
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR011
U 1 1 5F86D27D
P 1925 5125
F 0 "#PWR011" H 1925 4975 50  0001 C CNN
F 1 "+3.3V" H 1940 5298 50  0000 C CNN
F 2 "" H 1925 5125 50  0001 C CNN
F 3 "" H 1925 5125 50  0001 C CNN
	1    1925 5125
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5F86D925
P 2125 2420
F 0 "#PWR010" H 2125 2170 50  0001 C CNN
F 1 "GND" H 2130 2247 50  0000 C CNN
F 2 "" H 2125 2420 50  0001 C CNN
F 3 "" H 2125 2420 50  0001 C CNN
	1    2125 2420
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2125 2380 2800 2380
$Comp
L Device:LED D3
U 1 1 5F892230
P 7925 2325
F 0 "D3" V 7964 2207 50  0000 R CNN
F 1 "RED" V 7873 2207 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 7925 2325 50  0001 C CNN
F 3 "~" H 7925 2325 50  0001 C CNN
F 4 "Yes" H 7925 2325 50  0001 C CNN "Vorhanden"
	1    7925 2325
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D4
U 1 1 5F8932AC
P 8350 2325
F 0 "D4" V 8389 2207 50  0000 R CNN
F 1 "GREEN" V 8298 2207 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8350 2325 50  0001 C CNN
F 3 "~" H 8350 2325 50  0001 C CNN
F 4 "Yes" H 8350 2325 50  0001 C CNN "Vorhanden"
	1    8350 2325
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D5
U 1 1 5F895083
P 8775 2325
F 0 "D5" V 8814 2207 50  0000 R CNN
F 1 "GREEN" V 8723 2207 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8775 2325 50  0001 C CNN
F 3 "~" H 8775 2325 50  0001 C CNN
F 4 "Yes" H 8775 2325 50  0001 C CNN "Vorhanden"
	1    8775 2325
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R13
U 1 1 5F8967E0
P 7925 2800
F 0 "R13" H 7995 2846 50  0000 L CNN
F 1 "500" H 7995 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7855 2800 50  0001 C CNN
F 3 "~" H 7925 2800 50  0001 C CNN
	1    7925 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 5F8972E5
P 8350 2800
F 0 "R14" H 8420 2846 50  0000 L CNN
F 1 "500" H 8420 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8280 2800 50  0001 C CNN
F 3 "~" H 8350 2800 50  0001 C CNN
	1    8350 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5F898BC6
P 8775 2800
F 0 "R15" H 8845 2846 50  0000 L CNN
F 1 "500" H 8845 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8705 2800 50  0001 C CNN
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
L power:GND #PWR017
U 1 1 5F8A2636
P 8350 3150
F 0 "#PWR017" H 8350 2900 50  0001 C CNN
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
L power:GND #PWR014
U 1 1 5F8F6B0F
P 3825 6475
F 0 "#PWR014" H 3825 6225 50  0001 C CNN
F 1 "GND" H 3830 6302 50  0000 C CNN
F 2 "" H 3825 6475 50  0001 C CNN
F 3 "" H 3825 6475 50  0001 C CNN
	1    3825 6475
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR019
U 1 1 5F90AFB8
P 10025 5225
F 0 "#PWR019" H 10025 5075 50  0001 C CNN
F 1 "+3.3V" H 10040 5398 50  0000 C CNN
F 2 "" H 10025 5225 50  0001 C CNN
F 3 "" H 10025 5225 50  0001 C CNN
	1    10025 5225
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5F90B7D2
P 9725 4875
F 0 "#PWR018" H 9725 4625 50  0001 C CNN
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
	2125 2380 2125 2420
Wire Wire Line
	8350 3150 8350 3100
$Comp
L Board:ESP32-DEVKITC-32D U2
U 1 1 5F52F5CE
P 3600 3180
F 0 "U2" H 3600 1960 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 3595 2085 50  0000 C CNN
F 2 "Board:MODULE_ESP32-DEVKITC-32D" H 3600 3180 50  0001 L BNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf#603" H 3600 3180 50  0001 L BNN
F 4 "" H 3600 3180 50  0001 L BNN "Field4"
F 5 "Yes" H 3600 3180 50  0001 C CNN "Vorhanden"
	1    3600 3180
	1    0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR016
U 1 1 5FA181FD
P 5365 1350
F 0 "#PWR016" H 5365 1200 50  0001 C CNN
F 1 "+3.3V" H 5380 1523 50  0000 C CNN
F 2 "" H 5365 1350 50  0001 C CNN
F 3 "" H 5365 1350 50  0001 C CNN
	1    5365 1350
	1    0    0    -1  
$EndComp
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
	1325 5675 1675 5675
Wire Wire Line
	1325 5575 1675 5575
Wire Wire Line
	1325 5475 1675 5475
Text Label 1675 5675 2    50   ~ 0
GPIO_4
Text Label 1675 5575 2    50   ~ 0
GPIO_3
Text Label 1675 5475 2    50   ~ 0
GPIO_2
Text Label 1680 5375 2    50   ~ 0
GPIO_1
Wire Wire Line
	3525 5700 3525 5775
Connection ~ 3525 5775
$Comp
L power:+3.3V #PWR013
U 1 1 5FAED6AE
P 3525 5300
F 0 "#PWR013" H 3525 5150 50  0001 C CNN
F 1 "+3.3V" H 3540 5473 50  0000 C CNN
F 2 "" H 3525 5300 50  0001 C CNN
F 3 "" H 3525 5300 50  0001 C CNN
	1    3525 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3525 5300 3525 5400
Wire Wire Line
	2800 3280 1875 3280
Wire Wire Line
	2800 3180 1875 3180
Text HLabel 1875 3280 0    50   Input ~ 0
OBD_Voltage_Check
Text HLabel 1875 3180 0    50   Output ~ 0
~OBD~\CAN
$Comp
L Device:R R8
U 1 1 5FB6A40E
P 3525 5550
F 0 "R8" H 3595 5596 50  0000 L CNN
F 1 "1k" H 3595 5505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3455 5550 50  0001 C CNN
F 3 "~" H 3525 5550 50  0001 C CNN
	1    3525 5550
	1    0    0    -1  
$EndComp
$Comp
L Board:SS24 D2
U 1 1 5FB70E5B
P 1347 1350
F 0 "D2" H 1347 1567 50  0000 C CNN
F 1 "SS24" H 1347 1476 50  0000 C CNN
F 2 "Board:DIOM5336X265N" H 1347 1350 50  0001 L BNN
F 3 "https://www.onsemi.com/pub/Collateral/SS24-D.PDF" H 1347 1350 50  0001 L BNN
F 4 "" H 1347 1350 50  0001 L BNN "Field4"
F 5 "ON Semiconductor" H 1347 1350 50  0001 L BNN "Field5"
F 6 "1.1.2" H 1347 1350 50  0001 L BNN "Field6"
	1    1347 1350
	1    0    0    1   
$EndComp
Wire Wire Line
	1547 1350 1595 1350
Wire Wire Line
	1147 1350 1090 1350
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5FB78D65
P 1990 1350
F 0 "#FLG03" H 1990 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 1990 1523 50  0000 C CNN
F 2 "" H 1990 1350 50  0001 C CNN
F 3 "~" H 1990 1350 50  0001 C CNN
	1    1990 1350
	-1   0    0    -1  
$EndComp
Connection ~ 1990 1350
$Comp
L power:+5V #PWR09
U 1 1 5FA19D37
P 1090 1350
F 0 "#PWR09" H 1090 1200 50  0001 C CNN
F 1 "+5V" H 1105 1523 50  0000 C CNN
F 2 "" H 1090 1350 50  0001 C CNN
F 3 "" H 1090 1350 50  0001 C CNN
	1    1090 1350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1925 5125 1925 5175
Wire Wire Line
	9725 4825 9725 4875
Text Label 4750 2380 0    50   ~ 0
GND
$Comp
L power:GND #PWR015
U 1 1 5FAE14B2
P 5475 2380
F 0 "#PWR015" H 5475 2130 50  0001 C CNN
F 1 "GND" H 5480 2207 50  0000 C CNN
F 2 "" H 5475 2380 50  0001 C CNN
F 3 "" H 5475 2380 50  0001 C CNN
	1    5475 2380
	1    0    0    -1  
$EndComp
NoConn ~ 4400 2780
NoConn ~ 4400 2880
NoConn ~ 4400 3380
NoConn ~ 4400 3480
NoConn ~ 4400 3580
NoConn ~ 4400 3680
NoConn ~ 2800 3680
NoConn ~ 2800 3580
NoConn ~ 2800 3480
NoConn ~ 2800 3380
$Comp
L Device:C C14
U 1 1 5FBFD557
P 4730 1555
F 0 "C14" H 4845 1601 50  0000 L CNN
F 1 "100n" H 4845 1510 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4768 1405 50  0001 C CNN
F 3 "~" H 4730 1555 50  0001 C CNN
	1    4730 1555
	-1   0    0    1   
$EndComp
$Comp
L Device:C C15
U 1 1 5FBFE660
P 5085 1555
F 0 "C15" H 5200 1601 50  0000 L CNN
F 1 "1u" H 5200 1510 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5123 1405 50  0001 C CNN
F 3 "~" H 5085 1555 50  0001 C CNN
	1    5085 1555
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR029
U 1 1 5FBFEE41
P 4730 1785
F 0 "#PWR029" H 4730 1535 50  0001 C CNN
F 1 "GND" H 4735 1612 50  0000 C CNN
F 2 "" H 4730 1785 50  0001 C CNN
F 3 "" H 4730 1785 50  0001 C CNN
	1    4730 1785
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5FC014C2
P 5085 1785
F 0 "#PWR030" H 5085 1535 50  0001 C CNN
F 1 "GND" H 5090 1612 50  0000 C CNN
F 2 "" H 5085 1785 50  0001 C CNN
F 3 "" H 5085 1785 50  0001 C CNN
	1    5085 1785
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4730 1705 4730 1785
Wire Wire Line
	4730 1405 4730 1350
Connection ~ 4730 1350
Wire Wire Line
	4730 1350 5085 1350
Wire Wire Line
	5085 1405 5085 1350
Connection ~ 5085 1350
Wire Wire Line
	5085 1350 5365 1350
Wire Wire Line
	4400 1350 4400 2280
Wire Wire Line
	4400 1350 4730 1350
Wire Wire Line
	4400 2380 5475 2380
$Comp
L Device:C C13
U 1 1 5FC7CC68
P 2460 1695
F 0 "C13" H 2575 1741 50  0000 L CNN
F 1 "100n" H 2575 1650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2498 1545 50  0001 C CNN
F 3 "~" H 2460 1695 50  0001 C CNN
	1    2460 1695
	1    0    0    1   
$EndComp
$Comp
L Device:C C12
U 1 1 5FC7CC6E
P 2105 1695
F 0 "C12" H 1990 1741 50  0000 R CNN
F 1 "1u" H 1990 1650 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2143 1545 50  0001 C CNN
F 3 "~" H 2105 1695 50  0001 C CNN
	1    2105 1695
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5FC7CC74
P 2460 1925
F 0 "#PWR028" H 2460 1675 50  0001 C CNN
F 1 "GND" H 2465 1752 50  0000 C CNN
F 2 "" H 2460 1925 50  0001 C CNN
F 3 "" H 2460 1925 50  0001 C CNN
	1    2460 1925
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5FC7CC7A
P 2105 1925
F 0 "#PWR027" H 2105 1675 50  0001 C CNN
F 1 "GND" H 2110 1752 50  0000 C CNN
F 2 "" H 2105 1925 50  0001 C CNN
F 3 "" H 2105 1925 50  0001 C CNN
	1    2105 1925
	1    0    0    -1  
$EndComp
Wire Wire Line
	2460 1845 2460 1925
Wire Wire Line
	2105 1845 2105 1925
Wire Wire Line
	5085 1705 5085 1785
Wire Wire Line
	2800 1350 2800 2280
Wire Wire Line
	1990 1350 2105 1350
Wire Wire Line
	2105 1545 2105 1350
Connection ~ 2105 1350
Wire Wire Line
	2105 1350 2460 1350
Wire Wire Line
	2460 1545 2460 1350
Connection ~ 2460 1350
Wire Wire Line
	2460 1350 2800 1350
Wire Wire Line
	1680 5375 1325 5375
$Comp
L Connector:Conn_01x08_Female J1
U 1 1 5FC7E1BA
P 1125 5475
F 0 "J1" H 1017 4850 50  0000 C CNN
F 1 "Conn_01x08_Female" H 1017 4941 50  0000 C CNN
F 2 "Board:AST 045-08" H 1125 5475 50  0001 C CNN
F 3 "~" H 1125 5475 50  0001 C CNN
	1    1125 5475
	-1   0    0    -1  
$EndComp
NoConn ~ 1325 5875
NoConn ~ 1325 5775
Wire Wire Line
	4400 3080 5125 3080
Text Label 5125 3080 2    50   ~ 0
Indicator_STA_Mode
Wire Wire Line
	1595 1350 1595 1055
Connection ~ 1595 1350
Wire Wire Line
	1595 1350 1990 1350
Text HLabel 1595 1055 1    50   Output ~ 0
Relay_Supply
$EndSCHEMATC
