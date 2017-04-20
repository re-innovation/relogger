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
Sheet 6 7
Title "RE-Logger v1"
Date "2016-08-14"
Rev "3"
Comp "Renewable Energy Innovation"
Comment1 "by Matt Little"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 7600 4100 2    60   Input ~ 0
GND
Text HLabel 4250 3250 0    60   Input ~ 0
AC_IN+
Text HLabel 7650 3900 2    60   Output ~ 0
Freq_OUT
Text HLabel 4300 4300 0    60   Input ~ 0
AC_IN-
$Comp
L FOD817ASD OPTO1
U 1 1 57B10CC2
P 5300 4000
F 0 "OPTO1" H 5112 4177 40  0000 C CNN
F 1 "VO615A" H 5450 3800 40  0000 C CNN
F 2 "REInnovationFootprint:DIP-4_300_ELL" H 5650 3750 29  0001 C CNN
F 3 "http://docs-europe.electrocomponents.com/webdocs/1196/0900766b81196e5a.pdf" H 5300 4000 60  0001 C CNN
F 4 "~" H 5300 4000 60  0000 C CNN "Notes"
F 5 "Opto-coupler" H 5300 4000 60  0001 C CNN "Description"
F 6 "Vishay" H 5300 4000 60  0001 C CNN "Manufacturer"
F 7 "VO615A-5" H 5300 4000 60  0001 C CNN "Manufacturer Part No"
F 8 "RS" H 5300 4000 60  0001 C CNN "Supplier 1"
F 9 "773-3693" H 5300 4000 60  0001 C CNN "Supplier 1 Part No"
F 10 "0.12" H 5300 4000 60  0001 C CNN "Supplier 1 Cost"
F 11 "~" H 5300 4000 60  0001 C CNN "Supplier 2"
F 12 "~" H 5300 4000 60  0001 C CNN "Supplier 2 Part No"
F 13 "~" H 5300 4000 60  0001 C CNN "Supplier 2 Cost"
	1    5300 4000
	1    0    0    -1  
$EndComp
$Comp
L R R19
U 1 1 57B10D47
P 4800 3650
F 0 "R19" V 4880 3650 50  0000 C CNN
F 1 "1k" V 4800 3650 50  0000 C CNN
F 2 "REInnovationFootprint:TH_Resistor_1" V 4730 3650 50  0001 C CNN
F 3 "" H 4800 3650 50  0000 C CNN
F 4 "~" H 4800 3650 60  0001 C CNN "Description"
F 5 "~" H 4800 3650 60  0001 C CNN "Notes"
F 6 "~" H 4800 3650 60  0001 C CNN "Manufacturer"
F 7 "~" H 4800 3650 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 4800 3650 60  0001 C CNN "Supplier 1"
F 9 "~" H 4800 3650 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 4800 3650 60  0001 C CNN "Supplier 2"
F 11 "~" H 4800 3650 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 4800 3650 60  0001 C CNN "Cost"
	1    4800 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3250 4800 3500
Wire Wire Line
	4950 3900 4800 3900
Wire Wire Line
	4800 3900 4800 3800
Wire Wire Line
	4950 4100 4800 4100
Wire Wire Line
	4800 4100 4800 4300
Wire Wire Line
	4800 4300 4300 4300
$Comp
L D D15
U 1 1 57B11038
P 4500 3250
F 0 "D15" H 4500 3350 50  0000 C CNN
F 1 "1N4001" H 4500 3150 50  0000 C CNN
F 2 "REInnovationFootprint:TH_Diode_1" H 4500 3250 50  0001 C CNN
F 3 "" H 4500 3250 50  0000 C CNN
	1    4500 3250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 3250 4800 3250
Wire Wire Line
	4350 3250 4250 3250
Text HLabel 7600 3300 2    60   Output ~ 0
Vss
$Comp
L R R20
U 1 1 57B1112A
P 5950 3500
F 0 "R20" V 6030 3500 50  0000 C CNN
F 1 "10k" V 5950 3500 50  0000 C CNN
F 2 "REInnovationFootprint:TH_Resistor_1" V 5880 3500 50  0001 C CNN
F 3 "" H 5950 3500 50  0000 C CNN
	1    5950 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3300 5950 3300
Wire Wire Line
	5950 3300 5950 3350
Wire Wire Line
	5650 3900 7650 3900
Wire Wire Line
	5950 3900 5950 3650
Wire Wire Line
	5650 4100 7600 4100
Connection ~ 5950 3900
$EndSCHEMATC
