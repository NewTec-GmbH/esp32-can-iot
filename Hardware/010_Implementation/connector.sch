EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x09_Female J?
U 1 1 5FA5ACF8
P 1075 3775
AR Path="/5F562A6B/5FA5ACF8" Ref="J?"  Part="1" 
AR Path="/5FA55ABF/5FA5ACF8" Ref="J2"  Part="1" 
F 0 "J2" H 967 3150 50  0000 C CNN
F 1 "Conn_01x09_Female" H 967 3241 50  0000 C CNN
F 2 "Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.84mm_EdgePinOffset4.94mm_Housed_MountingHolesOffset7.48mm" H 1075 3775 50  0001 C CNN
F 3 "~" H 1075 3775 50  0001 C CNN
	1    1075 3775
	-1   0    0    1   
$EndComp
Text Label 1725 2650 3    50   ~ 0
OBD_VDD
NoConn ~ 1275 3475
NoConn ~ 1275 3675
NoConn ~ 1275 3875
NoConn ~ 1275 4175
Text HLabel 1725 1350 1    50   Output ~ 0
OBD_VDD
Text Notes 1510 2935 2    50   ~ 0
DSUB-9 Connector\n
Text HLabel 8600 2575 0    50   BiDi ~ 0
BUS_H
Text HLabel 8600 3075 0    50   BiDi ~ 0
BUS_L
Wire Wire Line
	1275 3375 1725 3375
Wire Wire Line
	1725 1350 1725 3375
Wire Notes Line
	2675 750  725  750 
Wire Notes Line
	725  750  725  4425
Wire Notes Line
	725  4425 2675 4425
Text HLabel 5650 4250 0    50   Input ~ 0
OBD-CAN_Switch
$Comp
L Board:G5V-2-DC5 K1
U 1 1 5FB0FBE9
P 7375 2875
F 0 "K1" V 7471 2245 50  0000 R CNN
F 1 "G5V-2-DC5" V 7380 2245 50  0000 R CNN
F 2 "Board:RELAY_G5V-2-DC5" H 7375 2875 50  0001 L BNN
F 3 "Relay; E-Mech; Low Signal; DPDT; Cur-Rtg 0.5/2AAC/ADC; Ctrl-V 5DC; Vol-Rtg 125/30AC/DC" H 7375 2875 50  0001 L BNN
F 4 "Omron Electronics" H 7375 2875 50  0001 L BNN "Field4"
F 5 "QFN-68 Omron" H 7375 2875 50  0001 L BNN "Field5"
F 6 "Unavailable" H 7375 2875 50  0001 L BNN "Field6"
F 7 "None" H 7375 2875 50  0001 L BNN "Field7"
F 8 "G5V-2-DC5" H 7375 2875 50  0001 L BNN "Field8"
	1    7375 2875
	-1   0    0    1   
$EndComp
$Comp
L Board:G5V-2-DC5 K2
U 1 1 5FB1A5F7
P 9325 2875
F 0 "K2" V 9421 2245 50  0000 R CNN
F 1 "G5V-2-DC5" V 9330 2245 50  0000 R CNN
F 2 "Board:RELAY_G5V-2-DC5" H 9325 2875 50  0001 L BNN
F 3 "Relay; E-Mech; Low Signal; DPDT; Cur-Rtg 0.5/2AAC/ADC; Ctrl-V 5DC; Vol-Rtg 125/30AC/DC" H 9325 2875 50  0001 L BNN
F 4 "Omron Electronics" H 9325 2875 50  0001 L BNN "Field4"
F 5 "QFN-68 Omron" H 9325 2875 50  0001 L BNN "Field5"
F 6 "Unavailable" H 9325 2875 50  0001 L BNN "Field6"
F 7 "None" H 9325 2875 50  0001 L BNN "Field7"
F 8 "G5V-2-DC5" H 9325 2875 50  0001 L BNN "Field8"
	1    9325 2875
	-1   0    0    1   
$EndComp
$Comp
L Diode:1N4148 D8
U 1 1 5FB2B4A7
P 5650 2775
F 0 "D8" V 5604 2855 50  0000 L CNN
F 1 "1N4148" V 5695 2855 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5650 2600 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5650 2775 50  0001 C CNN
	1    5650 2775
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC817 Q1
U 1 1 5FB2FAF8
P 7350 4250
F 0 "Q1" H 7541 4296 50  0000 L CNN
F 1 "BC817" H 7541 4205 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7550 4175 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 7350 4250 50  0001 L CNN
	1    7350 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2625 5650 1500
Wire Wire Line
	5650 1500 7900 1500
Wire Wire Line
	9950 1500 9950 2475
Wire Wire Line
	9950 2475 9625 2475
Wire Wire Line
	7675 2475 7900 2475
Wire Wire Line
	7900 2475 7900 1500
Wire Wire Line
	9625 3275 9950 3275
Wire Wire Line
	9950 3275 9950 3650
Wire Wire Line
	5650 3650 5650 2925
Wire Wire Line
	7675 3275 7875 3275
Wire Wire Line
	7875 3275 7875 3650
Wire Wire Line
	7875 3650 7450 3650
Wire Wire Line
	7450 4050 7450 3650
Connection ~ 7450 3650
Wire Wire Line
	7450 3650 5650 3650
Wire Wire Line
	7450 4450 7450 4850
$Comp
L power:GND #PWR020
U 1 1 5FB36BEA
P 7450 4850
F 0 "#PWR020" H 7450 4600 50  0001 C CNN
F 1 "GND" H 7455 4677 50  0000 C CNN
F 2 "" H 7450 4850 50  0001 C CNN
F 3 "" H 7450 4850 50  0001 C CNN
	1    7450 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5FB372EA
P 6950 4600
F 0 "R15" H 7020 4646 50  0000 L CNN
F 1 "150" H 7020 4555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6880 4600 50  0001 C CNN
F 3 "~" H 6950 4600 50  0001 C CNN
	1    6950 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 5FB379FD
P 6600 4250
F 0 "R14" V 6393 4250 50  0000 C CNN
F 1 "430" V 6484 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6530 4250 50  0001 C CNN
F 3 "~" H 6600 4250 50  0001 C CNN
	1    6600 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	6750 4250 6950 4250
Wire Wire Line
	6950 4450 6950 4250
Connection ~ 6950 4250
Wire Wire Line
	6950 4250 7150 4250
$Comp
L power:GND #PWR019
U 1 1 5FB38603
P 6950 4850
F 0 "#PWR019" H 6950 4600 50  0001 C CNN
F 1 "GND" H 6955 4677 50  0000 C CNN
F 2 "" H 6950 4850 50  0001 C CNN
F 3 "" H 6950 4850 50  0001 C CNN
	1    6950 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 4750 6950 4850
Wire Wire Line
	6450 4250 5650 4250
Wire Wire Line
	7900 1500 8250 1500
Connection ~ 7900 1500
Wire Wire Line
	7875 3650 9950 3650
Connection ~ 7875 3650
Wire Wire Line
	2250 4075 2250 4175
Wire Wire Line
	1275 4075 2250 4075
Wire Wire Line
	1275 3575 3100 3575
Wire Wire Line
	1275 3775 3100 3775
Wire Wire Line
	1275 3975 3100 3975
Wire Wire Line
	2250 4175 3100 4175
Text Label 3100 3575 2    50   ~ 0
Pin_7
Text Label 3100 3775 2    50   ~ 0
Pin_5
Text Label 3100 3975 2    50   ~ 0
Pin_3
Text Label 3100 4175 2    50   ~ 0
Pin_2
Wire Wire Line
	8925 2575 8600 2575
Wire Wire Line
	8925 2375 8600 2375
Text Label 8600 2375 0    50   ~ 0
Pin_7
Wire Wire Line
	8925 2775 8600 2775
Text Label 8600 2775 0    50   ~ 0
Pin_3
Wire Wire Line
	8925 3075 8600 3075
Wire Notes Line
	2675 4425 2675 750 
$Comp
L power:GND #PWR018
U 1 1 5FB4D7F5
P 6475 3125
F 0 "#PWR018" H 6475 2875 50  0001 C CNN
F 1 "GND" H 6480 2952 50  0000 C CNN
F 2 "" H 6475 3125 50  0001 C CNN
F 3 "" H 6475 3125 50  0001 C CNN
	1    6475 3125
	1    0    0    -1  
$EndComp
Wire Wire Line
	6975 3075 6475 3075
Wire Wire Line
	6475 3075 6475 3125
Wire Wire Line
	8925 2875 8600 2875
Wire Wire Line
	8925 3275 8600 3275
Wire Wire Line
	6975 3275 6650 3275
Wire Wire Line
	6975 2875 6650 2875
Text Label 8600 2875 0    50   ~ 0
Pin_2
Text Label 8600 3275 0    50   ~ 0
Pin_5
Text Label 6650 2875 0    50   ~ 0
Pin_3
Text Label 6650 3275 0    50   ~ 0
Pin_2
Wire Wire Line
	6475 2575 6475 2775
Wire Wire Line
	6475 2575 6975 2575
Connection ~ 6475 3075
Wire Wire Line
	6975 2775 6475 2775
Connection ~ 6475 2775
Wire Wire Line
	6475 2775 6475 3075
Wire Wire Line
	6475 2375 6975 2375
Text Label 6475 2375 0    50   ~ 0
CAN_Mode
Text Notes 5975 1175 0    50   ~ 0
Pin 2:   OBD_GND        //    CAN_L\nPin 3:   OBD_H          //    CAN_GND\nPin 5:   OBD_L           //    ------ \nPin 7:   -------      //    CAN_H
$Comp
L Device:LED D?
U 1 1 5FB5FD23
P 4050 5675
AR Path="/5F52F099/5FB5FD23" Ref="D?"  Part="1" 
AR Path="/5FA55ABF/5FB5FD23" Ref="D7"  Part="1" 
F 0 "D7" V 4089 5557 50  0000 R CNN
F 1 "RED" V 3998 5557 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 4050 5675 50  0001 C CNN
F 3 "~" H 4050 5675 50  0001 C CNN
	1    4050 5675
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5FB5FD29
P 4050 6150
AR Path="/5F52F099/5FB5FD29" Ref="R?"  Part="1" 
AR Path="/5FA55ABF/5FB5FD29" Ref="R13"  Part="1" 
F 0 "R13" H 4120 6196 50  0000 L CNN
F 1 "500" H 4120 6105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3980 6150 50  0001 C CNN
F 3 "~" H 4050 6150 50  0001 C CNN
	1    4050 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 5825 4050 6000
Wire Wire Line
	4050 5525 4050 5200
Text Label 4050 6875 1    50   ~ 0
CAN_Mode
Wire Wire Line
	4050 6300 4050 6875
$Comp
L power:+3.3V #PWR017
U 1 1 5FB62F1D
P 4050 5200
F 0 "#PWR017" H 4050 5050 50  0001 C CNN
F 1 "+3.3V" H 4065 5373 50  0000 C CNN
F 2 "" H 4050 5200 50  0001 C CNN
F 3 "" H 4050 5200 50  0001 C CNN
	1    4050 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5FA1A73B
P 8250 1325
F 0 "#PWR?" H 8250 1175 50  0001 C CNN
F 1 "+5V" H 8265 1498 50  0000 C CNN
F 2 "" H 8250 1325 50  0001 C CNN
F 3 "" H 8250 1325 50  0001 C CNN
	1    8250 1325
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1500 8250 1325
Connection ~ 8250 1500
Wire Wire Line
	8250 1500 9950 1500
$EndSCHEMATC
