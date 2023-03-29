EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title "CAN_Bus Analyzer - Power Supply"
Date "2021-02-04"
Rev "1.1"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1760 3200 0    50   Input ~ 0
OBD_VDD
Text Notes 4100 2510 2    50   ~ 0
12V-OBD Power Supply
$Comp
L Device:R R1
U 1 1 5FAFFDE5
P 4455 3890
F 0 "R1" H 4525 3936 50  0000 L CNN
F 1 "10k" H 4525 3845 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4385 3890 50  0001 C CNN
F 3 "~" H 4455 3890 50  0001 C CNN
	1    4455 3890
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5FB008D2
P 4560 4825
F 0 "R2" H 4630 4871 50  0000 L CNN
F 1 "1k" H 4630 4780 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4490 4825 50  0001 C CNN
F 3 "~" H 4560 4825 50  0001 C CNN
	1    4560 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	4455 4040 4455 4600
Wire Wire Line
	4455 4600 4560 4600
Connection ~ 4455 4600
Text HLabel 4880 4600 2    50   Output ~ 0
OBD_Voltage_Check
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5FB093DE
P 5730 3200
F 0 "#FLG01" H 5730 3275 50  0001 C CNN
F 1 "PWR_FLAG" H 5730 3373 50  0000 C CNN
F 2 "" H 5730 3200 50  0001 C CNN
F 3 "~" H 5730 3200 50  0001 C CNN
	1    5730 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5FB0CD60
P 4080 4825
F 0 "C1" H 4195 4871 50  0000 L CNN
F 1 "100n" H 4195 4780 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4118 4675 50  0001 C CNN
F 3 "~" H 4080 4825 50  0001 C CNN
	1    4080 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	4455 4600 4080 4600
Wire Wire Line
	4080 4600 4080 4675
Wire Wire Line
	4080 4975 4080 5100
$Comp
L power:GND #PWR01
U 1 1 5FB6777E
P 4280 5275
F 0 "#PWR01" H 4280 5025 50  0001 C CNN
F 1 "GND" H 4285 5102 50  0000 C CNN
F 2 "" H 4280 5275 50  0001 C CNN
F 3 "" H 4280 5275 50  0001 C CNN
	1    4280 5275
	1    0    0    -1  
$EndComp
Wire Wire Line
	4280 5275 4280 5100
Connection ~ 4280 5100
Wire Wire Line
	4280 5100 4080 5100
$Comp
L power:+5V #PWR05
U 1 1 5FA170AE
P 9795 3125
F 0 "#PWR05" H 9795 2975 50  0001 C CNN
F 1 "+5V" H 9810 3298 50  0000 C CNN
F 2 "" H 9795 3125 50  0001 C CNN
F 3 "" H 9795 3125 50  0001 C CNN
	1    9795 3125
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5FB3AA0A
P 7135 3200
F 0 "L1" V 7325 3200 50  0000 C CNN
F 1 "2.2u" V 7234 3200 50  0000 C CNN
F 2 "Board:INDPM5550X300N" H 7135 3200 50  0001 C CNN
F 3 "~" H 7135 3200 50  0001 C CNN
	1    7135 3200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5FB3B31A
P 6735 4600
F 0 "R3" V 6528 4600 50  0000 C CNN
F 1 "10k" V 6619 4600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6665 4600 50  0001 C CNN
F 3 "~" H 6735 4600 50  0001 C CNN
	1    6735 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	7285 3200 7410 3200
Wire Wire Line
	6060 4600 6585 4600
Wire Wire Line
	7410 4600 7410 3300
Connection ~ 7410 3200
Wire Wire Line
	6885 4600 7410 4600
$Comp
L power:GND #PWR03
U 1 1 5FB3F4B3
P 6460 4125
F 0 "#PWR03" H 6460 3875 50  0001 C CNN
F 1 "GND" H 6465 3952 50  0000 C CNN
F 2 "" H 6460 4125 50  0001 C CNN
F 3 "" H 6460 4125 50  0001 C CNN
	1    6460 4125
	1    0    0    -1  
$EndComp
Connection ~ 7410 3300
Wire Wire Line
	7410 3300 7410 3200
$Comp
L Device:C C2
U 1 1 5FB43F56
P 5460 3475
F 0 "C2" H 5575 3521 50  0000 L CNN
F 1 "10u" H 5575 3430 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5498 3325 50  0001 C CNN
F 3 "~" H 5460 3475 50  0001 C CNN
	1    5460 3475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5935 3300 5935 3200
Connection ~ 5935 3200
Wire Wire Line
	5460 3325 5460 3200
Wire Wire Line
	5460 3200 5730 3200
$Comp
L power:GND #PWR02
U 1 1 5FB459AA
P 5460 3800
F 0 "#PWR02" H 5460 3550 50  0001 C CNN
F 1 "GND" H 5465 3627 50  0000 C CNN
F 2 "" H 5460 3800 50  0001 C CNN
F 3 "" H 5460 3800 50  0001 C CNN
	1    5460 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5460 3800 5460 3625
$Comp
L power:GND #PWR04
U 1 1 5FB4620B
P 8835 4175
F 0 "#PWR04" H 8835 3925 50  0001 C CNN
F 1 "GND" H 8840 4002 50  0000 C CNN
F 2 "" H 8835 4175 50  0001 C CNN
F 3 "" H 8835 4175 50  0001 C CNN
	1    8835 4175
	1    0    0    -1  
$EndComp
Wire Wire Line
	9795 3200 9795 3125
$Comp
L Device:C C3
U 1 1 5FB437F9
P 8460 3400
F 0 "C3" H 8575 3446 50  0000 L CNN
F 1 "22u" H 8575 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 8498 3250 50  0001 C CNN
F 3 "~" H 8460 3400 50  0001 C CNN
	1    8460 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7410 3200 7760 3200
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5FB4D740
P 9620 3200
F 0 "#FLG02" H 9620 3275 50  0001 C CNN
F 1 "PWR_FLAG" H 9620 3373 50  0000 C CNN
F 2 "" H 9620 3200 50  0001 C CNN
F 3 "~" H 9620 3200 50  0001 C CNN
	1    9620 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9620 3200 9795 3200
Wire Wire Line
	4280 5100 4560 5100
Wire Wire Line
	4560 4975 4560 5100
Wire Wire Line
	4560 4675 4560 4600
Connection ~ 4560 4600
Wire Wire Line
	4560 4600 4880 4600
Wire Wire Line
	6060 3600 6060 4600
Wire Wire Line
	6860 3200 6985 3200
Wire Wire Line
	6860 3300 7410 3300
Wire Wire Line
	6560 3950 6560 3900
Wire Wire Line
	8460 3550 8460 4110
Wire Wire Line
	8835 4110 8835 4175
$Comp
L Device:C C9
U 1 1 5FAD5DF4
P 4770 3475
F 0 "C9" H 4885 3521 50  0000 L CNN
F 1 "100n" H 4885 3430 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4808 3325 50  0001 C CNN
F 3 "~" H 4770 3475 50  0001 C CNN
	1    4770 3475
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5FAD82B6
P 4770 3800
F 0 "#PWR0103" H 4770 3550 50  0001 C CNN
F 1 "GND" H 4775 3627 50  0000 C CNN
F 2 "" H 4770 3800 50  0001 C CNN
F 3 "" H 4770 3800 50  0001 C CNN
	1    4770 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4770 3800 4770 3625
Wire Wire Line
	4770 3325 4770 3200
$Comp
L Device:Ferrite_Bead FB1
U 1 1 5FADEE61
P 5105 3200
F 0 "FB1" V 4831 3200 50  0000 C CNN
F 1 "Ferrite_Bead" V 4922 3200 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5035 3200 50  0001 C CNN
F 3 "~" H 5105 3200 50  0001 C CNN
	1    5105 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	4770 3200 4955 3200
Connection ~ 4770 3200
Wire Wire Line
	5460 3200 5255 3200
Connection ~ 5460 3200
Connection ~ 8460 4110
Wire Wire Line
	8460 3250 8460 3200
$Comp
L Device:Ferrite_Bead FB2
U 1 1 5FAE6E42
P 8775 3200
F 0 "FB2" V 8501 3200 50  0000 C CNN
F 1 "Ferrite_Bead" V 8592 3200 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8705 3200 50  0001 C CNN
F 3 "~" H 8775 3200 50  0001 C CNN
	1    8775 3200
	0    1    1    0   
$EndComp
Connection ~ 8460 3200
Wire Wire Line
	8460 3200 8625 3200
Wire Wire Line
	9150 4110 9150 3550
$Comp
L Device:C C10
U 1 1 5FAEA108
P 9150 3400
F 0 "C10" H 9265 3446 50  0000 L CNN
F 1 "100n" H 9265 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 9188 3250 50  0001 C CNN
F 3 "~" H 9150 3400 50  0001 C CNN
	1    9150 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 3200 9150 3250
Wire Wire Line
	8925 3200 9150 3200
Connection ~ 9620 3200
Connection ~ 9150 3200
Wire Wire Line
	9150 3200 9620 3200
Wire Wire Line
	7760 3245 7760 3200
Wire Wire Line
	6860 3595 6860 3400
Wire Wire Line
	7760 3595 7760 3645
Connection ~ 7760 3595
Wire Wire Line
	7760 3595 6860 3595
Wire Wire Line
	7760 3945 7760 4110
Wire Wire Line
	7760 3545 7760 3595
$Comp
L Device:R R20
U 1 1 5FAC2DDF
P 7760 3795
F 0 "R20" H 7830 3841 50  0000 L CNN
F 1 "180k" H 7830 3750 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7690 3795 50  0001 C CNN
F 3 "~" H 7760 3795 50  0001 C CNN
F 4 "NP" H 7760 3795 50  0001 C CNN "NP"
	1    7760 3795
	1    0    0    -1  
$EndComp
$Comp
L Device:R R19
U 1 1 5FAC28BD
P 7760 3395
F 0 "R19" H 7830 3441 50  0000 L CNN
F 1 "910k" H 7830 3350 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7690 3395 50  0001 C CNN
F 3 "~" H 7760 3395 50  0001 C CNN
F 4 "NP" H 7760 3395 50  0001 C CNN "NP"
	1    7760 3395
	1    0    0    -1  
$EndComp
Connection ~ 7760 3200
Wire Wire Line
	7760 3200 8460 3200
Wire Wire Line
	7760 4110 8460 4110
Connection ~ 5730 3200
Wire Wire Line
	5730 3200 5935 3200
Wire Wire Line
	1760 3200 2080 3200
$Comp
L Device:Fuse F1
U 1 1 5FCB2092
P 2230 3200
F 0 "F1" V 2033 3200 50  0000 C CNN
F 1 "R452002" V 2124 3200 50  0000 C CNN
F 2 "Fuse:Fuse_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 2160 3200 50  0001 C CNN
F 3 "https://www.littelfuse.com/~/media/electronics/datasheets/tvs_diodes/littelfuse_tvs_diode_smaj_datasheet.pdf.pdf" H 2230 3200 50  0001 C CNN
F 4 "Yes" H 2230 3200 50  0001 C CNN "Vorhanden"
	1    2230 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	2380 3200 2530 3200
Wire Wire Line
	4455 3200 4455 3740
Connection ~ 4455 3200
Wire Wire Line
	4455 3200 4770 3200
$Comp
L Device:D D8
U 1 1 5FCB70B6
P 2530 3480
F 0 "D8" V 2484 3560 50  0000 L CNN
F 1 "SMAJ16A" V 2575 3560 50  0000 L CNN
F 2 "Diode_SMD:D_SMA" H 2530 3480 50  0001 C CNN
F 3 "https://m.littelfuse.com/~/media/electronics/datasheets/tvs_diodes/littelfuse_tvs_diode_smaj_datasheet.pdf.pdf" H 2530 3480 50  0001 C CNN
F 4 "Yes" H 2530 3480 50  0001 C CNN "Vorhanden"
	1    2530 3480
	0    1    1    0   
$EndComp
$Comp
L Device:C C16
U 1 1 5FCB7C90
P 3210 3485
F 0 "C16" H 3325 3531 50  0000 L CNN
F 1 "10u" H 3325 3440 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3248 3335 50  0001 C CNN
F 3 "~" H 3210 3485 50  0001 C CNN
	1    3210 3485
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Core_Iron L3
U 1 1 5FCB8E0F
P 2890 3200
F 0 "L3" V 2709 3200 50  0000 C CNN
F 1 "5u" V 2800 3200 50  0000 C CNN
F 2 "Board:INDPM5550X300N" H 2890 3200 50  0001 C CNN
F 3 "~" H 2890 3200 50  0001 C CNN
F 4 "Yes" H 2890 3200 50  0001 C CNN "Vorhanden"
	1    2890 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	3040 3200 3210 3200
Wire Wire Line
	3210 3335 3210 3200
Connection ~ 3210 3200
Wire Wire Line
	3210 3200 4455 3200
Wire Wire Line
	2530 3330 2530 3200
Connection ~ 2530 3200
Wire Wire Line
	2530 3200 2740 3200
$Comp
L power:GND #PWR032
U 1 1 5FCBBE89
P 2530 3775
F 0 "#PWR032" H 2530 3525 50  0001 C CNN
F 1 "GND" H 2535 3602 50  0000 C CNN
F 2 "" H 2530 3775 50  0001 C CNN
F 3 "" H 2530 3775 50  0001 C CNN
	1    2530 3775
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR033
U 1 1 5FCBCF3B
P 3210 3780
F 0 "#PWR033" H 3210 3530 50  0001 C CNN
F 1 "GND" H 3215 3607 50  0000 C CNN
F 2 "" H 3210 3780 50  0001 C CNN
F 3 "" H 3210 3780 50  0001 C CNN
	1    3210 3780
	1    0    0    -1  
$EndComp
Wire Wire Line
	3210 3780 3210 3635
Wire Wire Line
	2530 3630 2530 3775
Wire Wire Line
	8460 4110 8835 4110
Connection ~ 8835 4110
Wire Wire Line
	8835 4110 9150 4110
Text Notes 6005 4985 0    50   ~ 0
180kOm for Adjustable Version. 0Ohm for fixed 5V\n
$Comp
L Board:TPS62170DGK U1
U 1 1 5FB078C3
P 6460 2950
F 0 "U1" H 6460 2967 50  0000 C CNN
F 1 "TPS62160DGK" H 6460 2876 50  0000 C CNN
F 2 "Package_SO:VSSOP-8_3.0x3.0mm_P0.65mm" H 6210 2850 50  0001 C CNN
F 3 "" H 6210 2850 50  0001 C CNN
	1    6460 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6460 3900 6460 3950
Wire Wire Line
	5935 3300 6060 3300
Wire Wire Line
	5935 3200 6060 3200
Wire Wire Line
	6560 3950 6460 3950
Connection ~ 6460 3950
Wire Wire Line
	6460 3950 6460 4125
$EndSCHEMATC
