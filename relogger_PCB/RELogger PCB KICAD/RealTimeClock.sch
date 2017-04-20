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
Sheet 4 7
Title "RE-Logger v1"
Date "2016-08-14"
Rev "3"
Comp "Renewable Energy Innovation"
Comment1 "by Matt Little"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 5550 3450 0    60   Output ~ 0
D2/SQW
Text HLabel 5550 3150 0    60   Input ~ 0
+
Text HLabel 5550 3250 0    60   Input ~ 0
A4/SDA
Text HLabel 5550 3350 0    60   Input ~ 0
A5/SCL
Text HLabel 5550 3050 0    60   Input ~ 0
GND
$Comp
L CONN_01X06 J1
U 1 1 58F0FCFB
P 5950 3300
F 0 "J1" H 5950 3650 50  0000 C CNN
F 1 "RTC_MODULE" V 6050 3300 50  0000 C CNN
F 2 "REInnovationFootprint:TH_RTC_MODULE" H 5950 3300 50  0001 C CNN
F 3 "" H 5950 3300 50  0001 C CNN
	1    5950 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3050 5750 3050
Wire Wire Line
	5550 3150 5750 3150
Wire Wire Line
	5550 3250 5750 3250
Wire Wire Line
	5550 3350 5750 3350
Wire Wire Line
	5550 3450 5750 3450
NoConn ~ 5750 3550
$EndSCHEMATC
