EESchema Schematic File Version 4
LIBS:TargetPractice-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L MCU_Module:Arduino_Nano_v3.x A?
U 1 1 5D040CB2
P 4700 4400
F 0 "A?" H 4700 3314 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" V 4700 4400 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 4850 3450 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 4700 3400 50  0001 C CNN
	1    4700 4400
	1    0    0    -1  
$EndComp
$Comp
L JacobSymbol:SevenSegmentDisplayI2C U?
U 1 1 5D042999
P 8050 4000
F 0 "U?" H 7623 3621 50  0000 R CNN
F 1 "SevenSegmentDisplayI2C" H 7623 3530 50  0000 R CNN
F 2 "" H 8050 4000 50  0001 C CNN
F 3 "" H 8050 4000 50  0001 C CNN
	1    8050 4000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5200 4800 6900 4800
Wire Wire Line
	6900 4800 6900 4100
Wire Wire Line
	6900 4100 7500 4100
Wire Wire Line
	7500 4200 7000 4200
Wire Wire Line
	7000 4200 7000 4900
Wire Wire Line
	7000 4900 5200 4900
Text Notes 7350 4100 0    50   ~ 0
SDA
Text Notes 7350 4200 0    50   ~ 0
SCL
Wire Wire Line
	4900 3400 4900 3200
Wire Wire Line
	6800 3200 6800 4450
Wire Wire Line
	6800 4450 7300 4450
Wire Wire Line
	4800 5400 4800 5500
Wire Wire Line
	7100 5500 7100 4550
Wire Wire Line
	7100 4550 7500 4550
Wire Wire Line
	7500 4750 7300 4750
Wire Wire Line
	7300 4750 7300 4450
Connection ~ 7300 4450
Wire Wire Line
	7300 4450 7500 4450
$Comp
L Switch:SW_SPST SW?
U 1 1 5D0430C4
P 3050 3000
F 0 "SW?" H 3050 3235 50  0000 C CNN
F 1 "SW_SPST" H 3050 3144 50  0000 C CNN
F 2 "" H 3050 3000 50  0001 C CNN
F 3 "" H 3050 3000 50  0001 C CNN
	1    3050 3000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW?
U 1 1 5D043164
P 2250 3500
F 0 "SW?" H 2250 3735 50  0000 C CNN
F 1 "SW_SPST" H 2250 3644 50  0000 C CNN
F 2 "" H 2250 3500 50  0001 C CNN
F 3 "" H 2250 3500 50  0001 C CNN
	1    2250 3500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW?
U 1 1 5D0431AE
P 1400 4200
F 0 "SW?" H 1400 4435 50  0000 C CNN
F 1 "SW_SPST" H 1400 4344 50  0000 C CNN
F 2 "" H 1400 4200 50  0001 C CNN
F 3 "" H 1400 4200 50  0001 C CNN
	1    1400 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4000 3250 4000
Wire Wire Line
	4200 4100 2450 4100
Wire Wire Line
	1600 4200 4200 4200
Wire Wire Line
	1200 5500 3300 5500
Connection ~ 1200 4200
Wire Wire Line
	1200 4200 1200 5500
Connection ~ 4800 5500
Wire Wire Line
	3250 4000 3250 3000
Wire Wire Line
	2450 4100 2450 3500
Wire Wire Line
	1200 3000 2850 3000
Wire Wire Line
	1200 3000 1200 3500
Wire Wire Line
	2050 3500 1200 3500
Connection ~ 1200 3500
Wire Wire Line
	1200 3500 1200 4200
Text Notes 2900 3150 0    50   ~ 0
Target 1
Text Notes 2100 3650 0    50   ~ 0
Target 2
Text Notes 1250 4350 0    50   ~ 0
Target 3
$Comp
L Device:Speaker LS?
U 1 1 5D044C84
P 3300 6700
F 0 "LS?" V 3218 6880 50  0000 L CNN
F 1 "Speaker" V 3309 6880 50  0000 L CNN
F 2 "" H 3300 6500 50  0001 C CNN
F 3 "~" H 3290 6650 50  0001 C CNN
	1    3300 6700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5D044D96
P 3200 6100
F 0 "R?" H 3000 6100 50  0000 L CNN
F 1 "R_Small_US" H 2650 6000 50  0000 L CNN
F 2 "" H 3200 6100 50  0001 C CNN
F 3 "~" H 3200 6100 50  0001 C CNN
	1    3200 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4600 3200 4600
Wire Wire Line
	3200 4600 3200 6000
Wire Wire Line
	3200 6200 3200 6500
Wire Wire Line
	3300 6500 3300 5500
Connection ~ 3300 5500
Wire Wire Line
	3300 5500 4800 5500
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U?
U 1 1 5D181C98
P 9650 2100
F 0 "U?" H 9400 2700 50  0000 R CNN
F 1 "ATtiny85-20PU" H 9550 2800 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9650 2100 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 9650 2100 50  0001 C CNN
	1    9650 2100
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:TIP41C Q?
U 1 1 5D181E15
P 10150 3650
F 0 "Q?" H 10340 3696 50  0000 L CNN
F 1 "TIP41C" H 10340 3605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 10400 3575 50  0001 L CIN
F 3 "https://www.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=tip41.PDF" H 10150 3650 50  0001 L CNN
	1    10150 3650
	-1   0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 5D183929
P 10550 2100
F 0 "BT?" H 10668 2196 50  0000 L CNN
F 1 "Battery_Cell" H 10668 2105 50  0000 L CNN
F 2 "" V 10550 2160 50  0001 C CNN
F 3 "~" V 10550 2160 50  0001 C CNN
	1    10550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 1900 10550 700 
Wire Wire Line
	10550 700  9650 700 
Wire Wire Line
	9650 700  9650 1200
Wire Wire Line
	10550 2200 10550 2800
Wire Wire Line
	10550 2800 9650 2800
Wire Wire Line
	9650 2800 9650 2700
$Comp
L Switch:SW_Push SW?
U 1 1 5D184BC7
P 8350 2900
F 0 "SW?" H 8100 2950 50  0000 C CNN
F 1 "SW_Push" H 8050 3050 50  0000 C CNN
F 2 "" H 8350 3100 50  0001 C CNN
F 3 "" H 8350 3100 50  0001 C CNN
	1    8350 2900
	0    1    1    0   
$EndComp
Text Notes 7800 2950 0    50   ~ 0
Reset Button
$Comp
L Device:R_Small_US R?
U 1 1 5D1860C0
P 9300 1200
F 0 "R?" V 9095 1200 50  0000 C CNN
F 1 "R_Small_US" V 9186 1200 50  0000 C CNN
F 2 "" H 9300 1200 50  0001 C CNN
F 3 "~" H 9300 1200 50  0001 C CNN
	1    9300 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	9650 1550 9650 1500
Wire Wire Line
	9650 1200 9400 1200
Wire Wire Line
	8350 1200 9200 1200
Wire Wire Line
	8350 1200 8350 2300
Wire Wire Line
	8350 2300 9050 2300
Connection ~ 9650 2800
Text Notes 9450 1050 0    50   ~ 0
10K Ohm
Connection ~ 9650 1200
Wire Wire Line
	9650 1200 9650 1500
Connection ~ 9650 1500
Connection ~ 9650 700 
$Comp
L Device:R_Small_US R?
U 1 1 5D1E5287
P 10450 3650
F 0 "R?" V 10245 3650 50  0000 C CNN
F 1 "R_Small_US" V 10336 3650 50  0000 C CNN
F 2 "" H 10450 3650 50  0001 C CNN
F 3 "~" H 10450 3650 50  0001 C CNN
	1    10450 3650
	0    1    1    0   
$EndComp
Text Notes 10300 3400 0    50   ~ 0
1K Ohm
Wire Wire Line
	4800 5500 7100 5500
Wire Wire Line
	4900 3200 6800 3200
Wire Wire Line
	4900 3200 4900 700 
Wire Wire Line
	4900 700  9650 700 
Connection ~ 4900 3200
Wire Wire Line
	9050 1900 8850 1900
Wire Wire Line
	8850 1900 8850 3200
Wire Wire Line
	8850 3200 10800 3200
Wire Wire Line
	10800 3200 10800 3650
Wire Wire Line
	10800 3650 10550 3650
Wire Wire Line
	10050 3850 10050 4100
Wire Wire Line
	10050 4100 11050 4100
Wire Wire Line
	11050 4100 11050 2800
Wire Wire Line
	11050 2800 10550 2800
Connection ~ 10550 2800
Wire Wire Line
	7100 5500 9600 5500
Wire Wire Line
	9600 5500 9600 3450
Wire Wire Line
	9600 3450 10050 3450
Connection ~ 7100 5500
Wire Wire Line
	8350 2300 8350 2700
Connection ~ 8350 2300
Wire Wire Line
	8350 3100 8700 3100
Wire Wire Line
	8700 3100 8700 2800
Wire Wire Line
	8700 2800 9650 2800
$EndSCHEMATC
