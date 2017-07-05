  /********************************************************
  /****** RE Logger:  *************************************
  /****** by Matt Little **********************************
  /****** Date: 30/5/2017 *********************************
  /****** info@re-innovation.co.uk ************************
  /****** www.re-innovation.co.uk *************************
  /********************************************************

  See www.re-innovation.co.uk for information and construction details

  /*************Details of Code*****************************

  The RELogger is an Arduino nano based SD card datalogger.

  It measures:
  1 x Anemometer (hall effect or pulse)
  1 x wind vane
  1 x Hall effect current sensor (AC/DC)
  1 x External voltage
  1 x External AC signal as a rotation OR pulse type anemometer

  The pin assisgnments are as follows:
  D0 - Serial Rx
  D1 - Serial Tx
  D2 - Clock interrupt
  D3 - Anemometer - Pulses or hall effect to pulses
  D4 - AC frequency (rotational speed of generator)
  D5 - Switch A
  D6 - Switch B
  D7 - N/C
  D8 - Calibrate switch
  D9 - CS for ADC (SPI)
  D10 - CS for SD (SPI)
  D11 - MOSI (SPI) for SD and ADC
  D12 - MISO (SPI) for SD and ADC
  D13 - SCLOCK (SPI) for SD and ADC

  A0 - VBatt (local battery voltage)
  A1 - Tx_Software serial
  A2 - Rx Software serial
  A3 - LED WS2811 for data and error displaying
  A4 - I2C SDA (For OLED and RTC)
  A5 - I2C SCLK (For OLED and RTC)
  A6 - (nano only) External analog
  A7 - (nano only) External analog

  Each logger has a reference (user adjustable).

  Data is written to a .csv file created on an SD card.
  A new file is created each day. If file alreay present then data is appended.
  The file name is created from the reference number and the date in the format:
  DXXXXXX.csv, where DXXXXXX is the date in the format DDMMYY.


  Counts pulses from a sensor (such as a anemometer or flow sensor)
  These are pulses are averaged into a wind speed
  
  Each logger has a reference (user adjustable).
  
  Data is written to a .csv file created on an SD card.
  A new file is created each day. If file alreay present then data is appended.
  The file name is created from the reference number and the date in the format:
  DXXXXXX.csv, where DXXXXXX is the date in the format DDMMYY. 
  
  Data is stored with human readable headers:
  "Reference, Time, Date, Wind Pulses, Direction, Temp, Humidity"

  // This will be added to a seperate 'calibrate' mode
  When in Calibrate mode:
  You can adjust the parameters of the device using serial commands. These parameters are stored in EEPROM.
  These are:
  T??????E
  This will change the time to HHMMSS
  D??????E
  This will change the date to DDMMYY
  S?????E
  This will change the sample period to ????? seconds. Set to 00001 for 1 second data, set to 03600 for 1 hour data.
  The minimum is 1 second data. The maximum is 99999 seconds
  
  // Addedd Interrupt code from here:
  // PinChangeIntExample, version 1.1 Sun Jan 15 06:24:19 CST 2012
  // See the Wiki at http://code.google.com/p/arduino-pinchangeint/wiki 
  // for more information.
 
  Updates:
  30/5/17 Initial tesing of all functions
  30/5/17 WS2811 LED OK
  30/5/17 OLED I2C Works OK
  30/5/17 DS3210 RTC Works OK
  30/5/17 Clock Interrupt works OK
  20/6/17 SD Works OK
  20/6/17 Vane Works OK
  20/6/17 ADC Works OK 
   
  TO DO
  30/5/17 Opto Sensor Works OK
  30/5/17 Vext Works OK
  30/5/17 VBatt Works OK
  30/5/17 Hall effect Anemometer Works OK
  30/5/17 Anemometer Works OK
  30/5/17 Hall Effect I Works OK
  
    
  //********* OLED DETAILS*****************************
  Universal 8bit Graphics Library, https://github.com/olikraus/u8glib/
  Use this one: U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI
  OLED NOT USED!!

  //*********SD CARD DETAILS***************************
  The SD card circuit:
  SD card attached to SPI bus as follows:
  ** MOSI - pin 11
  ** MISO - pin 12
  ** CLK - pin 13
  ** CS - pin 10

  //************ Real Time Clock code*******************
  http://www.rinkydinkelectronics.com/library.php?id=73
  // DS3231_Serial_Easy
  // Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  // web: http://www.RinkyDinkElectronics.com/
  
 ** A4 - SDA (serial data)
 ** A5 - SDC (serial clock)
 ** D2 - Clock out - This gives a 1 second pulse to record the data

  //************ ADC MC3208 Library *********************************
  // https://github.com/labfruits/mcp3208

**********************************************************************************************************/


/************ External Libraries*****************************/

#include <Adafruit_NeoPixel.h>
#include <stdlib.h>

#include <SdFat.h>            // SD card library
#include <avr/pgmspace.h>  // Library for putting data into program memory
#include <EEPROM.h>        // For writing values to the EEPROM
#include <avr/sleep.h>
#include <avr/power.h>
#include <PinChangeInt.h>  // For additional interrupts
#include <DS3231.h>     // For the RTC
#include <Mcp3208.h>    // For the ADC
#include <SPI.h>
/************User variables and hardware allocation**********************************************/

/******* SD CARD*************/
#define SD_CS 10 // The SD card Chip Select pin 10

// SD file system object
SdFat sd;
//Log file
SdFile datafile;  

//File datafile;   // The logging file
String dataString;    // This is the holder for the data as a string. Start as blank
int counter = 0;   // Clue is in the name - its a counter.
volatile long dataCounter = 0;  // This holds the number of seconds since the last data store

// ******** WS2811 LED**************************************/
#define LED_WS2811 A3
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, LED_WS2811, NEO_GRB + NEO_KHZ800);

//// ********** OLED ******************************************/
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI

// ********** RTC ******************************************/
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
#define RTCinterrupt 0  // RTC interrupt - This is pin 2 of ardunio - which is INT0

///*************Real Time Clock*******/
//Rtc_Pcf8563 rtc;
//#define I2C_RTC 0x51 // 7 bit address (without last bit - look at the datasheet)


/************* Pulse counter *******/
#define pulseInterrupt 1  // Pulse Counter Interrupt - This is pin 3 of arduino - which is INT1
#define ANEMOMETER1 3   //   This is digital pin the pulse is attached to
#define ACFREQ 4        //   This is digital pin the pulse is attached to

/********* I/O Pins *************/
#define calibrate 8   // This controls if we are in serial calibrate mode or not

/********** ADC info **************/
#define ADC_CS 9      // Pin for the CS for the ADC
#define ADC_VREF    3280     // 3.3V Vref
#define ADC_CLK     1600000  // SPI clock 1.6MHz

#define battVoltagePin A0   // The battery voltage with a potential divider (100k//100k)
//#define voltagePin A2  // The external voltage with a potential divider (470k // 47k)
//#define current1Pin A3  // Current from a hall effect sensor
//#define vanePin A0      // The wind vane with a 10k pull UP

// We now read data from the ADC - so need to know which ADC lines to read
#define voltagePin  SINGLE_0  // The external voltage with a potential divider (470k // 47k) ADC 0
#define vanePin     SINGLE_1  // The wind vane with a 10k pull UP!! ADC 1
#define current1Pin 2  // Current from a hall effect sensor ADC 2

MCP3208 adc(ADC_VREF, ADC_CS);


/********** Wind Direction Storage *************/
String WindDirection = " ";  // Empty to start with
int windDirectionArray[] = {0,0,0,0,0,0,0,0,0};  //Holds the frequency of the wind direction

///********* Battery Voltage ****************/
float batteryVoltage;        // Temporary store for float
char BatteryVoltStr[6];      // Hold the battery voltage as a string

///********* Battery Voltage ****************/
float externalVoltage;        // Temporary store for float
char ExternalVoltStr[7];      // Hold the battery voltage as a string

///********* Current 1 ****************/
long int currentData1;      // Temp holder for value
long int currentDataAve;      // Temp holder for value
float current1;        // Temporary store for float
float currentOffset;  // Holds the offset current
int currentOffsetInt;  // Hold sthe current offset as an in for EEPROM storing
char Current1Str[8];      // Hold the current as a string

// ****** Serial Data Read***********
// Variables for the serial data read
char inByte;         // incoming serial char
String str_buffer = "";  // This is the holder for the string which we will display

//********Variables for the Filename*******************

char filename[] = "DXXXXXX.csv";  // This is a holder for the full file name
char deviceID[3]; // A buffer to hold the device ID

long sampleTime = 2;  // This is the time between samples for the DAQ
                      // Sample time is stored in EEPROM in locations 2 & 3

// Variables for the Pulse Counter
volatile long pulseCounter1 = 0;  // This counts pulses from the flow sensor  - Needs to be long to hold number
volatile long pulseCounter1Old = 0;  // This is storage for the old flow sensor - Needs to be long to hold number

volatile long pulseCounter2 = 0;  // This counts pulses from the flow sensor  - Needs to be long to hold number
volatile long pulseCounter2Old = 0;  // This is storage for the old flow sensor - Needs to be long to hold number

volatile boolean writedataflag = LOW;  // A flag to tell the code when to write data

// Varibales for writing to EEPROM
int hiByte;      // These are used to store longer variables into EERPRPROM
int loByte;

// Varibles for 'I'm alive' flash
int aliveFlashCounter = 0;  // This is used to count to give flash every 10 seconds

// These next ints are for the filename conversion
int day_int =0;      // To find the day from the Date for the filename
int day_int1 =0;
int day_int2 =0;
int month_int = 0;
int month_int1 = 0;
int month_int2 = 0;
int year_int = 0;  // Year
int hour_int = 0;
int min_int = 0;
int sec_int = 0;

boolean calibrateFlag = HIGH;  // This flag is lowered if we are in calibrate mode (switch ON)

boolean pulse1Flag = LOW;
boolean pulse2Flag = LOW;
boolean cardDetectFlag=LOW;
boolean oldCardDetectFlag=LOW;
boolean checkCurrentFlag = LOW; // To tell the unit to check the data (only when RTC interrupt)

//**********STRINGS TO USE****************************
String comma = ",";
String date;        // The stored date from filename creation
String newdate;     // The new date, read every time 

// These are Char Strings - they are stored in program memory to save space in data memory
// These are a mixutre of error messages and serial printed information
const char headers[] PROGMEM = "Ref, Date, Time, Wind1, AC/Wind2, Direction, Batt V, Ext V, Current, Temp(C)";  // Headers for the top of the file
const char headersOK[] PROGMEM = "Headers OK";
const char erroropen[] PROGMEM = "Error open";
const char error[] PROGMEM = "ERROR";
const char initialisesd[] PROGMEM = "Init SD";
const char dateerror[] PROGMEM = "Date ERR";
const char reference[] PROGMEM = "The ref is:";
const char noSD[] PROGMEM = "No SD card";

#define MAX_STRING 130      // Sets the maximum length of string probably could be lower
char stringBuffer[MAX_STRING];  // A buffer to hold the string when pulled from program memory

// DEBUG ONLY
boolean debugFlag = HIGH;    // Set this if you want to be in debugging mode.

/***************************************************
 *  Name:        pulse1
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Count pulses from Anemometer 1
 *
 ***************************************************/
void pulse1(void)
{
  // If the anemometer has spun around
  // Increment the pulse counter
  pulseCounter1++;
  // ***TO DO**** Might need to debounce this
  pulse1Flag=HIGH;
}

/***************************************************
 *  Name:        pulse2
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Count pulses from Anemometer 2
 *
 ***************************************************/
void pulse2(void)
{
  // If the anemometer has spun around
  // Increment the pulse counter
  pulseCounter2++;
  // ***TO DO**** Might need to debounce this
  pulse2Flag=HIGH;
}

/***************************************************
 *  Name:        RTC
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: I use the CLK_OUT from the RTC to give me exact 1Hz signal
 *               To do this I changed the initialise the RTC with the CLKOUT at 1Hz
 *
 ***************************************************/
void RTC()
{ 
  //detachInterrupt(RTCinterrupt);
  if(dataCounter<=0)
  {
    dataCounter=0;
  }
  dataCounter++;
  aliveFlashCounter++;
  checkCurrentFlag=HIGH;
  
  if(writedataflag==LOW&&dataCounter>=sampleTime)  // This stops us loosing data if a second is missed
  { 
    // If this interrupt has happened then we want to write data to SD card:
    // Save the pulsecounter value (this will be stored to write to SD card
    pulseCounter1Old = pulseCounter1;
    pulseCounter2Old = pulseCounter2;
   // Reset the pulse counter
    pulseCounter1 = 0;
    pulseCounter2 = 0;
   
    // Set the writedataflag HIGH
    writedataflag=HIGH;
  }
}

/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Enters the arduino into sleep mode.
 *
 ***************************************************/
void enterSleep(void)
{

  attachInterrupt(RTCinterrupt, RTC, RISING);
  sleep_enable(); 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  
  byte old_ADCSRA = ADCSRA;  // Store the old value to re-enable 
  // disable ADC
  ADCSRA = 0;

  byte old_PRR = PRR;  // Store previous version on PRR
  // turn off various modules
  PRR = 0b11111111;
  
  sleep_cpu();
  /* The program will continue from here. */
  /************* ASLEEP *******************/
  
  // ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ //
  
  /************** WOKEN UP ***************/
  /* First thing to do is disable sleep. */
  sleep_disable();
  
  // turn ON various modules USART and ADC
  PRR = old_PRR;  
  
  // enable ADC
  ADCSRA = old_ADCSRA;  
 
  //Set up the calibrate line again (should have been OK)
  pinMode(calibrate,INPUT_PULLUP);
  // Initialise the ADC with correct set-up
  // Initialize SPI interface for MCP3208
  // set initial PIN state
  digitalWrite(ADC_CS, HIGH);
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(settings);
  
}


/***************************************************
 *  Name:        setup
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Setup for the Arduino.           
 *
 ***************************************************/
void setup()
{
  Serial.begin(115200);
  //Wire.begin();

  //WS2811 LED info
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  //******Real Time Clock Set - up********
  // A4 and A5 are used as I2C interface.
  // D2 is connected to CLK OUT from RTC. This triggers an interrupt to take data
  // We need to enable pull up resistors
  pinMode(A4, INPUT_PULLUP);           // set pin to input
  pinMode(A5, INPUT_PULLUP);           // set pin to input
  pinMode(RTCinterrupt,INPUT);    // Set D2 to be an input for the RTC CLK-OUT   

  // Initialize the rtc object
  rtc.begin();
  
  pinMode(ADC_CS, OUTPUT);
  
  // Initialise the ADC with correct set-up
  // Initialize SPI interface for MCP3208
  // set initial PIN state
  digitalWrite(ADC_CS, HIGH);
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(settings);
 
  //Set up digital data lines
  pinMode(calibrate,INPUT_PULLUP);
  
  analogReference(EXTERNAL);  // This should be default, but just to be sure

  // Put unused pins to INPUT to try and save power...      
  
  setupRTC();  // Initialise the real time clock  
  
  initialiseSD();    // Inisitalise the SD card   
  createfilename();  // Create the corrct filename (from date)

  // Read the reference number from the EEROM
  deviceID[0] = char(EEPROM.read(0));
  deviceID[1] = char(EEPROM.read(1));
  
  // Read in the sample time from EEPROM
  hiByte = EEPROM.read(2);
  loByte = EEPROM.read(3);
  sampleTime = (hiByte << 8)+loByte;  // Get the sensor calibrate value 
  Serial.print("Sample time:");
  Serial.println(sampleTime);
  Serial.flush();
  
  // Read the Current Voltage Offset from the EEROM
  hiByte = EEPROM.read(4);
  loByte = EEPROM.read(5);
  currentOffsetInt = (hiByte << 8)+loByte;  // Get the sensor calibrate value
  currentOffset = float(currentOffsetInt)*3.3f/1023.0f;   // Convert the current offset to a voltage
  
  // Attach interrupts for the pulse counting
  pinMode(ANEMOMETER1, INPUT_PULLUP); 
  PCintPort::attachInterrupt(ANEMOMETER1, &pulse1, FALLING);  // add more attachInterrupt code as required
  pinMode(ACFREQ, INPUT_PULLUP); 
  PCintPort::attachInterrupt(ACFREQ, &pulse2, FALLING); 
  attachInterrupt(RTCinterrupt, RTC, RISING);
}

/***************************************************
 *  Name:        main loop
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Main application loop.
 *
 ***************************************************/
void loop()
{

  if((pulse1Flag==HIGH||pulse2Flag==HIGH)&&calibrateFlag==HIGH)
  {
    //debouce?
    attachInterrupt(RTCinterrupt, RTC, RISING);    
    delayMicroseconds(50);
    // Do nothing else and go back to sleep
    pulse1Flag=LOW; // Reset the flags  
    pulse2Flag=LOW;// Reset the flags  
    if(dataCounter<=0)
    {
      dataCounter=0;
    }
    enterSleep(); 
  }
  else
  {
    // A Switch on D7 will set if the unit is in serial adjust mode or not  
    //calibrateFlag = digitalRead(calibrate);  
    calibrateFlag=digitalRead(calibrate);
    
    if(calibrateFlag==LOW)
    { 
      //detachInterrupt(RTCinterrupt);  
      // We ARE in calibrate mode
      pulseCounter1Old = pulseCounter1;
      pulseCounter2Old = pulseCounter2;
     // Reset the pulse counter
      pulseCounter1 = 0;
      pulseCounter2 = 0;
      Serial.println("Calibrate"); 
      Serial.flush();    // Force out the end of the serial data     
      getData();
      delay(1000);  // Some time to read data (Does NOT sleep in calibrate mode)     
      writedataflag=HIGH;  // Set the write data flag high 
      currentData1 = 0; // Reset the current data
      checkCurrentFlag=HIGH ; // Also check the current
      pulse1Flag=LOW; // Reset the flags
      pulse2Flag=LOW; // Reset the flags
      if(dataCounter<=0)
      {
        dataCounter=0;
      }
    }
    else
    {
      attachInterrupt(RTCinterrupt, RTC, RISING);      
      enterSleep();     
    }
    
  
    if(checkCurrentFlag==HIGH)
    {
      // Is the SD OK?
      // If Not then show a RED error
      // ***** TO DO *************************************
      
      // *********** WIND DIRECTION **************************************  
      // Want to measure the wind direction every second to give good direction analysis
      // This can be checked every second and an average used
      // We are now using the ADC to read this so must read Channel 1 from ADC at 10 bit resolution.
      // set initial PIN state   
      convertWindDirection(adc.read(MCP3208::vanePin));    // Run this every second. It increments the windDirectionArray        

               
      // *********** Check current every 1 sec and average*******************
      currentDataAve=0; // Reset this value before doing measurement
      // Current averaging - 1 second amples averaged over sample period
      for(int y=0;y<10;y++)
      {
//        currentDataAve += analogRead(current1Pin);
        delay(1);
      }
      currentData1 += (float(currentDataAve)/10.0);
      
      if(calibrateFlag==HIGH)
      {
        Serial.println(sampleTime-dataCounter+1);
        Serial.flush();    // Force out the end of the serial data
      }       
      checkCurrentFlag=LOW;
      
    }
   
    if(aliveFlashCounter>=10)
    {
      // Flash the LED every 10 seconds to show alive
      strip.setPixelColor(0, strip.Color(255,0,0));
      strip.show();
      delay(50);
      strip.setPixelColor(0, strip.Color(0,0,0));
      strip.show();
      aliveFlashCounter=0;  // Reset the counter 
    }
  
    if(writedataflag==HIGH)
    {  
      strip.setPixelColor(0, strip.Color(0,0,255));
      strip.show();
  
      // *********** WIND SPEED ******************************************
      // Want to get the number of pulses and average into the sample time
      // This gives us the average wind speed
      // pulsecounterold holds the value of pulses.
      // This can be converted into the wind speed using the time and 
      // the pulse-wind speed characterisitic of the anemometer.
      // Do this as post processing - pulse count is most important.
      
      // *********** WIND DIRECTION **************************************
      // This can be checked every second and an average used
      WindDirection = analyseWindDirection();
      for(int i=0;i<9;i++)
      {
        //Resets the wind direction array
        windDirectionArray[i]=0;
      }
      
  
      // *********** BATTERY VOLTAGE ***************************************
      // From Vcc-100k-DATA-100k-GND potential divider
      // This is to test in case battery voltage has dropped too low - alert?
      batteryVoltage = float(analogRead(battVoltagePin))*(3.3f/1024.0f)*((100.0f+100.0f)/100.0f);        // Temporary store for float
      dtostrf(batteryVoltage,2,2,BatteryVoltStr);     // Hold the battery voltage as a string
      
      // ******* TO DO********************* //
      // Battery LOW Alert //
      
  
      // *********** EXTERNAL VOLTAGE ***************************************
      // From Vcc-2200k--10k-GND potential divider
      // Read on ADC Channel 0
//      externalVoltage = float(analogRead(voltagePin))*(3.3f/1023.0f)*((570.0f+10.0f)/10.0f);        // Temporary store for float
//      dtostrf(externalVoltage,2,2,ExternalVoltStr);     // Hold the battery voltage as a string    
      //digitalWrite(ADC_CS, LOW);    
      
      externalVoltage=float(adc.read(MCP3208::voltagePin));
       
      uint16_t raw = adc.read(MCP3208::SINGLE_0);
      uint16_t val = adc.toAnalog(raw);  
          
      //digitalWrite(ADC_CS, HIGH); 
      Serial.println(externalVoltage);
      externalVoltage=externalVoltage*(float(ADC_VREF)/(4096.0f*1000.0f))*((220.0f+10.0f)/10.0f);
      Serial.println(externalVoltage);      
      dtostrf(externalVoltage,2,3,ExternalVoltStr);     // Hold the battery voltage as a string

      // readed value
      Serial.print("value: ");
      Serial.print(raw);
      Serial.print(" (");
      Serial.print(val);
      Serial.println(" mV)");
      
      // ********** EXTERNAL CURRENTS **************************************
      // Measured using a hall effect current sensor
      // Either using a ACS*** or a LEM HTFS 200-P
      // Comment out whichever you are not using
   
  
      // Lets average the data here over sample period (in normal mode) or over 1 second (if calibrate mode):
      if(calibrateFlag==HIGH)
      {
        current1 = float(currentData1)/float(sampleTime);
      }
      else
      {
        current1 = float(currentData1);
      }
      currentData1 = 0;  // Reset the value
            
      current1 = (current1*3.3f/1023.0f) - currentOffset ;
      // Current 1 holds the incoming voltage.
  
           
      // ********** LEM HTFS 200-P SENSOR *********************************
      // Voutput is Vref +/- 1.25 * Ip/Ipn 
      current1 = (current1*200.0f)/1.25f;
      
  //    // ********* LEM HASS 50-S******************************************
  //    //  http://www.lem.com/docs/products/hass_50_600-s.pdf
  //    // Voutput is Vref +/- 0.625 * Ip/Ipn
  //    current1 = (current1 * 50.0f) / 0.625f;    
  
    
  //    // ************* ACS*** Hall Effect **********************
  //    // Output is Input Voltage - offset / mV per Amp sensitivity
  //    // Datasheet says 60mV/A 
  //    
  
      
      // Convert the current to a string.
      dtostrf(current1,2,2,Current1Str);     // Hold the battery voltage as a string
    
      // ******** put this data into a file ********************************
      // ****** Check filename *********************************************
      // Each day we want to write a new file.
      // Compare date with previous stored date, every second
      newdate = String(rtc.getDateStr(FORMAT_SHORT));  
      if(newdate != date)
      {
         // If date has changed then create a new file
         createfilename();  // Create the corrct filename (from date)
      }    
  
      // ********* Create string of data **************************
      // Data in format: "Ref, Date, Time, Wind1, AC/Wind2, Direction, Batt V, Ext V, Current, Temp(C)" //
      
      dataString =  String(deviceID[0]); 
      dataString += deviceID[1];  // Reference
      dataString += comma;
      dataString += newdate;  // Date
      dataString += comma;
      dataString += String(rtc.getTimeStr()); // Time
      dataString += comma;
      dataString += String(pulseCounter1Old); // Wind pulses 1
      dataString += comma;
      dataString += String(pulseCounter2Old); // AC Freq OR Wind pulses 2
      dataString += comma;
      dataString += WindDirection; // Wind direction (from ADC)
      dataString += comma;
      dataString += BatteryVoltStr;  // Battery voltage  (From analog pin)
      dataString += comma;
      dataString += ExternalVoltStr;  // External Voltage reading (from ADC)
      dataString += comma;
      dataString += Current1Str;  // Current 2 reading (from ADC)
      dataString += comma;
      dataString += String(rtc.getTemp());  // Read RTC internal temperature sensor

      // Want to check if SD card has been inserted
      if(cardDetectFlag == HIGH)
      {
        // Check if SD is available
        // if the file is available, write to it:
        if (!sd.cardBegin()) {
          Serial.println(getString(noSD));
          Serial.flush();
          cardDetectFlag = HIGH;  // Set a flag to ensure SD is re-initialised.   
        }
        else
        {
          oldCardDetectFlag = cardDetectFlag;
          cardDetectFlag = LOW;  // Set a flag to ensure SD is re-initialised.
            // if the file is available, write to it:      
        }
      }
      if(cardDetectFlag==LOW&&oldCardDetectFlag==HIGH)
      {
        initialiseSD();
        oldCardDetectFlag = LOW;
      }
  
      // ************** Write it to the SD card if calibrate is NOT high *************
      // This depends upon the card detect.
      // If card is there then write to the file
      // If card has recently been inserted then initialise the card/filenames
      // If card is not there then flash LEDs
      

      if(calibrateFlag==HIGH&&cardDetectFlag==LOW)
      {
        //Ensure that there is a card present
        // We then write the data to the SD card here:
        writetoSD();    
      }
      else
      {
         // print to the serial port Do NOT write:
         Serial.println(dataString);
         Serial.flush();    // Force out the end of the serial data
      }      
      
      // Finish up write routine here:    
      // Switch OFF LED
      strip.setPixelColor(0, strip.Color(0,0,0));
      strip.show(); 
      
      writedataflag=LOW;
      
      if(calibrateFlag==LOW)
      {
         // Reset the DataCounter
        dataCounter = -1;            
      }
      else
      {
        // Reset the DataCounter
        dataCounter = 0;  
      }
    }
  }  
}

// Set Up RTC routine
void setupRTC()
{
  // We need to set up the 1Hz output from the RTC here:
  rtc.setOutput(OUTPUT_SQW);
  rtc.setSQWRate(SQW_RATE_1);
  
}

// Converts a decimal to BCD (binary coded decimal)
byte DecToBcd(byte value){
  return (value / 10 * 16 + value % 10);
}

//*********** FUNCTION TO INITIALISE THE SD CARD***************
void initialiseSD()
{
  // Initialize the SD card at SPI_HALF_SPEED to avoid bus errors 
  // We use SPI_HALF_SPEED here as I am using resistor level shifters.
  //if (!sd.begin(SD_CS, SPI_HALF_SPEED)) sd.initErrorHalt();
  
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(SD_CS, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!sd.begin(SD_CS, SPI_HALF_SPEED)) {
    if(debugFlag==HIGH)
    {
      Serial.println("FAIL");
    }
    // don't do anything more:
    // Want to turn on an ERROR LED here
    return;
  }
  else
  {
    if(debugFlag==HIGH)
    {
      Serial.println(getString(initialisesd));
    }
  }
}

// *********FUNCTION TO SORT OUT THE FILENAME**************
void createfilename()
{
  // Check there is a file created with the date in the title
  // If it does then create a new one with the new name
  // The name is created from:
  // DMMDDYY.CSV, where YY is the year MM is the month, DD is the day
  // You must add on the '0' to convert to ASCII

  // Init a Time-data structure
  Time  t;
  
  // Get data from the DS3231
  t = rtc.getTime();
  
  date = String(rtc.getDateStr(FORMAT_SHORT));
  day_int = t.date;  // Get the actual day from the RTC
  month_int = t.mon;  // Get the month
  year_int = t.year;  // Get the year
  year_int = year_int-2000;   // Remove the year 2000
  day_int1 = day_int/10;    // Find the first part of the integer
  day_int2 = day_int%10;    // Find the second part of the integer
  month_int1 = month_int/10;    // Find the first part of the integer
  month_int2 = month_int%10;    // Find the second part of the integer
  filename[1]=(year_int/10) + '0';  // Convert from int to ascii
  filename[2]=(year_int%10) + '0';  // Convert from int to ascii 
  filename[3]= month_int1 + '0';  // Convert from int to ascii
  filename[4]= month_int2 + '0';  // Convert from int to ascii   
  filename[5]= day_int1 + '0';  // Convert from int to ascii
  filename[6]= day_int2 + '0';  // Convert from int to ascii 
  
  if(debugFlag==HIGH)
  {
    Serial.println(filename);
  }
  
  if(!sd.exists(filename))
  {
    // open the file for write at end like the Native SD library
    if (!datafile.open(filename, O_RDWR | O_CREAT | O_AT_END)) 
    {
      if(debugFlag==HIGH)
      {
        Serial.println(getString(erroropen));
        delay(100);
      }
    }
    // if the file opened okay, write to it:
    datafile.println(getString(headers));
    // close the file:
    datafile.close();
    
    if(debugFlag==HIGH)
    {
      Serial.println(getString(headersOK));
    }
  } 
  else
  {
    if(debugFlag==HIGH)
    {
      Serial.println("Filename OK");
    }
  }
  
}

// This routine writes the dataString to the SD card
void writetoSD()
{
  Serial.println("Writing to SD...");
  
  // if the file is available, write to it:
  if (!sd.cardBegin()) {
    Serial.println(getString(noSD));
    Serial.flush();
    cardDetectFlag = HIGH;  // Set a flag to ensure SD is re-initialised.   
  } 
  else if (sd.exists(filename)) 
  {  
    datafile.open(filename, O_RDWR | O_CREAT | O_AT_END);    // Open the correct file    
    datafile.println(dataString);
    datafile.close();
    // print to the serial port too:
    Serial.println(dataString);
    Serial.flush();    // Force out the end of the serial data
  }  
  
  // if the file isn't open, pop up an error:
  else 
  {
    if(debugFlag==HIGH)
    {
      Serial.println(getString(erroropen));
      delay(100);
    }
  }
}

// Get a string from program memory
// This routine pulls the string stored in program memory so we can use it
// It is temporaily stored in the stringBuffer
char* getString(const char* str) {
	strcpy_P(stringBuffer, (char*)str);
	return stringBuffer;
}

// **********************GET DATA SUBROUTINE*****************************************
// This sub-routine picks up and serial string sent to the device and sorts out a power string if there is one
// All values are global, hence nothing is sent/returned

void getData()
{
    // **********GET DATA*******************************************
  // We want to find the bit of interesting data in the serial data stream
  // If we write H then house number then the code will update the house number in EEPROM
  // **** aslo need to write code to update RTC
  
  for(int i = 0; i<10;i++)  // This helps us just take a 'chunk' of data so does not fill up serial buffer
  {
    // get incoming bytes:
    if (Serial.available() > 0) 
    {
     inByte = Serial.read(); 
     str_buffer+=inByte;
    
     if(inByte=='E')    // We read everything up to the byte 'E' which stands for END
     {
       int buffer_length = str_buffer.length();  // We also find the length of the string so we know how many char to display 
       // Depending upon what came before we update different values
       // To change the reference number we enter R00E, where 00 can be any number up to 99 

        for(int i = buffer_length; i>=0; i--)  // Check the buffer from the end of the data, working backwards
        {
          if(str_buffer[i]=='R')
          {
              // In this case we have changed the house number, so UPDATE and store in EEPROM
              deviceID[0]=str_buffer[i+1];
              deviceID[1]=str_buffer[i+2];
              Serial.print(getString(reference));
              Serial.print(deviceID[0]);
              Serial.println(deviceID[1]);
              EEPROM.write(0,deviceID[0]);
              EEPROM.write(1,deviceID[1]);
              initialiseSD();
              createfilename();
          }          
          if(str_buffer[i]=='T')
          {
              // In this case we have changed the TIME, so UPDATE and store to RTC
              // The time is in the format  HHMMSS
              
              String hourstr = str_buffer.substring(i+1,i+3);
              int hour = atoi(&hourstr[0]);
              String minutestr = str_buffer.substring(i+3,i+5);
              int minute = atoi(&minutestr[0]);
              String secondstr = str_buffer.substring(i+5,i+7);
              int second = atoi(&secondstr[0]);
              //hr, min, sec into Real Time Clock
              rtc.setTime(hour, minute, second);
              
              initialiseSD();
              createfilename();
              Serial.print("New Time: ");              
              Serial.println(rtc.getTimeStr()); // Time
          }
          if(str_buffer[i]=='D')
          {
              // In this case we have changed the DATE, so UPDATE and store to RTC
              // The time is in the format  DDMMYY
              
              String daystr = str_buffer.substring(i+1,i+3);
              int day = atoi(&daystr[0]);
              String monthstr = str_buffer.substring(i+3,i+5);
              int month = atoi(&monthstr[0]);          
              String yearstr = str_buffer.substring(i+5,i+7);
              int year = atoi(&yearstr[0]) + 2000;          
              
              //day, month, year(0-99)
              rtc.setDate(day, month, year);                   
              initialiseSD();
              createfilename();
              Serial.print("New Date: ");
              Serial.println(rtc.getDateStr());
          }           
          if(str_buffer[i]=='S')
          {          
              // In this case we have changed the sample time, so UPDATE and store to EEPROM
              // Data will be in the form of 5 x chars, signifying XXXXX, a value from 00001 to 99999 seconds
              
              sampleTime = atol(&str_buffer[i+1]);  // Convert the string to a long int
              
              EEPROM.write(2, sampleTime >> 8);    // Do this seperately
              EEPROM.write(3, sampleTime & 0xff);
              Serial.print("Sample Time:");
              Serial.println(sampleTime);
              
              //dataCounter=0;  // Reset the data counter to start counting again.
          }
          
          if(str_buffer[i]=='O')
          {    
            // ******** Recalibrate the offset *******************
            
            // We want to measure the offset for the current sensor here. 
            // This will be changed to a calibrate function.
            // When switched on the unit should not have any current through the sensor or this
            // will read incorrectly.
            delay(100);
            currentData1 = 0;  // Reset this holder
            for(int i = 0;i<=19;i++)
            {  
//              currentData1 += analogRead(current1Pin);
              delay(20);
            }           
            currentOffsetInt = currentData1/20;
            
            currentOffset = float(currentOffsetInt)*3.3f/1023.0f;
            Serial.print("Ioffset:");
            Serial.print(currentOffset);
            Serial.println("V");
            delay(100);    
            
            // Write this info to EEPROM   
            EEPROM.write(4, currentOffsetInt >> 8);    // Do this seperately
            EEPROM.write(5, currentOffsetInt & 0xff);     
          }        
        }
        str_buffer="";  // Reset the buffer to be filled again 
      }
    }
  }
}

// ******** CALC DIRECTION *********
// This routine takes in an analog read value and converts it into a wind direction
// The Wind vane uses a series of resistors to show what direction the wind comes from
// The different values are (with a 10k to Ground/3.3V):
// CHANGED for ADC - 12 bits
//    10 bit ADC Pull DOWN  // 12 Bit ADC Pull UP
//    R1 = 33k  => 238 N 3143
//    R2 = 8.2k => 562 NE 1845
//    R3 = 1k => 930 E 372
//    R4 = 2.2k => 839 SE 739 
//    R5 = 3.9k => 736 S 1149
//    R6 = 16k => 394 SW 2520
//    R7 = 120k => 79 W 3780
//    R8 = 64.9k => 137 NW 3549
//    No Connection - 2279 (12 bit ADC Pull UP)

// The different values are (with a 10k to Vbattery):
// The value will be 4096 - vane integer reading

// This means we can 'band' the data into 8 bands

void convertWindDirection(uint16_t reading)
{
  
  // The reading has come from the ADC

  if(reading>=300&&reading<450)
  {
    windDirectionArray[2]++; // E
  }
  else if(reading>=600&&reading<850)
  {
    windDirectionArray[3]++; // SE
  }
  else if(reading>=850&&reading<1300)
  {
    windDirectionArray[4]++;  // S
  }
  else if(reading>=1300&&reading<2000)
  {
    windDirectionArray[1]++; // NE
  }   
  else if(reading>=2200&&reading<2400)
  {
    windDirectionArray[8]++;  //  N/C // This if for No Connection! Pulled UP, but rests here for some reason.
  }   
  else if(reading>=2400&&reading<2900)
  {
    windDirectionArray[5]++;  // SW
  }
  else if(reading>=2900&&reading<3200)
  {
    windDirectionArray[0]++;  //N    
  }
  else if(reading>=3200&&reading<3400)
  {
    windDirectionArray[7]++;  // NW
  }  
  else if(reading>=3400&&reading<3700)
  {  
    windDirectionArray[6]++;   // W
  }  
  else if(reading>=3950)
  {
    windDirectionArray[8]++;  // N/C // This if for No Connection! Pulled UP
  }   
  else
  {
      // This is an error reading
  }
}

String analyseWindDirection()
{
  // When a data sample period is over we need to see the most frequent wind direction.
  // This needs to be converted back to a direction and stored on SD
  
  int data1 = windDirectionArray[0];
  int maxIndex = 0;
  // First need to find the maximum integer in the array
  for(int i=1;i<9;i++)
  {
    if(data1<windDirectionArray[i])
    {
      data1=windDirectionArray[i];
      maxIndex = i;
    }
  }
  //Serial.println(maxIndex);  //Testing
    
  
  // Then convert that into the direction
  switch(maxIndex)
  {
    case 0:
      return("N");
    break;
    case 1:
      return("NE");
    break;    
    case 2:
      return("E");
    break;  
    case 3:
      return("SE");
    break;
    case 4:
      return("S");
    break;  
    case 5:
      return("SW");
    break;
    case 6:
      return("W");
    break;
    case 7:
      return("NW");
    break;
    case 8:
      return("N/C"); // If the value is 0 for any length of time - not connected
    break;
  }
}
