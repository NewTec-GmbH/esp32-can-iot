EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
Title "CAN_Bus Analyzer - Power Supply - EXT MF Switch"
Date "2020-09-07"
Rev "1.0"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 8200 1500 2    50   Output ~ 0
V_OUT
Text HLabel 3600 1500 0    50   Input ~ 0
V_IN
Text HLabel 2100 3125 0    50   Input ~ 0
EN
Text HLabel 6425 4225 3    50   Input ~ 0
GND
Connection ~ 6425 3900
Wire Wire Line
	6425 3900 6425 4225
Wire Wire Line
	2675 3125 2100 3125
$Comp
L Device:R R?
U 1 1 5F5D2774
P 6425 2950
AR Path="/5F52EFB7/5F56212F/5F5D2774" Ref="R?"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5D2774" Ref="R4"  Part="1" 
F 0 "R4" H 6495 2996 50  0000 L CNN
F 1 "220" H 6495 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 6355 2950 50  0001 C CNN
F 3 "~" H 6425 2950 50  0001 C CNN
	1    6425 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6425 3100 6425 3225
Wire Wire Line
	3600 1500 5000 1500
Connection ~ 6425 1500
Wire Wire Line
	6425 3225 7400 3225
Wire Wire Line
	7400 3225 7400 1800
Connection ~ 6425 3225
Wire Wire Line
	7400 1800 5575 1800
Wire Wire Line
	6025 2925 5000 2925
Wire Wire Line
	5000 2925 5000 2350
Wire Wire Line
	6025 2925 6025 2400
Connection ~ 5000 1500
Wire Wire Line
	5000 1500 5375 1500
$Comp
L Device:R R?
U 1 1 5F5D2786
P 5000 2200
AR Path="/5F52EFB7/5F56212F/5F5D2786" Ref="R?"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5D2786" Ref="R3"  Part="1" 
F 0 "R3" H 5070 2246 50  0000 L CNN
F 1 "220" H 5070 2155 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 4930 2200 50  0001 C CNN
F 3 "~" H 5000 2200 50  0001 C CNN
	1    5000 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2050 5000 1500
$Comp
L Board:FDV304P U?
U 1 1 5F5D278D
P 5575 1600
AR Path="/5F52EFB7/5F56212F/5F5D278D" Ref="U?"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5D278D" Ref="U6"  Part="1" 
F 0 "U6" H 5575 1600 50  0001 L BNN
F 1 "FDV304P" H 5575 1600 50  0001 L BNN
F 2 "Board:SOT23-3" H 5575 1600 50  0001 L BNN
F 3 "" H 5575 1600 50  0001 C CNN
	1    5575 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5575 1700 5575 1800
Wire Wire Line
	5675 1500 6425 1500
$Comp
L Board:FDV304P U?
U 1 1 5F5D2795
P 7400 1600
AR Path="/5F52EFB7/5F56212F/5F5D2795" Ref="U?"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5D2795" Ref="U8"  Part="1" 
F 0 "U8" H 7400 1600 50  0001 L BNN
F 1 "FDV304P" H 7400 1600 50  0001 L BNN
F 2 "Board:SOT23-3" H 7400 1600 50  0001 L BNN
F 3 "" H 7400 1600 50  0001 C CNN
	1    7400 1600
	0    1    -1   0   
$EndComp
Wire Wire Line
	7600 1500 8200 1500
Wire Wire Line
	7400 1700 7400 1800
Connection ~ 7400 1800
Wire Wire Line
	6425 1500 7300 1500
$Comp
L Board:FDV304P U?
U 1 1 5F5D279F
P 6325 2400
AR Path="/5F52EFB7/5F56212F/5F5D279F" Ref="U?"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5D279F" Ref="U7"  Part="1" 
F 0 "U7" H 6325 2400 50  0001 L BNN
F 1 "FDV304P" H 6325 2400 50  0001 L BNN
F 2 "Board:SOT23-3" H 6325 2400 50  0001 L BNN
F 3 "" H 6325 2400 50  0001 C CNN
	1    6325 2400
	1    0    0    1   
$EndComp
Wire Wire Line
	6425 2600 6425 2800
Wire Wire Line
	6025 2400 6225 2400
Wire Wire Line
	6425 1500 6425 2300
$Comp
L Board:2N7002 Q?
U 1 1 5F5D27A8
P 6225 3525
AR Path="/5F52EFB7/5F56212F/5F5D27A8" Ref="Q?"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5D27A8" Ref="Q3"  Part="1" 
F 0 "Q3" H 6225 3837 50  0000 C CNN
F 1 "2N7002" H 6225 3746 50  0000 C CNN
F 2 "Board:SOT23-3" H 6225 3525 50  0001 L BNN
F 3 "" H 6225 3525 50  0001 C CNN
	1    6225 3525
	1    0    0    -1  
$EndComp
Wire Wire Line
	6425 3225 6425 3425
Wire Wire Line
	6425 3625 6425 3900
Wire Wire Line
	6025 2925 6025 3625
Connection ~ 6025 2925
$Comp
L Board:2N7002 Q?
U 1 1 5F5E0FC7
P 2875 3025
AR Path="/5F52EFB7/5F56212F/5F5E0FC7" Ref="Q?"  Part="1" 
AR Path="/5F52EFB7/5F566EF5/5F5E0FC7" Ref="Q2"  Part="1" 
F 0 "Q2" H 2875 3337 50  0000 C CNN
F 1 "2N7002" H 2875 3246 50  0000 C CNN
F 2 "Board:SOT23-3" H 2875 3025 50  0001 L BNN
F 3 "" H 2875 3025 50  0001 C CNN
	1    2875 3025
	1    0    0    -1  
$EndComp
Wire Wire Line
	3075 3900 6425 3900
Wire Wire Line
	3075 3125 3075 3900
Wire Wire Line
	5000 2925 3075 2925
Connection ~ 5000 2925
$EndSCHEMATC
