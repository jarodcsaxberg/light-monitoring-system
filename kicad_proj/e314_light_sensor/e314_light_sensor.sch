EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Light Sensor"
Date "2020-03-09"
Rev "R001"
Comp "Indiana University"
Comment1 "Here's a comment"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32L4:STM32L432KCUx U3
U 1 1 5E66D899
P 9050 4750
F 0 "U3" H 9450 5850 50  0000 C CNN
F 1 "STM32L432KCUx" H 9500 5750 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-32-1EP_5x5mm_P0.5mm_EP3.45x3.45mm" H 8650 3850 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00257205.pdf" H 9050 4750 50  0001 C CNN
	1    9050 4750
	1    0    0    -1  
$EndComp
$Comp
L e314_light_sensor-rescue:STDC14-e314_parts U2
U 1 1 5E69AC05
P 8350 1150
F 0 "U2" H 8350 1365 50  0000 C CNN
F 1 "STDC14" H 8350 1274 50  0000 C CNN
F 2 "e314_parts:ftsh_14p_connector" H 8350 1150 50  0001 C CNN
F 3 "" H 8350 1150 50  0001 C CNN
	1    8350 1150
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR012
U 1 1 5E6A3D66
P 7450 1200
F 0 "#PWR012" H 7450 1050 50  0001 C CNN
F 1 "VCC" H 7465 1373 50  0000 C CNN
F 2 "" H 7450 1200 50  0001 C CNN
F 3 "" H 7450 1200 50  0001 C CNN
	1    7450 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 1200 7450 1300
Wire Wire Line
	7450 1300 7750 1300
$Comp
L power:GND #PWR013
U 1 1 5E6A4CE9
P 7450 1900
F 0 "#PWR013" H 7450 1650 50  0001 C CNN
F 1 "GND" H 7455 1727 50  0000 C CNN
F 2 "" H 7450 1900 50  0001 C CNN
F 3 "" H 7450 1900 50  0001 C CNN
	1    7450 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 1900 7450 1700
Wire Wire Line
	7450 1700 7750 1700
Wire Wire Line
	7450 1700 7450 1500
Wire Wire Line
	7450 1500 7750 1500
Connection ~ 7450 1700
Wire Wire Line
	7750 1400 7450 1400
Wire Wire Line
	7450 1400 7450 1500
Connection ~ 7450 1500
NoConn ~ 7750 1600
NoConn ~ 7750 1200
NoConn ~ 8950 1600
NoConn ~ 8950 1200
$Comp
L power:GND #PWR018
U 1 1 5E6A8280
P 8000 4650
F 0 "#PWR018" H 8000 4400 50  0001 C CNN
F 1 "GND" H 8005 4477 50  0000 C CNN
F 2 "" H 8000 4650 50  0001 C CNN
F 3 "" H 8000 4650 50  0001 C CNN
	1    8000 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 4450 8000 4450
Wire Wire Line
	8000 4450 8000 4650
$Comp
L power:GND #PWR020
U 1 1 5E6A905A
P 9050 5950
F 0 "#PWR020" H 9050 5700 50  0001 C CNN
F 1 "GND" H 9055 5777 50  0000 C CNN
F 2 "" H 9050 5950 50  0001 C CNN
F 3 "" H 9050 5950 50  0001 C CNN
	1    9050 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 5750 8950 5950
Wire Wire Line
	8950 5950 9050 5950
Wire Wire Line
	9150 5950 9150 5750
Wire Wire Line
	9150 5950 9050 5950
Connection ~ 9050 5950
Wire Wire Line
	9050 5950 9050 5750
Text Label 8950 1300 0    50   ~ 0
SWDIO
Text Label 8950 1400 0    50   ~ 0
SWDCLK
Text Label 8950 1500 0    50   ~ 0
SWO
Text Label 8950 1700 0    50   ~ 0
NRST
Text Label 8950 1800 0    50   ~ 0
TX
Text Label 7750 1800 2    50   ~ 0
RX
Text Label 8550 5150 2    50   ~ 0
SWO
Text Label 9550 4250 0    50   ~ 0
TX
Text Label 9550 4350 0    50   ~ 0
RX
Text Label 9550 5450 0    50   ~ 0
SWDCLK
Text Label 8550 4050 2    50   ~ 0
NRST
Text Label 9550 5350 0    50   ~ 0
SWDIO
Text Label 9550 4850 0    50   ~ 0
CLKOUT
Text Label 9550 4450 0    50   ~ 0
sensor_pwr
Text Label 9550 4050 0    50   ~ 0
tsl237_freq
Text Label 8550 4650 2    50   ~ 0
oscillator
$Comp
L power:VCC #PWR019
U 1 1 5E6C4553
P 9050 3500
F 0 "#PWR019" H 9050 3350 50  0001 C CNN
F 1 "VCC" H 9065 3673 50  0000 C CNN
F 2 "" H 9050 3500 50  0001 C CNN
F 3 "" H 9050 3500 50  0001 C CNN
	1    9050 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 3500 9150 3500
Wire Wire Line
	9150 3500 9150 3850
Wire Wire Line
	9050 3500 8950 3500
Wire Wire Line
	8950 3500 8950 3850
Connection ~ 9050 3500
Wire Wire Line
	9050 3500 9050 3850
NoConn ~ 8550 4750
NoConn ~ 8550 4950
NoConn ~ 8550 5050
NoConn ~ 8550 5250
NoConn ~ 8550 5350
NoConn ~ 8550 5450
NoConn ~ 8550 5550
NoConn ~ 9550 5550
NoConn ~ 9550 5250
NoConn ~ 9550 5150
NoConn ~ 9550 5050
NoConn ~ 9550 4950
NoConn ~ 9550 4750
NoConn ~ 9550 4650
NoConn ~ 9550 4550
NoConn ~ 9550 4150
$Comp
L Connector:TestPoint TP3
U 1 1 5E82CCF8
P 10050 4850
F 0 "TP3" H 10108 4968 50  0000 L CNN
F 1 "TestPoint" H 10108 4877 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 10250 4850 50  0001 C CNN
F 3 "~" H 10250 4850 50  0001 C CNN
	1    10050 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 4850 9550 4850
$Comp
L Device:C C3
U 1 1 5E666610
P 7500 3700
F 0 "C3" H 7615 3746 50  0000 L CNN
F 1 "0.1uF" H 7615 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7538 3550 50  0001 C CNN
F 3 "~" H 7500 3700 50  0001 C CNN
	1    7500 3700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR014
U 1 1 5E666C77
P 7500 3350
F 0 "#PWR014" H 7500 3200 50  0001 C CNN
F 1 "VCC" H 7515 3523 50  0000 C CNN
F 2 "" H 7500 3350 50  0001 C CNN
F 3 "" H 7500 3350 50  0001 C CNN
	1    7500 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5E667339
P 7500 4100
F 0 "#PWR015" H 7500 3850 50  0001 C CNN
F 1 "GND" H 7505 3927 50  0000 C CNN
F 2 "" H 7500 4100 50  0001 C CNN
F 3 "" H 7500 4100 50  0001 C CNN
	1    7500 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3350 7500 3550
Wire Wire Line
	7500 3850 7500 4100
$Comp
L Device:C C4
U 1 1 5E6698E7
P 8000 3700
F 0 "C4" H 8115 3746 50  0000 L CNN
F 1 "1uF" H 8115 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8038 3550 50  0001 C CNN
F 3 "~" H 8000 3700 50  0001 C CNN
	1    8000 3700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR016
U 1 1 5E6698ED
P 8000 3350
F 0 "#PWR016" H 8000 3200 50  0001 C CNN
F 1 "VCC" H 8015 3523 50  0000 C CNN
F 2 "" H 8000 3350 50  0001 C CNN
F 3 "" H 8000 3350 50  0001 C CNN
	1    8000 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5E6698F3
P 8000 4100
F 0 "#PWR017" H 8000 3850 50  0001 C CNN
F 1 "GND" H 8005 3927 50  0000 C CNN
F 2 "" H 8000 4100 50  0001 C CNN
F 3 "" H 8000 4100 50  0001 C CNN
	1    8000 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3350 8000 3550
Wire Wire Line
	8000 3850 8000 4100
Wire Notes Line
	9250 2100 7350 2100
Wire Notes Line
	7350 650  9250 650 
Wire Notes Line
	7350 650  7350 2100
Wire Notes Line
	9250 650  9250 2100
Text Notes 7950 800  0    50   ~ 0
Debugger Interface
Wire Notes Line
	10550 3100 10550 6200
Wire Notes Line
	10550 6200 7350 6200
Wire Notes Line
	7350 6200 7350 3100
Wire Notes Line
	7350 3100 10550 3100
Text Notes 8750 3200 0    50   ~ 0
Processor Core
$Comp
L e314_light_sensor-rescue:TG-3541CE-e314_parts U1
U 1 1 5E86301E
P 2300 1950
F 0 "U1" H 2275 2375 50  0000 C CNN
F 1 "TG-3541CE" H 2275 2284 50  0000 C CNN
F 2 "e314_parts:TG-3541CE" H 2300 2250 50  0001 C CNN
F 3 "" H 2300 2250 50  0001 C CNN
	1    2300 1950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E86937A
P 2250 2500
F 0 "#PWR06" H 2250 2250 50  0001 C CNN
F 1 "GND" H 2255 2327 50  0000 C CNN
F 2 "" H 2250 2500 50  0001 C CNN
F 3 "" H 2250 2500 50  0001 C CNN
	1    2250 2500
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 5E8698B9
P 900 2050
F 0 "TP1" H 958 2168 50  0000 L CNN
F 1 "TestPoint" H 958 2077 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 1100 2050 50  0001 C CNN
F 3 "~" H 1100 2050 50  0001 C CNN
	1    900  2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1550 1350 1750
Wire Wire Line
	1350 1950 1800 1950
Wire Wire Line
	1800 1850 1350 1850
Connection ~ 1350 1850
Wire Wire Line
	1350 1850 1350 1950
Wire Wire Line
	1350 1750 1800 1750
Connection ~ 1350 1750
Wire Wire Line
	1350 1750 1350 1850
Wire Wire Line
	1800 2150 1800 2450
Wire Wire Line
	1800 2450 2250 2450
Wire Wire Line
	3000 2450 3000 2050
Wire Wire Line
	3000 1850 2750 1850
Wire Wire Line
	2750 1950 3000 1950
Connection ~ 3000 1950
Wire Wire Line
	3000 1950 3000 1850
Wire Wire Line
	2750 2050 3000 2050
Connection ~ 3000 2050
Wire Wire Line
	3000 2050 3000 1950
Wire Wire Line
	2250 2500 2250 2450
Connection ~ 2250 2450
Wire Wire Line
	2250 2450 3000 2450
Text Label 1800 2050 2    50   ~ 0
oscillator
Wire Wire Line
	900  2050 1800 2050
$Comp
L Device:C C1
U 1 1 5E87DA6C
P 1550 2600
F 0 "C1" H 1665 2646 50  0000 L CNN
F 1 "0.1uF" H 1665 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 1588 2450 50  0001 C CNN
F 3 "~" H 1550 2600 50  0001 C CNN
	1    1550 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5E87DA78
P 1550 2850
F 0 "#PWR03" H 1550 2600 50  0001 C CNN
F 1 "GND" H 1555 2677 50  0000 C CNN
F 2 "" H 1550 2850 50  0001 C CNN
F 3 "" H 1550 2850 50  0001 C CNN
	1    1550 2850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR02
U 1 1 5E87DA72
P 1550 2350
F 0 "#PWR02" H 1550 2200 50  0001 C CNN
F 1 "VCC" H 1565 2523 50  0000 C CNN
F 2 "" H 1550 2350 50  0001 C CNN
F 3 "" H 1550 2350 50  0001 C CNN
	1    1550 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 2350 1550 2450
Wire Wire Line
	1550 2750 1550 2850
Wire Notes Line
	850  3050 3050 3050
Wire Notes Line
	3050 3050 3050 1250
Wire Notes Line
	3050 1250 850  1250
Wire Notes Line
	850  3050 850  1250
Text Notes 1550 1350 0    50   ~ 0
32.768khz Oscillator
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5E89649A
P 1500 3900
F 0 "J1" H 1608 4181 50  0000 C CNN
F 1 "Conn_01x04_Male" H 1608 4090 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B4B-XH-AM_1x04_P2.50mm_Vertical" H 1500 3900 50  0001 C CNN
F 3 "~" H 1500 3900 50  0001 C CNN
	1    1500 3900
	1    0    0    -1  
$EndComp
NoConn ~ 1700 4000
NoConn ~ 1700 3800
Wire Wire Line
	2000 4100 2000 4250
$Comp
L power:GND #PWR04
U 1 1 5E89A1EC
P 2000 4250
F 0 "#PWR04" H 2000 4000 50  0001 C CNN
F 1 "GND" H 2005 4077 50  0000 C CNN
F 2 "" H 2000 4250 50  0001 C CNN
F 3 "" H 2000 4250 50  0001 C CNN
	1    2000 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 3900 2200 3900
Wire Wire Line
	2200 3900 2200 4650
Wire Wire Line
	1700 4100 2000 4100
$Comp
L Device:Battery_Cell BT1
U 1 1 5E8A43C8
P 2200 5550
F 0 "BT1" H 2318 5646 50  0000 L CNN
F 1 "Battery_Cell" H 2318 5555 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_1060_1x2032" V 2200 5610 50  0001 C CNN
F 3 "~" V 2200 5610 50  0001 C CNN
	1    2200 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5E8A508D
P 2200 6000
F 0 "#PWR05" H 2200 5750 50  0001 C CNN
F 1 "GND" H 2205 5827 50  0000 C CNN
F 2 "" H 2200 6000 50  0001 C CNN
F 3 "" H 2200 6000 50  0001 C CNN
	1    2200 6000
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5E8A5643
P 1750 5800
F 0 "#FLG01" H 1750 5875 50  0001 C CNN
F 1 "PWR_FLAG" H 1750 5973 50  0000 C CNN
F 2 "" H 1750 5800 50  0001 C CNN
F 3 "~" H 1750 5800 50  0001 C CNN
	1    1750 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6000 2200 5900
Wire Wire Line
	1750 5800 1750 5900
Wire Wire Line
	1750 5900 2200 5900
Connection ~ 2200 5900
Wire Wire Line
	2200 5900 2200 5650
Wire Wire Line
	2200 5350 2200 5150
$Comp
L Jumper:Jumper_3_Open JP1
U 1 1 5E89CECA
P 2200 4900
F 0 "JP1" V 2246 4987 50  0000 L CNN
F 1 "Jumper_3_Open" V 2155 4987 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm" H 2200 4900 50  0001 C CNN
F 3 "~" H 2200 4900 50  0001 C CNN
	1    2200 4900
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5E8B0CD5
P 2700 5050
F 0 "#FLG02" H 2700 5125 50  0001 C CNN
F 1 "PWR_FLAG" H 2700 5223 50  0000 C CNN
F 2 "" H 2700 5050 50  0001 C CNN
F 3 "~" H 2700 5050 50  0001 C CNN
	1    2700 5050
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 4900 2700 4900
Wire Wire Line
	2700 4900 2700 5050
Wire Notes Line
	2900 3450 2900 6250
Wire Notes Line
	2900 6250 1250 6250
Wire Notes Line
	1250 6250 1250 3450
Wire Notes Line
	1250 3450 2900 3450
Text Notes 1850 3550 0    50   ~ 0
Power Input
$Comp
L e314_light_sensor-rescue:TSL237S-LF-e314_parts IC1
U 1 1 5E8CC1D2
P 4500 4850
F 0 "IC1" H 5000 5115 50  0000 C CNN
F 1 "TSL237S-LF" H 5000 5024 50  0000 C CNN
F 2 "e314_parts:TSL237S-LF" H 5350 4950 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/TSL237S-LF.pdf" H 5350 4850 50  0001 L CNN
F 4 "Light To Frequency & Light To Voltage Light to Frequency High Responsivity" H 5350 4750 50  0001 L CNN "Description"
F 5 "856-TSL237S-LF" H 5350 4550 50  0001 L CNN "Mouser Part Number"
F 6 "https://www.mouser.com/Search/Refine.aspx?Keyword=856-TSL237S-LF" H 5350 4450 50  0001 L CNN "Mouser Price/Stock"
F 7 "ams" H 5350 4350 50  0001 L CNN "Manufacturer_Name"
F 8 "TSL237S-LF" H 5350 4250 50  0001 L CNN "Manufacturer_Part_Number"
	1    4500 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E8D5149
P 4200 4300
F 0 "C2" H 4315 4346 50  0000 L CNN
F 1 "1uF" H 4315 4255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4238 4150 50  0001 C CNN
F 3 "~" H 4200 4300 50  0001 C CNN
	1    4200 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E8D514F
P 4200 4550
F 0 "#PWR010" H 4200 4300 50  0001 C CNN
F 1 "GND" H 4205 4377 50  0000 C CNN
F 2 "" H 4200 4550 50  0001 C CNN
F 3 "" H 4200 4550 50  0001 C CNN
	1    4200 4550
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR09
U 1 1 5E8D5155
P 4200 4050
F 0 "#PWR09" H 4200 3900 50  0001 C CNN
F 1 "VCC" H 4215 4223 50  0000 C CNN
F 2 "" H 4200 4050 50  0001 C CNN
F 3 "" H 4200 4050 50  0001 C CNN
	1    4200 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4050 4200 4150
Wire Wire Line
	4200 4450 4200 4550
$Comp
L power:GND #PWR08
U 1 1 5E8D6670
P 3900 5150
F 0 "#PWR08" H 3900 4900 50  0001 C CNN
F 1 "GND" H 3905 4977 50  0000 C CNN
F 2 "" H 3900 5150 50  0001 C CNN
F 3 "" H 3900 5150 50  0001 C CNN
	1    3900 5150
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 5E8D6CDF
P 5700 4650
F 0 "TP2" H 5758 4768 50  0000 L CNN
F 1 "TestPoint" H 5758 4677 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 5900 4650 50  0001 C CNN
F 3 "~" H 5900 4650 50  0001 C CNN
	1    5700 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 4850 3900 4850
Wire Wire Line
	3900 4850 3900 5150
Wire Wire Line
	5500 4850 5700 4850
Wire Wire Line
	5700 4850 5700 4650
Text Label 4500 4950 2    50   ~ 0
sensor_pwr
Text Label 6050 4850 0    50   ~ 0
tsl237_freq
Wire Wire Line
	5700 4850 6050 4850
Connection ~ 5700 4850
Wire Notes Line
	3800 3750 3800 5400
Wire Notes Line
	3800 5400 6550 5400
Wire Notes Line
	6550 5400 6550 3750
Wire Notes Line
	3800 3750 6550 3750
Text Notes 4850 3900 0    50   ~ 0
Light Sensor
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5E84A133
P 4350 2750
F 0 "J2" H 4350 2450 50  0000 C CNN
F 1 "Conn_01x03" H 4268 2516 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B3B-XH-AM_1x03_P2.50mm_Vertical" H 4350 2750 50  0001 C CNN
F 3 "~" H 4350 2750 50  0001 C CNN
	1    4350 2750
	-1   0    0    1   
$EndComp
Wire Wire Line
	4550 2650 4900 2650
Wire Wire Line
	4550 2750 4900 2750
Wire Wire Line
	4550 2850 4900 2850
Wire Wire Line
	4900 2850 4900 2950
$Comp
L power:GND #PWR011
U 1 1 5E851110
P 4900 2950
F 0 "#PWR011" H 4900 2700 50  0001 C CNN
F 1 "GND" H 4905 2777 50  0000 C CNN
F 2 "" H 4900 2950 50  0001 C CNN
F 3 "" H 4900 2950 50  0001 C CNN
	1    4900 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R1
U 1 1 5E851D02
P 5000 2650
F 0 "R1" V 4900 2650 50  0000 C CNN
F 1 "200" V 4900 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5000 2650 50  0001 C CNN
F 3 "~" H 5000 2650 50  0001 C CNN
	1    5000 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R2
U 1 1 5E8527B8
P 5000 2750
F 0 "R2" V 5100 2750 50  0000 C CNN
F 1 "200" V 5100 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5000 2750 50  0001 C CNN
F 3 "~" H 5000 2750 50  0001 C CNN
	1    5000 2750
	0    1    1    0   
$EndComp
Text Label 5100 2650 0    50   ~ 0
TX
Text Label 5100 2750 0    50   ~ 0
RX
Wire Notes Line
	4200 2300 4200 3200
Wire Notes Line
	4200 3200 5250 3200
Wire Notes Line
	5250 3200 5250 2300
Wire Notes Line
	5250 2300 4200 2300
Text Notes 4400 2400 0    50   ~ 0
LPUART Connector
$Comp
L Mechanical:MountingHole H2
U 1 1 5E85C9CB
P 4750 1300
F 0 "H2" H 4850 1346 50  0000 L CNN
F 1 "MountingHole" H 4850 1255 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 4750 1300 50  0001 C CNN
F 3 "~" H 4750 1300 50  0001 C CNN
	1    4750 1300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5E85D041
P 5200 1650
F 0 "H4" H 5300 1696 50  0000 L CNN
F 1 "MountingHole" H 5300 1605 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 5200 1650 50  0001 C CNN
F 3 "~" H 5200 1650 50  0001 C CNN
	1    5200 1650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5E85D4E6
P 4750 2050
F 0 "H3" H 4850 2096 50  0000 L CNN
F 1 "MountingHole" H 4850 2005 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 4750 2050 50  0001 C CNN
F 3 "~" H 4750 2050 50  0001 C CNN
	1    4750 2050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5E85D7F6
P 4300 1650
F 0 "H1" H 4400 1696 50  0000 L CNN
F 1 "MountingHole" H 4400 1605 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 4300 1650 50  0001 C CNN
F 3 "~" H 4300 1650 50  0001 C CNN
	1    4300 1650
	1    0    0    -1  
$EndComp
Wire Notes Line
	4200 1050 4200 2150
Wire Notes Line
	4200 2150 5850 2150
Wire Notes Line
	5850 2150 5850 1050
Wire Notes Line
	5850 1050 4200 1050
Text Notes 4800 1150 0    50   ~ 0
Mounting
$Comp
L power:VCC #PWR0101
U 1 1 5E946803
P 1350 1550
F 0 "#PWR0101" H 1350 1400 50  0001 C CNN
F 1 "VCC" H 1367 1723 50  0000 C CNN
F 2 "" H 1350 1550 50  0001 C CNN
F 3 "" H 1350 1550 50  0001 C CNN
	1    1350 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 4700 2700 4900
$Comp
L power:VCC #PWR?
U 1 1 5E94D5E5
P 2700 4700
F 0 "#PWR?" H 2700 4550 50  0001 C CNN
F 1 "VCC" H 2717 4873 50  0000 C CNN
F 2 "" H 2700 4700 50  0001 C CNN
F 3 "" H 2700 4700 50  0001 C CNN
	1    2700 4700
	1    0    0    -1  
$EndComp
Connection ~ 2700 4900
$EndSCHEMATC