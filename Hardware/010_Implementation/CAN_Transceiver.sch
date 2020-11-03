EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title "CAN_Analyzer - CAN_Transceivers"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	8525 3475 8525 3600
Connection ~ 8625 2975
Wire Wire Line
	8625 3075 8625 2975
Wire Wire Line
	8525 3075 8625 3075
$Comp
L power:GND #PWR03
U 1 1 5F9161C7
P 5075 4375
F 0 "#PWR03" H 5075 4125 50  0001 C CNN
F 1 "GND" H 5080 4202 50  0000 C CNN
F 2 "" H 5075 4375 50  0001 C CNN
F 3 "" H 5075 4375 50  0001 C CNN
	1    5075 4375
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 5F913497
P 8750 3600
F 0 "#PWR05" H 8750 3450 50  0001 C CNN
F 1 "+3.3V" H 8765 3773 50  0000 C CNN
F 2 "" H 8750 3600 50  0001 C CNN
F 3 "" H 8750 3600 50  0001 C CNN
	1    8750 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5F91316D
P 8750 2775
F 0 "#PWR04" H 8750 2525 50  0001 C CNN
F 1 "GND" H 8755 2602 50  0000 C CNN
F 2 "" H 8750 2775 50  0001 C CNN
F 3 "" H 8750 2775 50  0001 C CNN
	1    8750 2775
	1    0    0    -1  
$EndComp
Text Notes 5175 2300 2    50   ~ 0
Signal Filter
Wire Wire Line
	5075 4050 6700 4050
Connection ~ 5075 4050
Wire Wire Line
	5075 4375 5075 4050
Wire Wire Line
	2800 2525 3400 2525
Wire Wire Line
	2800 3450 3400 3450
Connection ~ 3400 3450
Wire Wire Line
	3925 4050 4450 4050
Wire Wire Line
	4450 4050 5075 4050
Connection ~ 4450 4050
Wire Wire Line
	3400 3025 3400 3100
Connection ~ 3400 3025
Wire Wire Line
	3700 3025 3700 4050
Wire Wire Line
	3400 3025 3700 3025
Wire Wire Line
	3400 3450 4450 3450
Wire Wire Line
	3400 3400 3400 3450
Wire Wire Line
	3400 2525 3925 2525
Connection ~ 3400 2525
Wire Wire Line
	3400 2650 3400 2525
Wire Wire Line
	3400 2950 3400 3025
Wire Wire Line
	3925 2525 4675 2525
Connection ~ 3925 2525
Wire Wire Line
	3925 2525 3925 3500
Wire Wire Line
	4675 3100 4875 3100
Wire Wire Line
	4675 2525 4675 3100
Wire Wire Line
	4450 3450 4675 3450
Connection ~ 4450 3450
Wire Wire Line
	4450 3500 4450 3450
Wire Wire Line
	4675 3300 4875 3300
Wire Wire Line
	4675 3450 4675 3300
$Comp
L Diode:SD05_SOD323 D2
U 1 1 5F5F1395
P 3400 3250
F 0 "D2" V 3354 3329 50  0000 L CNN
F 1 "SD05_SOD323" V 3445 3329 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 3400 3050 50  0001 C CNN
F 3 "https://www.littelfuse.com/~/media/electronics/datasheets/tvs_diode_arrays/littelfuse_tvs_diode_array_sd_c_datasheet.pdf.pdf" H 3400 3250 50  0001 C CNN
	1    3400 3250
	0    1    1    0   
$EndComp
$Comp
L Diode:SD05_SOD323 D1
U 1 1 5F5F138F
P 3400 2800
F 0 "D1" V 3446 2721 50  0000 R CNN
F 1 "SD05_SOD323" V 3355 2721 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323" H 3400 2600 50  0001 C CNN
F 3 "https://www.littelfuse.com/~/media/electronics/datasheets/tvs_diode_arrays/littelfuse_tvs_diode_array_sd_c_datasheet.pdf.pdf" H 3400 2800 50  0001 C CNN
	1    3400 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4450 3800 4450 4050
Connection ~ 3925 4050
Wire Wire Line
	3925 4050 3700 4050
Wire Wire Line
	3925 3800 3925 4050
$Comp
L Device:C C3
U 1 1 5F5F1385
P 3925 3650
F 0 "C3" H 4040 3696 50  0000 L CNN
F 1 "100p" H 4040 3605 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 3963 3500 50  0001 C CNN
F 3 "~" H 3925 3650 50  0001 C CNN
	1    3925 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5F5F137F
P 4450 3650
F 0 "C4" H 4565 3696 50  0000 L CNN
F 1 "100p" H 4565 3605 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 4488 3500 50  0001 C CNN
F 3 "~" H 4450 3650 50  0001 C CNN
	1    4450 3650
	1    0    0    -1  
$EndComp
Connection ~ 5750 3800
Wire Wire Line
	5525 3800 5750 3800
Wire Wire Line
	5525 3300 5525 3800
Wire Wire Line
	5275 3300 5525 3300
Connection ~ 5750 2650
Wire Wire Line
	5525 2650 5750 2650
Wire Wire Line
	5525 3100 5525 2650
Wire Wire Line
	5275 3100 5525 3100
$Comp
L Device:L_Core_Ferrite_Coupled L1
U 1 1 5F5F1371
P 5075 3200
F 0 "L1" H 5075 2875 50  0000 C CNN
F 1 "L_Core_Ferrite_Coupled" H 5075 2966 50  0000 C CNN
F 2 "Transformer_THT:Transformer_Toroid_Horizontal_D9.0mm_Amidon-T30" H 5075 3200 50  0001 C CNN
F 3 "~" H 5075 3200 50  0001 C CNN
	1    5075 3200
	-1   0    0    -1  
$EndComp
Connection ~ 6200 3800
Wire Wire Line
	5750 3800 6200 3800
Wire Wire Line
	5750 3350 5750 3800
Connection ~ 6200 2650
Wire Wire Line
	5750 2650 6200 2650
Wire Wire Line
	5750 3050 5750 2650
$Comp
L Device:C C5
U 1 1 5F5F1365
P 5750 3200
F 0 "C5" H 5865 3246 50  0000 L CNN
F 1 "100p" H 5865 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 5788 3050 50  0001 C CNN
F 3 "~" H 5750 3200 50  0001 C CNN
	1    5750 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3950 6700 4050
Wire Wire Line
	6200 3200 6200 3375
Connection ~ 6200 3200
Wire Wire Line
	6700 3200 6200 3200
Wire Wire Line
	6700 3650 6700 3200
Wire Wire Line
	6200 2650 6200 2750
Wire Wire Line
	6450 2650 6200 2650
Wire Wire Line
	6450 3375 6450 2650
Wire Wire Line
	7125 3375 6450 3375
Wire Wire Line
	6450 3475 7125 3475
Wire Wire Line
	6200 3050 6200 3200
Wire Wire Line
	6450 3800 6450 3475
Wire Wire Line
	6200 3800 6450 3800
Wire Wire Line
	6200 3675 6200 3800
$Comp
L Device:C C6
U 1 1 5F5F1351
P 6700 3800
F 0 "C6" H 6815 3846 50  0000 L CNN
F 1 "4n7" H 6815 3755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 6738 3650 50  0001 C CNN
F 3 "~" H 6700 3800 50  0001 C CNN
	1    6700 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F5F134B
P 6200 3525
F 0 "R4" H 6270 3571 50  0000 L CNN
F 1 "62" H 6270 3480 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6130 3525 50  0001 C CNN
F 3 "~" H 6200 3525 50  0001 C CNN
	1    6200 3525
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5F5F1345
P 6200 2900
F 0 "R3" H 6270 2946 50  0000 L CNN
F 1 "62" H 6270 2855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6130 2900 50  0001 C CNN
F 3 "~" H 6200 2900 50  0001 C CNN
	1    6200 2900
	1    0    0    -1  
$EndComp
Text Notes 7635 2295 0    50   ~ 0
Transceiver
Wire Wire Line
	8625 2775 8750 2775
Connection ~ 8625 2775
Wire Wire Line
	8625 2975 8625 2775
Wire Wire Line
	8525 2975 8625 2975
Wire Wire Line
	8525 3600 8750 3600
Wire Wire Line
	8525 2775 8625 2775
Wire Wire Line
	8525 3275 9175 3275
Wire Wire Line
	9175 3175 8525 3175
$Comp
L Board:SN65HVD233-HT IC1
U 1 1 5F565F75
P 7825 3175
F 0 "IC1" H 7825 2405 50  0000 C CNN
F 1 "SN65HVD233-HT" H 7825 2496 50  0000 C CNN
F 2 "Board:SOIC127P600X175" H 7825 3175 50  0001 L BNN
F 3 "" H 7825 3175 50  0001 C CNN
	1    7825 3175
	-1   0    0    1   
$EndComp
Text HLabel 9175 3175 2    50   Input ~ 0
CAN_Tx
Text HLabel 9175 3275 2    50   Output ~ 0
CAN_Rx
Text HLabel 2800 2525 0    50   BiDi ~ 0
BUS_H
Text HLabel 2800 3450 0    50   BiDi ~ 0
BUS_L
$EndSCHEMATC
