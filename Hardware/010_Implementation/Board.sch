EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title "CAN_Bus Analyzer - Block Overview"
Date "2021-02-04"
Rev "1.1"
Comp "NewTec Gmbh."
Comment1 "Reyes, Gabryel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 4650 3625 1300 475 
U 5F562A6B
F0 "CAN_Transceiver" 50
F1 "CAN_Transceiver.sch" 50
F2 "CAN_Rx" O R 5950 3925 50 
F3 "CAN_Tx" I R 5950 3825 50 
F4 "BUS_H" B L 4650 3825 50 
F5 "BUS_L" B L 4650 3925 50 
$EndSheet
$Sheet
S 6075 3625 1075 900 
U 5F52F099
F0 "MCU" 50
F1 "MCU.sch" 50
F2 "CAN_Tx" O L 6075 3825 50 
F3 "CAN_Rx" I L 6075 3925 50 
F4 "OBD_Voltage_Check" I R 7150 4125 50 
F5 "~OBD~\\CAN" O L 6075 4325 50 
F6 "Relay_Supply" O L 6075 4440 50 
$EndSheet
$Sheet
S 3300 3625 1200 900 
U 5FA55ABF
F0 "Connector" 50
F1 "connector.sch" 50
F2 "OBD_VDD" O L 3300 3750 50 
F3 "BUS_H" B R 4500 3825 50 
F4 "BUS_L" B R 4500 3925 50 
F5 "~OBD~\\CAN" I R 4500 4325 50 
F6 "Relay_Supply" I R 4500 4440 50 
$EndSheet
Wire Wire Line
	5950 3825 6075 3825
Wire Wire Line
	6075 3925 5950 3925
Wire Wire Line
	4500 3825 4650 3825
Wire Wire Line
	4650 3925 4500 3925
Wire Wire Line
	3300 3750 3175 3750
Wire Wire Line
	3175 3750 3175 3075
Wire Wire Line
	3175 3075 3900 3075
Wire Wire Line
	4500 4325 6075 4325
Wire Wire Line
	6725 2850 7525 2850
Wire Wire Line
	7525 2850 7525 4125
Wire Wire Line
	7525 4125 7150 4125
$Sheet
S 3900 2650 2825 525 
U 5F52EFB7
F0 "Power Supply" 50
F1 "Netzteil.sch" 50
F2 "OBD_VDD" I L 3900 3075 50 
F3 "OBD_Voltage_Check" O R 6725 2850 50 
$EndSheet
Wire Wire Line
	4500 4440 6075 4440
$EndSCHEMATC
