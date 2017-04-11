EESchema Schematic File Version 2
LIBS:RELogger_PCB_v1-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:1wire
LIBS:arduino_shieldsNCL
LIBS:atmel-1
LIBS:atmel-2005
LIBS:philips
LIBS:nxp
LIBS:matts_components
LIBS:linear2
LIBS:RELogger_PCB_v1-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
Title "RE-Logger v1"
Date "2016-08-14"
Rev "3"
Comp "Renewable Energy Innovation"
Comment1 "by Matt Little"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	6300 3800 6300 3650
Wire Wire Line
	3200 3300 4300 3300
Wire Wire Line
	6000 2950 6850 2950
Wire Wire Line
	6150 3050 6850 3050
Wire Wire Line
	6000 3250 6850 3250
Wire Wire Line
	3200 3900 4400 3900
Wire Wire Line
	5700 3150 6850 3150
Wire Wire Line
	5700 3150 5700 3900
Wire Wire Line
	3200 3600 6200 3600
Wire Wire Line
	6200 3600 6200 3350
Wire Wire Line
	6200 3350 6850 3350
Wire Wire Line
	3200 3000 4150 3000
Wire Wire Line
	6050 3650 6850 3650
NoConn ~ 6850 3950
NoConn ~ 6850 3850
NoConn ~ 6850 3750
NoConn ~ 6850 3450
NoConn ~ 6850 3550
$Comp
L R-RESCUE-RELogger_PCB_v1 R8
U 1 1 546255DF
P 6300 4050
F 0 "R8" V 6380 4050 50  0000 C CNN
F 1 "10k" V 6300 4050 50  0000 C CNN
F 2 "" H 6300 4050 60  0001 C CNN
F 3 "" H 6300 4050 60  0001 C CNN
	1    6300 4050
	1    0    0    -1  
$EndComp
$Comp
L CON-SD-MMC-3 J1
U 1 1 54625627
P 7150 3350
F 0 "J1" H 7000 4080 50  0000 L BNN
F 1 "CON-SD-MMC-3" H 7100 2550 50  0000 L BNN
F 2 "m-pad-2.1-DM1AA-SF-PEJ(21)" H 7150 3500 50  0001 C CNN
F 3 "" H 7150 3350 60  0001 C CNN
	1    7150 3350
	1    0    0    -1  
$EndComp
Text HLabel 3200 3000 0    60   Input ~ 0
D10
Text HLabel 3200 3300 0    60   Input ~ 0
D11
Text HLabel 3200 3600 0    60   Input ~ 0
D12
Text HLabel 3200 3900 0    60   Input ~ 0
D13
Text HLabel 3150 2250 0    60   Input ~ 0
3V3
Wire Wire Line
	6150 1750 6150 3050
Text HLabel 3150 4250 0    60   Output ~ 0
CD
$Comp
L 4050 U1
U 1 1 546524B9
P 4850 2100
F 0 "U1" H 5045 2215 60  0000 C CNN
F 1 "4050" H 5040 1975 60  0000 C CNN
F 2 "" H 4850 2100 60  0000 C CNN
F 3 "" H 4850 2100 60  0000 C CNN
	1    4850 2100
	1    0    0    -1  
$EndComp
$Comp
L 4050 U1
U 2 1 546524C8
P 4850 2600
F 0 "U1" H 5045 2715 60  0000 C CNN
F 1 "4050" H 5040 2475 60  0000 C CNN
F 2 "" H 4850 2600 60  0000 C CNN
F 3 "" H 4850 2600 60  0000 C CNN
	2    4850 2600
	1    0    0    -1  
$EndComp
$Comp
L 4050 U1
U 3 1 546524D7
P 4850 3900
F 0 "U1" H 5045 4015 60  0000 C CNN
F 1 "4050" H 5040 3775 60  0000 C CNN
F 2 "" H 4850 3900 60  0000 C CNN
F 3 "" H 4850 3900 60  0000 C CNN
	3    4850 3900
	1    0    0    -1  
$EndComp
$Comp
L 4050 U1
U 4 1 546524F0
P 4850 4550
F 0 "U1" H 5045 4665 60  0000 C CNN
F 1 "4050" H 5040 4425 60  0000 C CNN
F 2 "" H 4850 4550 60  0000 C CNN
F 3 "" H 4850 4550 60  0000 C CNN
	4    4850 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2750 6850 2750
Wire Wire Line
	5950 2750 5950 2100
Wire Wire Line
	5950 2100 5300 2100
Wire Wire Line
	4150 3000 4150 2100
Wire Wire Line
	4150 2100 4400 2100
Wire Wire Line
	5700 2850 6850 2850
Wire Wire Line
	5700 2850 5700 2600
Wire Wire Line
	5700 2600 5300 2600
Wire Wire Line
	4300 3300 4300 2600
Wire Wire Line
	4300 2600 4400 2600
Wire Wire Line
	5700 3900 5300 3900
Wire Wire Line
	6150 1750 3600 1750
Wire Wire Line
	3600 1750 3600 2250
Wire Wire Line
	3600 2250 3150 2250
Wire Wire Line
	3150 4250 6050 4250
Wire Wire Line
	6050 4250 6050 3650
Connection ~ 6300 3650
Wire Wire Line
	6300 4800 6300 4300
Wire Wire Line
	4800 2350 4800 2200
Wire Wire Line
	4800 2000 4800 1750
Connection ~ 4800 1750
NoConn ~ 4400 4550
NoConn ~ 5300 4550
Text HLabel 3150 4800 0    60   Input ~ 0
Vss
Wire Wire Line
	3150 4800 6300 4800
Text HLabel 6000 2950 0    60   Input ~ 0
GND
Text HLabel 6000 3250 0    60   Input ~ 0
GND
Text HLabel 4550 2350 0    60   Input ~ 0
GND
Wire Wire Line
	4550 2350 4800 2350
$EndSCHEMATC
