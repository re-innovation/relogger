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
Sheet 7 7
Title "RE-Logger v1"
Date "2016-08-14"
Rev "3"
Comp "Renewable Energy Innovation"
Comment1 "by Matt Little"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 5250 2300 0    60   Input ~ 0
Vss
Text HLabel 3100 3800 0    60   Input ~ 0
GND
Text HLabel 7450 3250 2    60   Output ~ 0
Freq_OUT
Text HLabel 7450 3800 2    60   Output ~ 0
GND_OUT
Text HLabel 7450 2300 2    60   Output ~ 0
Vss_OUT
Text HLabel 3100 2950 0    60   Input ~ 0
Hall_In
$Comp
L LM393 U6
U 1 1 57B16972
P 6700 3250
F 0 "U6" H 6850 3400 50  0000 C CNN
F 1 "LM393" H 6950 3100 50  0000 C CNN
F 2 "REInnovationFootprint:DIP-8_300_ELL" H 6700 3250 50  0001 C CNN
F 3 "http://docs-europe.electrocomponents.com/webdocs/13e4/0900766b813e452a.pdf" H 6700 3250 50  0001 C CNN
F 4 "~" H 6700 3250 60  0000 C CNN "Notes"
F 5 "Op Amp" H 6700 3250 60  0001 C CNN "Description"
F 6 "ON Semi" H 6700 3250 60  0001 C CNN "Manufacturer"
F 7 "LM393NG" H 6700 3250 60  0001 C CNN "Manufacturer Part No"
F 8 "RS" H 6700 3250 60  0001 C CNN "Supplier 1"
F 9 "463-870" H 6700 3250 60  0001 C CNN "Supplier 1 Part No"
F 10 "0.25" H 6700 3250 60  0001 C CNN "Supplier 1 Cost"
F 11 "~" H 6700 3250 60  0001 C CNN "Supplier 2"
F 12 "~" H 6700 3250 60  0001 C CNN "Supplier 2 Part No"
F 13 "~" H 6700 3250 60  0001 C CNN "Supplier 2 Cost"
	1    6700 3250
	1    0    0    -1  
$EndComp
$Comp
L LM393 U6
U 2 1 57B169C5
P 6700 4350
F 0 "U6" H 6850 4500 50  0000 C CNN
F 1 "LM393" H 6950 4200 50  0000 C CNN
F 2 "REInnovationFootprint:DIP-8_300_ELL" H 6700 4350 50  0001 C CNN
F 3 "" H 6700 4350 50  0000 C CNN
F 4 "~" H 6700 4350 60  0001 C CNN "Description"
F 5 "~" H 6700 4350 60  0001 C CNN "Notes"
F 6 "~" H 6700 4350 60  0001 C CNN "Manufacturer"
F 7 "~" H 6700 4350 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6700 4350 60  0001 C CNN "Supplier 1"
F 9 "~" H 6700 4350 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6700 4350 60  0001 C CNN "Supplier 2"
F 11 "~" H 6700 4350 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6700 4350 60  0001 C CNN "Cost"
	2    6700 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3800 7450 3800
Wire Wire Line
	6600 3800 6600 3550
Wire Wire Line
	6600 4950 6600 4650
Wire Wire Line
	4400 4950 6600 4950
Wire Wire Line
	5850 4950 5850 3800
Connection ~ 5850 3800
Wire Wire Line
	5250 2300 7450 2300
Wire Wire Line
	6600 2300 6600 2950
Wire Wire Line
	6600 4050 6600 3950
Wire Wire Line
	6600 3950 6200 3950
Wire Wire Line
	6200 3950 6200 2300
Connection ~ 6200 2300
Connection ~ 6600 3800
Connection ~ 6600 2300
Wire Wire Line
	7000 3250 7450 3250
$Comp
L ZENER-RESCUE-RELogger_PCB_v1 D16
U 1 1 57B7AFA3
P 4800 3400
F 0 "D16" H 4800 3500 50  0000 C CNN
F 1 "5V1" H 4800 3300 50  0000 C CNN
F 2 "REInnovationFootprint:TH_Diode_1" H 4800 3400 50  0001 C CNN
F 3 "" H 4800 3400 50  0000 C CNN
	1    4800 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 2950 4800 3200
Connection ~ 4800 2950
Wire Wire Line
	4800 3800 4800 3600
Connection ~ 4800 3800
Text HLabel 1450 4250 0    60   Input ~ 0
Freq_IN
Text HLabel 7500 4350 2    60   Output ~ 0
Freq_OUT2
$Comp
L C C4
U 1 1 595F852C
P 4400 4600
F 0 "C4" H 4425 4700 50  0000 L CNN
F 1 "C" H 4425 4500 50  0000 L CNN
F 2 "" H 4438 4450 50  0000 C CNN
F 3 "" H 4400 4600 50  0000 C CNN
	1    4400 4600
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 595F8479
P 4150 3350
F 0 "C3" H 4175 3450 50  0000 L CNN
F 1 "C" H 4175 3250 50  0000 L CNN
F 2 "" H 4188 3200 50  0000 C CNN
F 3 "" H 4150 3350 50  0000 C CNN
	1    4150 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4950 4400 4750
Connection ~ 5850 4950
Wire Wire Line
	3700 2950 6300 2950
$Comp
L R R13
U 1 1 595F88DC
P 3550 2950
F 0 "R13" V 3630 2950 50  0000 C CNN
F 1 "R" V 3550 2950 50  0000 C CNN
F 2 "" V 3480 2950 50  0000 C CNN
F 3 "" H 3550 2950 50  0000 C CNN
	1    3550 2950
	0    1    1    0   
$EndComp
$Comp
L R R12
U 1 1 595F8926
P 3500 4250
F 0 "R12" V 3580 4250 50  0000 C CNN
F 1 "R" V 3500 4250 50  0000 C CNN
F 2 "" V 3430 4250 50  0000 C CNN
F 3 "" H 3500 4250 50  0000 C CNN
	1    3500 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 3200 4150 2950
Connection ~ 4150 2950
Wire Wire Line
	4150 3500 4150 3800
Connection ~ 4150 3800
Wire Wire Line
	3100 2950 3400 2950
$Comp
L R R11
U 1 1 595F8B10
P 3250 2600
F 0 "R11" V 3330 2600 50  0000 C CNN
F 1 "10k" V 3250 2600 50  0000 C CNN
F 2 "" V 3180 2600 50  0000 C CNN
F 3 "" H 3250 2600 50  0000 C CNN
	1    3250 2600
	-1   0    0    1   
$EndComp
Text HLabel 3200 2300 0    60   Input ~ 0
Vss
Wire Wire Line
	3200 2300 3250 2300
Wire Wire Line
	3250 2300 3250 2450
Wire Wire Line
	3250 2750 3250 2950
Connection ~ 3250 2950
Text Notes 3350 2650 0    60   ~ 0
Pull Up\nFor Switch ONLY
$Comp
L R R10
U 1 1 595F8CBD
P 1750 4050
F 0 "R10" V 1830 4050 50  0000 C CNN
F 1 "10k" V 1750 4050 50  0000 C CNN
F 2 "" V 1680 4050 50  0000 C CNN
F 3 "" H 1750 4050 50  0000 C CNN
	1    1750 4050
	-1   0    0    1   
$EndComp
Text HLabel 1700 3750 0    60   Input ~ 0
Vss
Wire Wire Line
	1700 3750 1750 3750
Wire Wire Line
	1750 3750 1750 3900
Text Notes 1850 4100 0    60   ~ 0
Pull Up\nFor Switch ONLY
Wire Wire Line
	1450 4250 3350 4250
Wire Wire Line
	1750 4200 1750 4250
Connection ~ 1750 4250
Wire Wire Line
	3650 4250 6100 4250
Wire Wire Line
	6100 4250 6100 4450
Wire Wire Line
	6100 4450 6400 4450
Wire Wire Line
	4400 4450 4400 4250
Connection ~ 4400 4250
Wire Wire Line
	6300 2950 6300 3350
Wire Wire Line
	6300 3350 6400 3350
$Comp
L R R21
U 1 1 595F95C2
P 6950 2750
F 0 "R21" V 7030 2750 50  0000 C CNN
F 1 "100k" V 6950 2750 50  0000 C CNN
F 2 "" V 6880 2750 50  0000 C CNN
F 3 "" H 6950 2750 50  0000 C CNN
	1    6950 2750
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 595F96E6
P 6000 3400
F 0 "R14" V 6080 3400 50  0000 C CNN
F 1 "1k" V 6000 3400 50  0000 C CNN
F 2 "" V 5930 3400 50  0000 C CNN
F 3 "" H 6000 3400 50  0000 C CNN
F 4 "~" H 6000 3400 60  0001 C CNN "Description"
F 5 "~" H 6000 3400 60  0001 C CNN "Notes"
F 6 "~" H 6000 3400 60  0001 C CNN "Manufacturer"
F 7 "~" H 6000 3400 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6000 3400 60  0001 C CNN "Supplier 1"
F 9 "~" H 6000 3400 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6000 3400 60  0001 C CNN "Supplier 2"
F 11 "~" H 6000 3400 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6000 3400 60  0001 C CNN "Cost"
	1    6000 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 3150 6000 3150
Wire Wire Line
	6000 2750 6000 3250
Wire Wire Line
	6000 2750 6800 2750
Connection ~ 6000 3150
Wire Wire Line
	7100 2750 7150 2750
Wire Wire Line
	7150 2750 7150 3250
Connection ~ 7150 3250
Wire Wire Line
	6000 3550 6000 3800
Connection ~ 6000 3800
$Comp
L R R15
U 1 1 595F9B2D
P 6000 4600
F 0 "R15" V 6080 4600 50  0000 C CNN
F 1 "1k" V 6000 4600 50  0000 C CNN
F 2 "" V 5930 4600 50  0000 C CNN
F 3 "" H 6000 4600 50  0000 C CNN
F 4 "~" H 6000 4600 60  0001 C CNN "Description"
F 5 "~" H 6000 4600 60  0001 C CNN "Notes"
F 6 "~" H 6000 4600 60  0001 C CNN "Manufacturer"
F 7 "~" H 6000 4600 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6000 4600 60  0001 C CNN "Supplier 1"
F 9 "~" H 6000 4600 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6000 4600 60  0001 C CNN "Supplier 2"
F 11 "~" H 6000 4600 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6000 4600 60  0001 C CNN "Cost"
	1    6000 4600
	-1   0    0    1   
$EndComp
$Comp
L R R22
U 1 1 595F9BB8
P 6950 4000
F 0 "R22" V 7030 4000 50  0000 C CNN
F 1 "100k" V 6950 4000 50  0000 C CNN
F 2 "" V 6880 4000 50  0000 C CNN
F 3 "" H 6950 4000 50  0000 C CNN
	1    6950 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	7500 4350 7000 4350
Wire Wire Line
	7250 4350 7250 4000
Wire Wire Line
	7250 4000 7100 4000
Connection ~ 7250 4350
Wire Wire Line
	6800 4000 6000 4000
Wire Wire Line
	6000 4000 6000 4450
Wire Wire Line
	6000 4750 6000 4950
Connection ~ 6000 4950
Wire Wire Line
	6400 4250 6200 4250
Wire Wire Line
	6200 4250 6200 4000
Connection ~ 6200 4000
$EndSCHEMATC
