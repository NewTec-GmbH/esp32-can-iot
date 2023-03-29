EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title "CAN_Bus Analyzer - Power Supply - USB MF Switch"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 4325 3700 0    50   Input ~ 0
EN_2
Text HLabel 8650 1775 2    50   Output ~ 0
V_OUT
Text HLabel 4050 1775 0    50   Input ~ 0
V_IN
Text HLabel 6875 4500 3    50   Input ~ 0
GND
Connection ~ 6875 4175
Wire Wire Line
	6875 4175 6875 4500
Wire Wire Line
	3125 3400 2550 3400
$Comp
L Device:R R?
U 1 1 5F5F5950
P 6875 3225
AR Path="/5F52EFB7/5F56212F/5F5F5950" Ref="R?"  Part="1" 
AR Path="/5F52EFB7/5F5717B1/5F5F5950" Ref="R6"  Part="1" 
F 0 "R6" H 6945 3271 50  0000 L CNN
F 1 "220" H 6945 3180 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 6805 3225 50  0001 C CNN
F 3 "~" H 6875 3225 50  0001 C CNN
	1    6875 3225
	1    0    0    -1  
$EndComp
Wire Wire Line
	6875 3375 6875 3500
Wire Wire Line
	4050 1775 5450 1775
Connection ~ 6875 1775
Wire Wire Line
	6875 3500 7850 3500
Wire Wire Line
	7850 3500 7850 2075
Connection ~ 6875 3500
Wire Wire Line
	7850 2075 6025 2075
Wire Wire Line
	6475 3200 5450 3200
Wire Wire Line
	5450 3200 5450 2625
Wire Wire Line
	6475 3200 6475 2675
Connection ~ 5450 1775
Wire Wire Line
	5450 1775 5825 1775
$Comp
L Device:R R?
U 1 1 5F5F5962
P 5450 2475
AR Path="/5F52EFB7/5F56212F/5F5F5962" Ref="R?"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5F5962" Ref="R?"  Part="1" 
AR Path="/5F52EFB7/5F5717B1/5F5F5962" Ref="R5"  Part="1" 
F 0 "R5" H 5520 2521 50  0000 L CNN
F 1 "220" H 5520 2430 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 5380 2475 50  0001 C CNN
F 3 "~" H 5450 2475 50  0001 C CNN
	1    5450 2475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2325 5450 1775
$Comp
L Board:FDV304P U?
U 1 1 5F5F5969
P 6025 1875
AR Path="/5F52EFB7/5F56212F/5F5F5969" Ref="U?"  Part="1" 
AR Path="/5F52EFB7/5F5717B1/5F5F5969" Ref="U9"  Part="1" 
F 0 "U9" H 6025 1875 50  0001 L BNN
F 1 "FDV304P" H 6025 1875 50  0001 L BNN
F 2 "Board:SOT23-3" H 6025 1875 50  0001 L BNN
F 3 "" H 6025 1875 50  0001 C CNN
	1    6025 1875
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6025 1975 6025 2075
Wire Wire Line
	6125 1775 6875 1775
$Comp
L Board:FDV304P U?
U 1 1 5F5F5971
P 7850 1875
AR Path="/5F52EFB7/5F56212F/5F5F5971" Ref="U?"  Part="1" 
AR Path="/5F52EFB7/5F5717B1/5F5F5971" Ref="U11"  Part="1" 
F 0 "U11" H 7850 1875 50  0001 L BNN
F 1 "FDV304P" H 7850 1875 50  0001 L BNN
F 2 "Board:SOT23-3" H 7850 1875 50  0001 L BNN
F 3 "" H 7850 1875 50  0001 C CNN
	1    7850 1875
	0    1    -1   0   
$EndComp
Wire Wire Line
	8050 1775 8650 1775
Wire Wire Line
	7850 1975 7850 2075
Connection ~ 7850 2075
Wire Wire Line
	6875 1775 7750 1775
$Comp
L Board:FDV304P U?
U 1 1 5F5F597B
P 6775 2675
AR Path="/5F52EFB7/5F56212F/5F5F597B" Ref="U?"  Part="1" 
AR Path="/5F52EFB7/5F5717B1/5F5F597B" Ref="U10"  Part="1" 
F 0 "U10" H 6775 2675 50  0001 L BNN
F 1 "FDV304P" H 6775 2675 50  0001 L BNN
F 2 "Board:SOT23-3" H 6775 2675 50  0001 L BNN
F 3 "" H 6775 2675 50  0001 C CNN
	1    6775 2675
	1    0    0    1   
$EndComp
Wire Wire Line
	6875 2875 6875 3075
Wire Wire Line
	6475 2675 6675 2675
Wire Wire Line
	6875 1775 6875 2575
$Comp
L Board:2N7002 Q?
U 1 1 5F5F5984
P 6675 3800
AR Path="/5F52EFB7/5F56212F/5F5F5984" Ref="Q?"  Part="1" 
AR Path="/5F52EFB7/5F5717B1/5F5F5984" Ref="Q6"  Part="1" 
F 0 "Q6" H 6675 4112 50  0000 C CNN
F 1 "2N7002" H 6675 4021 50  0000 C CNN
F 2 "Board:SOT23-3" H 6675 3800 50  0001 L BNN
F 3 "" H 6675 3800 50  0001 C CNN
	1    6675 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6875 3500 6875 3700
Wire Wire Line
	6875 3900 6875 4175
Wire Wire Line
	6475 3200 6475 3900
Connection ~ 6475 3200
$Comp
L Board:2N7002 Q?
U 1 1 5F5F598E
P 3325 3300
AR Path="/5F52EFB7/5F56212F/5F5F598E" Ref="Q?"  Part="1" 
AR Path="/5F52EFB7/5F5717B1/5F5F598E" Ref="Q4"  Part="1" 
F 0 "Q4" H 3325 3612 50  0000 C CNN
F 1 "2N7002" H 3325 3521 50  0000 C CNN
F 2 "Board:SOT23-3" H 3325 3300 50  0001 L BNN
F 3 "" H 3325 3300 50  0001 C CNN
	1    3325 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3525 4175 4875 4175
Wire Wire Line
	3525 3400 3525 4175
Wire Wire Line
	5450 3200 4875 3200
Connection ~ 5450 3200
$Comp
L Board:2N7002 Q?
U 1 1 5F60148B
P 4675 3600
AR Path="/5F52EFB7/5F56212F/5F60148B" Ref="Q?"  Part="1" 
AR Path="/5F52EFB7/5F5717B1/5F60148B" Ref="Q5"  Part="1" 
F 0 "Q5" H 4675 3912 50  0000 C CNN
F 1 "2N7002" H 4675 3821 50  0000 C CNN
F 2 "Board:SOT23-3" H 4675 3600 50  0001 L BNN
F 3 "" H 4675 3600 50  0001 C CNN
	1    4675 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4325 3700 4475 3700
Wire Wire Line
	4875 3700 4875 4175
Connection ~ 4875 4175
Wire Wire Line
	4875 4175 6875 4175
Wire Wire Line
	4875 3500 4875 3200
Connection ~ 4875 3200
Wire Wire Line
	4875 3200 3525 3200
Text HLabel 2550 3400 0    50   Input ~ 0
EN_1
$EndSCHEMATC
