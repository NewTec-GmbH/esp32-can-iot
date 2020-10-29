EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
Title "CAN_Analyzer - CAN_Transceivers"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 10450 3600 2    50   Output ~ 0
CAN_Rx
Text HLabel 10450 3500 2    50   Input ~ 0
CAN_Tx
$Comp
L Board:SN65HVD233-HT IC1
U 1 1 5F565F75
P 9100 3500
F 0 "IC1" H 9100 2730 50  0000 C CNN
F 1 "SN65HVD233-HT" H 9100 2821 50  0000 C CNN
F 2 "Board:SOIC127P600X175" H 9100 3500 50  0001 L BNN
F 3 "" H 9100 3500 50  0001 C CNN
	1    9100 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	10450 3500 9800 3500
Wire Wire Line
	9800 3600 10450 3600
Wire Wire Line
	9800 3400 10450 3400
Wire Wire Line
	9800 3100 9900 3100
Wire Wire Line
	9800 3800 10025 3800
Wire Wire Line
	9800 3300 9900 3300
Wire Wire Line
	9900 3300 9900 3100
Connection ~ 9900 3100
Wire Wire Line
	9900 3100 10025 3100
$Comp
L Connector:Conn_01x09_Female J2
U 1 1 5F56C5ED
P 1100 4025
F 0 "J2" H 992 3400 50  0000 C CNN
F 1 "Conn_01x09_Female" H 992 3491 50  0000 C CNN
F 2 "Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.84mm_EdgePinOffset4.94mm_Housed_MountingHolesOffset7.48mm" H 1100 4025 50  0001 C CNN
F 3 "~" H 1100 4025 50  0001 C CNN
	1    1100 4025
	-1   0    0    1   
$EndComp
Text Label 2025 5300 1    50   ~ 0
CAN_GND
Text Label 2250 2925 3    50   ~ 0
OBD_VDD
NoConn ~ 1300 3725
NoConn ~ 1300 3925
NoConn ~ 1300 4125
NoConn ~ 1300 4425
Text Label 2375 2925 3    50   ~ 0
OBD_GND
Text HLabel 2250 1625 1    50   Output ~ 0
OBD_VDD
Text HLabel 2375 1625 1    50   Output ~ 0
OBD_GND
Text Label 1375 5825 0    50   ~ 0
EN_CAN
Wire Wire Line
	1300 4225 2025 4225
Wire Wire Line
	2025 4225 2025 5625
Wire Wire Line
	1300 3625 1850 3625
Text Notes 1000 5525 0    50   ~ 0
CAN_GND Decoupler
Wire Wire Line
	1300 4325 2375 4325
Connection ~ 2375 4325
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5F5BFD41
P 1850 3625
F 0 "#FLG02" H 1850 3700 50  0001 C CNN
F 1 "PWR_FLAG" H 1850 3798 50  0000 C CNN
F 2 "" H 1850 3625 50  0001 C CNN
F 3 "~" H 1850 3625 50  0001 C CNN
	1    1850 3625
	1    0    0    -1  
$EndComp
Connection ~ 1850 3625
Wire Wire Line
	1850 3625 2250 3625
Text Notes 8910 2620 0    50   ~ 0
Transceiver
Text Notes 1535 3185 2    50   ~ 0
DSUB-9 Connector\n
$Comp
L Device:R R8
U 1 1 5F5F1345
P 7475 3225
F 0 "R8" H 7545 3271 50  0000 L CNN
F 1 "62" H 7545 3180 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 7405 3225 50  0001 C CNN
F 3 "~" H 7475 3225 50  0001 C CNN
	1    7475 3225
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5F5F134B
P 7475 3850
F 0 "R9" H 7545 3896 50  0000 L CNN
F 1 "62" H 7545 3805 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 7405 3850 50  0001 C CNN
F 3 "~" H 7475 3850 50  0001 C CNN
	1    7475 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5F5F1351
P 7975 4125
F 0 "C6" H 8090 4171 50  0000 L CNN
F 1 "4n7" H 8090 4080 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 8013 3975 50  0001 C CNN
F 3 "~" H 7975 4125 50  0001 C CNN
	1    7975 4125
	1    0    0    -1  
$EndComp
Wire Wire Line
	7475 4000 7475 4125
Wire Wire Line
	7475 4125 7725 4125
Wire Wire Line
	7725 4125 7725 3800
Wire Wire Line
	7475 3375 7475 3525
Wire Wire Line
	7725 3800 8400 3800
Wire Wire Line
	8400 3700 7725 3700
Wire Wire Line
	7725 3700 7725 2975
Wire Wire Line
	7725 2975 7475 2975
Wire Wire Line
	7475 2975 7475 3075
Wire Wire Line
	7975 3975 7975 3525
Wire Wire Line
	7975 3525 7475 3525
Connection ~ 7475 3525
Wire Wire Line
	7475 3525 7475 3700
Wire Wire Line
	7975 4275 7975 4375
$Comp
L Device:C C5
U 1 1 5F5F1365
P 7025 3525
F 0 "C5" H 7140 3571 50  0000 L CNN
F 1 "100p" H 7140 3480 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 7063 3375 50  0001 C CNN
F 3 "~" H 7025 3525 50  0001 C CNN
	1    7025 3525
	1    0    0    -1  
$EndComp
Wire Wire Line
	7025 3375 7025 2975
Wire Wire Line
	7025 2975 7475 2975
Connection ~ 7475 2975
Wire Wire Line
	7025 3675 7025 4125
Wire Wire Line
	7025 4125 7475 4125
Connection ~ 7475 4125
$Comp
L Device:L_Core_Ferrite_Coupled L1
U 1 1 5F5F1371
P 6350 3525
F 0 "L1" H 6350 3200 50  0000 C CNN
F 1 "L_Core_Ferrite_Coupled" H 6350 3291 50  0000 C CNN
F 2 "Transformer_THT:Transformer_Toroid_Horizontal_D9.0mm_Amidon-T30" H 6350 3525 50  0001 C CNN
F 3 "~" H 6350 3525 50  0001 C CNN
	1    6350 3525
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6550 3425 6800 3425
Wire Wire Line
	6800 3425 6800 2975
Wire Wire Line
	6800 2975 7025 2975
Connection ~ 7025 2975
Wire Wire Line
	6550 3625 6800 3625
Wire Wire Line
	6800 3625 6800 4125
Wire Wire Line
	6800 4125 7025 4125
Connection ~ 7025 4125
$Comp
L Device:C C4
U 1 1 5F5F137F
P 5725 3975
F 0 "C4" H 5840 4021 50  0000 L CNN
F 1 "100p" H 5840 3930 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 5763 3825 50  0001 C CNN
F 3 "~" H 5725 3975 50  0001 C CNN
	1    5725 3975
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5F5F1385
P 5200 3975
F 0 "C3" H 5315 4021 50  0000 L CNN
F 1 "100p" H 5315 3930 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 5238 3825 50  0001 C CNN
F 3 "~" H 5200 3975 50  0001 C CNN
	1    5200 3975
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 4125 5200 4375
Wire Wire Line
	5200 4375 4975 4375
Connection ~ 5200 4375
Wire Wire Line
	5725 4125 5725 4375
$Comp
L Diode:SD05_SOD323 D1
U 1 1 5F5F138F
P 4675 3125
F 0 "D1" V 4721 3046 50  0000 R CNN
F 1 "SD05_SOD323" V 4630 3046 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323" H 4675 2925 50  0001 C CNN
F 3 "https://www.littelfuse.com/~/media/electronics/datasheets/tvs_diode_arrays/littelfuse_tvs_diode_array_sd_c_datasheet.pdf.pdf" H 4675 3125 50  0001 C CNN
	1    4675 3125
	0    -1   -1   0   
$EndComp
$Comp
L Diode:SD05_SOD323 D2
U 1 1 5F5F1395
P 4675 3575
F 0 "D2" V 4629 3654 50  0000 L CNN
F 1 "SD05_SOD323" V 4720 3654 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 4675 3375 50  0001 C CNN
F 3 "https://www.littelfuse.com/~/media/electronics/datasheets/tvs_diode_arrays/littelfuse_tvs_diode_array_sd_c_datasheet.pdf.pdf" H 4675 3575 50  0001 C CNN
	1    4675 3575
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 3775 5950 3625
Wire Wire Line
	5950 3625 6150 3625
Wire Wire Line
	5725 3825 5725 3775
Connection ~ 5725 3775
Wire Wire Line
	5725 3775 5950 3775
Wire Wire Line
	5950 2850 5950 3425
Wire Wire Line
	5950 3425 6150 3425
Wire Wire Line
	5200 2850 5200 3825
Connection ~ 5200 2850
Wire Wire Line
	5200 2850 5950 2850
Wire Wire Line
	4675 3275 4675 3350
Wire Wire Line
	4675 2975 4675 2850
Connection ~ 4675 2850
Wire Wire Line
	4675 2850 5200 2850
Wire Wire Line
	4675 3725 4675 3775
Wire Wire Line
	4675 3775 5725 3775
Wire Wire Line
	4675 3350 4975 3350
Wire Wire Line
	4975 3350 4975 4375
Connection ~ 4675 3350
Wire Wire Line
	4675 3350 4675 3425
Connection ~ 5725 4375
Wire Wire Line
	5725 4375 6350 4375
Wire Wire Line
	5200 4375 5725 4375
Connection ~ 4675 3775
Text Label 3025 4975 1    50   ~ 0
EN_CAN
Wire Wire Line
	3775 3775 4675 3775
Wire Wire Line
	3775 4325 3775 4025
Wire Wire Line
	1300 4025 3775 4025
Connection ~ 3775 4025
Wire Wire Line
	3775 4025 3775 3775
Wire Wire Line
	3675 3825 3675 2850
Wire Wire Line
	1300 3825 3675 3825
Wire Wire Line
	3675 2850 4675 2850
Wire Wire Line
	2025 4225 2650 4225
Connection ~ 2025 4225
Wire Wire Line
	2250 1625 2250 3625
Connection ~ 3675 2850
Text Label 3025 3500 1    50   ~ 0
EN_CAN
Text Label 3675 3050 3    50   ~ 0
CAN_H
Text Label 2650 3025 3    50   ~ 0
OBD_H
Text Label 3325 4025 0    50   ~ 0
OBD_L
Text Label 2550 4325 0    50   ~ 0
CAN_L
Text HLabel 1275 5825 0    50   Input ~ 0
EN_CAN
$Comp
L Device:R R7
U 1 1 5F657D86
P 1450 6075
F 0 "R7" H 1520 6121 50  0000 L CNN
F 1 "220" H 1520 6030 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 1380 6075 50  0001 C CNN
F 3 "~" H 1450 6075 50  0001 C CNN
	1    1450 6075
	1    0    0    -1  
$EndComp
Wire Wire Line
	1275 5825 1450 5825
Wire Wire Line
	1450 5925 1450 5825
Connection ~ 1450 5825
Wire Wire Line
	1450 6225 1450 6300
Wire Wire Line
	1450 6300 2025 6300
Connection ~ 2025 6300
Wire Wire Line
	2025 6300 2025 6475
Wire Wire Line
	2375 1625 2375 4325
Wire Wire Line
	6350 4700 6350 4375
Connection ~ 6350 4375
Wire Wire Line
	6350 4375 7975 4375
Text HLabel 10450 3400 2    50   Input ~ 0
EN_Transceiver
Text Notes 6450 2625 2    50   ~ 0
Signal Filter
Text Label 3950 2850 0    50   ~ 0
Signal_H
Text Label 3950 3775 0    50   ~ 0
Signal_L
$Comp
L Board:FDV304P U12
U 1 1 5F60ADD9
P 1925 5825
F 0 "U12" H 1925 5825 50  0001 L BNN
F 1 "FDV304P" H 1925 5825 50  0001 L BNN
F 2 "Board:SOT23-3" H 1925 5825 50  0001 L BNN
F 3 "" H 1925 5825 50  0001 C CNN
	1    1925 5825
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 5825 1825 5825
Wire Wire Line
	2025 5925 2025 6300
$Comp
L Board:FDV304P U13
U 1 1 5F6176D2
P 3025 4425
F 0 "U13" H 3025 4425 50  0001 L BNN
F 1 "FDV304P" H 3025 4425 50  0001 L BNN
F 2 "Board:SOT23-3" H 3025 4425 50  0001 L BNN
F 3 "" H 3025 4425 50  0001 C CNN
	1    3025 4425
	0    1    -1   0   
$EndComp
Wire Wire Line
	3025 4525 3025 4975
Wire Wire Line
	2375 4325 2925 4325
Wire Wire Line
	3225 4325 3775 4325
$Comp
L Board:2N7002 Q7
U 1 1 5F62A0A8
P 2925 3050
F 0 "Q7" V 2971 2875 50  0000 R CNN
F 1 "2N7002" V 2880 2875 50  0000 R CNN
F 2 "Board:SOT23-3" H 2925 3050 50  0001 L BNN
F 3 "" H 2925 3050 50  0001 C CNN
	1    2925 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2650 2850 2650 4225
Wire Wire Line
	2650 2850 2825 2850
Wire Wire Line
	3025 3250 3025 3500
Wire Wire Line
	3025 2850 3675 2850
$Comp
L power:GND #PWR0105
U 1 1 5F91316D
P 10025 3100
F 0 "#PWR0105" H 10025 2850 50  0001 C CNN
F 1 "GND" H 10030 2927 50  0000 C CNN
F 2 "" H 10025 3100 50  0001 C CNN
F 3 "" H 10025 3100 50  0001 C CNN
	1    10025 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0106
U 1 1 5F913497
P 10025 3800
F 0 "#PWR0106" H 10025 3650 50  0001 C CNN
F 1 "+3.3V" H 10040 3973 50  0000 C CNN
F 2 "" H 10025 3800 50  0001 C CNN
F 3 "" H 10025 3800 50  0001 C CNN
	1    10025 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5F9161C7
P 6350 4700
F 0 "#PWR0107" H 6350 4450 50  0001 C CNN
F 1 "GND" H 6355 4527 50  0000 C CNN
F 2 "" H 6350 4700 50  0001 C CNN
F 3 "" H 6350 4700 50  0001 C CNN
	1    6350 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5F916540
P 2025 6475
F 0 "#PWR0108" H 2025 6225 50  0001 C CNN
F 1 "GND" H 2030 6302 50  0000 C CNN
F 2 "" H 2025 6475 50  0001 C CNN
F 3 "" H 2025 6475 50  0001 C CNN
	1    2025 6475
	1    0    0    -1  
$EndComp
$EndSCHEMATC
