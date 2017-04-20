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
Sheet 3 7
Title "RE-Logger v1"
Date "2016-08-14"
Rev "3"
Comp "Renewable Energy Innovation"
Comment1 "by Matt Little"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Arduino_Nano_Header J2
U 1 1 58F03BFB
P 5750 3200
F 0 "J2" H 5750 4000 60  0000 C CNN
F 1 "Arduino_Nano_Header" H 5750 2400 60  0000 C CNN
F 2 "REInnovationFootprint:NANO_DIP_30_600" H 5750 3200 60  0001 C CNN
F 3 "" H 5750 3200 60  0000 C CNN
	1    5750 3200
	1    0    0    -1  
$EndComp
Text HLabel 6400 3900 2    60   Input ~ 0
D13
Text HLabel 5100 3900 0    60   Input ~ 0
D12
Text HLabel 5100 3800 0    60   Input ~ 0
D11
Text HLabel 5100 3700 0    60   Input ~ 0
D10
Text HLabel 5100 3600 0    60   Input ~ 0
D9
Text HLabel 5100 3500 0    60   Input ~ 0
D8
Text HLabel 5100 3400 0    60   Input ~ 0
D7
Text HLabel 5100 3300 0    60   Input ~ 0
D6
Text HLabel 5100 3200 0    60   Input ~ 0
D5
Text HLabel 5100 3100 0    60   Input ~ 0
D4
Text HLabel 5100 3000 0    60   Input ~ 0
D3
Text HLabel 5100 2900 0    60   Input ~ 0
D2
Text HLabel 5100 2800 0    60   Input ~ 0
GND
Text HLabel 5100 2500 0    60   Input ~ 0
Tx/D1
Text HLabel 5100 2600 0    60   Input ~ 0
Rx/D0
Text HLabel 6400 2500 2    60   Input ~ 0
Vpower
Text HLabel 6400 2600 2    60   Input ~ 0
GND
Text HLabel 6400 3600 2    60   Input ~ 0
A0
Text HLabel 6400 3500 2    60   Input ~ 0
A1
Text HLabel 6400 3400 2    60   Input ~ 0
A2
Text HLabel 6400 3300 2    60   Input ~ 0
A3
Text HLabel 6400 3200 2    60   Input ~ 0
A4
Text HLabel 6400 3100 2    60   Input ~ 0
A5
Text HLabel 5100 2700 0    60   Input ~ 0
RESET
Text HLabel 6400 2700 2    60   Input ~ 0
RESET
Text HLabel 6400 3700 2    60   Input ~ 0
VREF
Text HLabel 6400 3800 2    60   Input ~ 0
3v3
Wire Wire Line
	5100 2500 5400 2500
Wire Wire Line
	5400 2600 5100 2600
Wire Wire Line
	5100 2700 5400 2700
Wire Wire Line
	5400 2800 5100 2800
Wire Wire Line
	5100 2900 5400 2900
Wire Wire Line
	5400 3000 5100 3000
Wire Wire Line
	5100 3100 5400 3100
Wire Wire Line
	5400 3200 5100 3200
Wire Wire Line
	5100 3300 5400 3300
Wire Wire Line
	5400 3400 5100 3400
Wire Wire Line
	5100 3500 5400 3500
Wire Wire Line
	5400 3600 5100 3600
Wire Wire Line
	5100 3700 5400 3700
Wire Wire Line
	5400 3800 5100 3800
Wire Wire Line
	5100 3900 5400 3900
Wire Wire Line
	6100 2500 6400 2500
Wire Wire Line
	6400 2600 6100 2600
Wire Wire Line
	6100 2700 6400 2700
Wire Wire Line
	6100 3100 6400 3100
Wire Wire Line
	6400 3200 6100 3200
Wire Wire Line
	6400 3300 6100 3300
Wire Wire Line
	6100 3400 6400 3400
Wire Wire Line
	6400 3500 6100 3500
Wire Wire Line
	6100 3600 6400 3600
Wire Wire Line
	6400 3700 6100 3700
Wire Wire Line
	6100 3800 6400 3800
Wire Wire Line
	6400 3900 6100 3900
Text HLabel 6400 3000 2    60   Input ~ 0
A6
Text HLabel 6400 2900 2    60   Input ~ 0
A7
Text HLabel 6400 2800 2    60   Input ~ 0
5v
Wire Wire Line
	6100 2800 6400 2800
Wire Wire Line
	6400 2900 6100 2900
Wire Wire Line
	6400 3000 6100 3000
$EndSCHEMATC
