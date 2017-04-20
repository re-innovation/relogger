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
$Comp
L CONN_01X06 J3
U 1 1 58F140FE
P 6000 3450
F 0 "J3" H 6000 3800 50  0000 C CNN
F 1 "MICRO_SD" V 6100 3450 50  0000 C CNN
F 2 "REInnovationFootprint:TH_SD_MODULE" H 6000 3450 50  0001 C CNN
F 3 "" H 6000 3450 50  0001 C CNN
	1    6000 3450
	1    0    0    -1  
$EndComp
Text HLabel 5450 3200 0    60   Input ~ 0
3V3
Text HLabel 5450 3400 0    60   Input ~ 0
D11
Text HLabel 5450 3300 0    60   Input ~ 0
D10
Text HLabel 5450 3500 0    60   Input ~ 0
D13
Text HLabel 5450 3600 0    60   Input ~ 0
D12
Text HLabel 5450 3850 3    60   Input ~ 0
GND
Text Label 5500 3300 0    60   ~ 0
SD_CS
Text Label 5500 3400 0    60   ~ 0
MOSI
Text Label 5500 3500 0    60   ~ 0
SCK
Text Label 5500 3600 0    60   ~ 0
MISO
Wire Wire Line
	5450 3200 5800 3200
Wire Wire Line
	5450 3300 5800 3300
Wire Wire Line
	5450 3400 5800 3400
Wire Wire Line
	5450 3500 5800 3500
Wire Wire Line
	5450 3600 5800 3600
Wire Wire Line
	5450 3700 5450 3850
Wire Wire Line
	5800 3700 5450 3700
$EndSCHEMATC
