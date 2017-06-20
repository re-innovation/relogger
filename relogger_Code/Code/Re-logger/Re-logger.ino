#include <PinChangeInt.h>

#include <Adafruit_NeoPixel.h>

#include <SPI.h>
#include <BlockDriver.h>
#include <FreeStack.h>
#include <MinimumSerial.h>
#include <SdFat.h>
#include <SdFatConfig.h>
#include <SysCall.h>

#include <DS3231.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>

#define RGB_LED_PIN    6
#define NUMPIXELS      1

#define SD_CS_PIN      SS

#define ONE_WIRE_BUS   6

#define DOWN_BUTTON    5

#define RTC_INT_PIN    2

DS3231  rtc(A4, A5);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

SdFat SD;
File myFile;

int k = 0;
int k_1 = 0;

char firstTimeWS = 1;
int cptBuff1 = 0;
int cptPulse1 = 0;
int cptBuff2 = 0;
int cptPulse2 = 0;
int cptST = 0;
char rtc_flag = 0;
volatile int f_wdt=1; 

char test_at[5] = "1234";
int res;
char flagWriteData = 0;
char car = 0;

int sampleTime = 0;

int dataNumber = -1;
char dateFile[20];
char pathMes[30];

// Structure that stores the informations for one value to measure
struct dataToRead {
  int dataPin;
  char dataName[4];
  char dataType[2];
  float dataCal1;
  float dataCal2;
  char dataUnit[3];
  char dataAD;
};

// Array that stores all the informations about the data to measure got from the parsed config file
dataToRead fileFormat[10];

// Array that stores the sensorValues
int sensorValues[10];

// Array that stores the measured values after the conversion from sensorValues to measuredValues
float measuredValues[10];

/*********************************************************/
void setup() {
  // put your setup code here, to run once:
  char valid = 0;
  String pathDate;

  /*
   * Begin() of all libraries
   */  
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  sensors.begin();
  
  pixels.begin(); 
  
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("error init sd");
    return;
  }

  rtc.begin();

  /*
   * Set the date
   */
   
  /*do{
  valid = setDte();
  }while(valid == 0);*/

  /*
   * Create a file if doesn't exists
   */

  pathDate = "Re-Logger/";
  pathDate.concat(rtc.getDateStr());
  pathDate.concat(".csv");
  //Serial.println(pathDate);
  pathDate.toCharArray(pathMes, 30);
  //Serial.println(pathMes);
  if (!myFile.exists(pathMes))
  {
    if (!myFile.open(pathMes, O_CREAT | O_WRITE)) {
      Serial.println("fail create File");
    }
    myFile.close();
  }

  /*
   * Init the watchdog timer
   */

  MCUSR &= ~(1<<WDRF);                                          // Clear the reset flag  
  WDTCSR |= (1<<WDCE) | (1<<WDE);                               // In order to change WDE or the prescaler, we need to set WDCE (This will allow updates for 4 clock cycles).
  WDTCSR = 0<<WDP3 | 1<<WDP2 | 0<<WDP1 | 0<<WDP0;               // Set new watchdog timeout prescaler value (0.250 seconds)
  WDTCSR |= _BV(WDIE);                                          // Enable the WD interrupt (note no reset)

  /*
   * Read config file and parse it
   */
  getFileFormat();

  delay(1000);

  Serial.println(sampleTime);
  Serial.println(fileFormat[0].dataPin);
  Serial.println(fileFormat[0].dataName);
  Serial.println(fileFormat[0].dataType);
  Serial.println(fileFormat[0].dataCal1);
  Serial.println(fileFormat[0].dataCal2);
  Serial.println(fileFormat[0].dataUnit);
  Serial.println(fileFormat[0].dataAD);

  delay(1000);

  Serial.println(fileFormat[1].dataPin);
  Serial.println(fileFormat[1].dataName);
  Serial.println(fileFormat[1].dataType);
  Serial.println(fileFormat[1].dataCal1);
  Serial.println(fileFormat[1].dataCal2);
  Serial.println(fileFormat[1].dataUnit);
  Serial.println(fileFormat[1].dataAD);

  delay(1000);

  writeHeaderOnFile();

  /*
   * Init the RTC "interrupt"
   */  
     
  rtc.setOutput(OUTPUT_SQW);
  rtc.setSQWRate(SQW_RATE_1);
  pinMode(RTC_INT_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(RTC_INT_PIN), rtc_ISR, RISING);
  
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void loop() {
  String pathDate;
  // put your main code here, to run repeatedly:
  
  if(rtc_flag == 1)
  {
    rtc_flag = 0;
  
    cptBuff1 = cptPulse1;
    cptBuff2 = cptPulse2;
    cptPulse1 = 0;
    cptPulse2 = 0;
  
    //read data

    readSensorValues();
    conversion();
    
    //average data
    
    //check if write data
    
    if (cptST >= sampleTime)
    {
      cptST = 0;
      flagWriteData = 1;
    }
  }
  
  
  
  //enable sleep
  sleep_enable();

  sleep_mode();

  sleep_disable();

  power_all_enable();
  
  if(f_wdt == 1)
  {
    // disable sleep
    if(flagWriteData == 1)
    {
      flagWriteData = 0;
      /*
      //check file
      pathDate = "Re-Logger/";
      pathDate.concat(rtc.getDateStr());
      pathDate.concat(".csv");
      //Serial.println(pathDate);
      pathDate.toCharArray(pathMes, 30);
      //Serial.println(pathMes);
      if (!myFile.exists(pathMes))
      {
        if (!myFile.open(pathMes, O_CREAT | O_WRITE)) {
          Serial.println("fail create File");
        }
        myFile.close();
      }

      //write data on file
      writeDataOnFile();
      */
      
    }
    f_wdt = 0;

    //update LED


    //check switchs
    
  }


  
  /*Serial.println(sampleTime);
  Serial.println(fileFormat[0].dataPin);
  Serial.println(fileFormat[0].dataName);
  Serial.println(fileFormat[0].dataType);
  Serial.println(fileFormat[0].dataCal1);
  Serial.println(fileFormat[0].dataCal2);
  Serial.println(fileFormat[0].dataUnit);
  Serial.println(fileFormat[0].dataAD);*/

  //writeOnFile();


  /*k = digitalRead(RTC_INT_PIN);
  if(k!=k_1)
  {
    if(k>k_1){
      rtc_flag = 1;}
    k_1 = digitalRead(RTC_INT_PIN);
  }
  else
  {
    rtc_flag = 0;
  }
  
  if(rtc_flag == 1)
  {
    
  }*/

  /*  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :
  delay (1000);*/

  /*getFileFormat();

  Serial.println(sampleTime);
  Serial.println(fileFormat[0].dataPin);
  Serial.println(fileFormat[0].dataName);
  Serial.println(fileFormat[0].dataType);
  Serial.println(fileFormat[0].dataCal1);
  Serial.println(fileFormat[0].dataCal2);
  Serial.println(fileFormat[0].dataUnit);

  delay(1000);*/
  
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rtc_ISR ()
{
  if(rtc_flag == 0)
  {
    rtc_flag = 1;
  }
  cptST++;
}

void pulse1_ISR ()
{
  cptPulse1++;
}

void pulse2_ISR ()
{
  cptPulse2++;
}

ISR(WDT_vect)                             //Watchdog Interrupt Service. This is executed when watchdog timed out
{
  if(f_wdt == 0)
  {
    f_wdt=1; 
  }
  else
  {
             //Serial.println("WDT Overrun!!!");
  }
}




void error()
{
  Serial.println("error");
  Serial.println("please re-write the config file");
}

char setDte()
{
  char valid = 0;
  int dOw = 0;
  int ho=0;
  int ho_d=0;
  int ho_u=0;
  int mi=0;
  int mi_d=0;
  int mi_u=0;
  int se=0;
  int se_d=0;
  int se_u=0;
  int da=0;
  int da_d=0;
  int da_u=0;
  int mo=0;
  int mo_d=0;
  int mo_u=0;
  int ye=0;
  int ye_m=0;
  int ye_c=0;
  int ye_d=0;
  int ye_u=0;
  //set the date
  Serial.println(" ");
  Serial.println("set the date:");
  Serial.print("day of the week : ");
  do{
    do{
    dOw = Serial.read()-48;
    }while(dOw <0);
    if((dOw>=1) && (dOw<=7))
    {
      valid = 1;
      Serial.println(dOw);
    }
    else
    {
      //Serial.println("error");
      return(0);
    }
  }while(valid == 0);
  valid = 0;
  rtc.setDOW(dOw);     // Set Day-of-Week to SUNDAY
  Serial.print("hour : ");
  do{
      do{
        ho_d = Serial.read()-48;
      }while(ho_d <0);
      Serial.print(ho_d);
      do{
      ho_u = Serial.read()-48;
      }while(ho_u <0);
      ho = 10*ho_d + ho_u;
      if((ho>=0) && (ho<=24))
      {
        valid = 1;
        Serial.println(ho_u);
      }
      else
      {
        //Serial.println("error");
        return(0);
      }
  }while(valid == 0);
  valid = 0;
  Serial.print("minutes : ");
  do{
      do{
         mi_d = Serial.read()-48;
       }while(mi_d <0);
      Serial.print(mi_d);
      do{
      mi_u = Serial.read()-48;
      }while(mi_u <0);
      mi = 10*mi_d + mi_u;
      if((mi>=0) && (mi<=60))
      {
        valid = 1;
        Serial.println(mi_u);
      }
      else
      {
        //Serial.println("error");
        return(0);
      }
  }while(valid == 0);
  valid = 0;
  Serial.print("seconds : ");
  do{
      do{
        se_d = Serial.read()-48;
      }while(se_d <0);
      Serial.print(se_d);
      do{
      se_u = Serial.read()-48;
      }while(se_u <0);
      se = 10*se_d + se_u;
      if((se>=0) && (se<=60))
      {
        valid = 1;
        Serial.println(se_u);
      }
      else
      {
        //Serial.println("error");
        return(0);
      }
  }while(valid == 0);
  valid = 0;
  rtc.setTime(ho, mi, se);     // Set the time to 12:00:00 (24hr format)
  Serial.print("day of the month : ");
    do{
      do{
        da_d = Serial.read()-48;
       }while(da_d <0);
      Serial.print(da_d);
      do{
      da_u = Serial.read()-48;
      }while(da_u <0);
      da = 10*da_d + da_u;
      if((da>=0) && (da<=31))
      {
        valid = 1;
        Serial.println(da_u);
      }
      else
      {
        //Serial.println("error");
        return(0);
      }
  }while(valid == 0);
  valid = 0;
  Serial.print("month : ");
  do{
      do{
        mo_d = Serial.read()-48;
      }while(mo_d <0);
      Serial.print(mo_d);
      do{
      mo_u = Serial.read()-48;
      }while(mo_u <0);
      mo = 10*mo_d + mo_u;
      if((mo>=0) && (mo<=12))
      {
        valid = 1;
        Serial.println(mo_u);
      }
      else
      {
        //Serial.println("error");
        return(0);
      } 
  }while(valid == 0);
  valid = 0;
  Serial.print("year : ");
  do{
    do{
    ye_m = Serial.read()-48;
    }while(ye_m <0);
    Serial.print(ye_m);
    do{
    ye_c = Serial.read()-48;
    }while(ye_c <0);
    Serial.print(ye_c);
    do{
    ye_d = Serial.read()-48;
    }while(ye_d <0);
    Serial.print(ye_d);
      do{
        ye_u = Serial.read()-48;
      }while(ye_u <0);
      ye = 1000*ye_m + 100*ye_c + 10*ye_d + ye_u;
      if((ye>=0) && (ye<=3000))
      {
        valid = 1;
        Serial.println(ye_u);
      }
      else
      {
        //Serial.println("error");
        return(0);
      }
  }while(valid == 0);
  valid = 0;
  rtc.setDate(da, mo, ye);
  return(1);
}

bool getFileFormat ()   //parameters Sample Time, fileFormat and dataNumber
{
  char c = 0;
  char str[5] = {0,0,0,0,0};
  char buff[5] = {'\0','\0','\0','\0','\0'};
  int cpt = 0;
  int i = 0;
  bool valid = false;
  bool pass;
  
  myFile = SD.open("Re-Logger/config.txt");
  
  while (myFile.available())
  {
    pass = false;
    do{
      c = myFile.read();   
      if (c == '$')
      {
         pass = true;
         Serial.print("ok1");
      }
    }while (pass == false);
    pass = false;
    // Sample time
    do{
      c = myFile.read();
      if ((c >= '0') && (c <= '9') && (cpt < 4))
      {
        str[cpt] = c;
        cpt++;
        Serial.print("ok2");
      }
      else if ((c == ';') && (cpt <= 4))
      {
        for (i = 0; i<cpt; i++)
        {
          buff[i] = str[i];
        }
        sampleTime = atoi(buff);
        for (i = 0; i<cpt; i++)
        {
          str[i] = 0;
        }
        for (i = 0; i<5; i++)
        {
          buff[i] = '\0';
        }
        cpt = 0;
        pass = true;
        Serial.print("ok3");
      }
      else 
      {
        error();
        return (false);
      }
    }while (pass == false);
    while (valid == false)
    {
      pass = false;
      do{
        c = myFile.read();
        if (c == '$')
        {
          dataNumber ++;
          pass = true;
          Serial.print("ok4");
        }
        else if (c == '#')
        {
          Serial.println("ok5");
          valid = true;
          return (true);
        }
        else if (c == '\r')
        {
          pass = false;
        }
        else if (c == '\n')
        {
          pass = false;
        }
        else
        {
          error();
          return (false);
        }
      }while (pass == false);
      pass = false;
    // analog/digital
      do{
        c = myFile.read();
        if((c != ';') && (cpt < 1))
        {
          str[cpt] = c;
          cpt++;
          Serial.print("ok18");
        }
        else if ((c == ',') && (cpt <= 1))
        {
          Serial.print("ok19");
          for (i = 0; i<cpt; i++)
          {
            fileFormat[dataNumber].dataAD = str[i];
          }
          for (i = 0; i<cpt; i++)
          {
            str[i] = 0;
          }
          cpt = 0;
          pass = true;
        }
        else
        {
          error();
          return (false);
        }
      }while (pass == false);
      pass = false;
      // Pin
      do{
        c = myFile.read();
        if ((c>='0') && (c<='9') && (cpt < 2))
        {
          str[cpt] = c;
          cpt++;
          Serial.print("ok6");
        }
        else if ((c == ',') && (cpt <= 2))
        {
          for (i = 0; i<cpt; i++)
          {
            buff[i] = str[i];
          }
          fileFormat[dataNumber].dataPin = atoi(buff);
          for (i = 0; i<cpt; i++)
          {
            str[i] = 0;
          }
          for (i = 0; i<5; i++)
          {
            buff[i] = '\0';
          }
          cpt = 0;
          pass = true;
          Serial.print("ok7");
        }
        else
        {
          error();
          return (false);
        }
      }while (pass == false);
      pass = false;
      // Name
      do{
        c = myFile.read();
        if ((c != ',') && (cpt < 4))
        {
          str[cpt] = c;
          cpt ++;
          Serial.print("ok8");
        }
        else if ((c = ',') && (cpt <= 4))
        {
          for (i = 0; i < cpt; i++)
          {
            fileFormat[dataNumber].dataName[i] = str[i];
          }
          for (i = 0; i<cpt; i++)
          {
            str[i] = 0;
          }
          cpt = 0;
          pass = true;
          Serial.print("ok9");
        }
        else
        {
          error();
          return (false);
        }
      }while (pass == false);
      pass = false;
      // Type
      do{
        c = myFile.read();
        if ((c != ',') && (cpt < 2))
        {
          str[cpt] = c;
          cpt ++;
          Serial.print("ok10");
        }
        else if ((c = ',') && (cpt <= 2))
        {
          for (i = 0; i < cpt; i++)
          {
            fileFormat[dataNumber].dataType[i] = str[i];
          }
          for (i = 0; i<cpt; i++)
          {
            str[i] = 0;
          }
          cpt = 0;
          pass = true;
          Serial.print("ok11");
        }
        else
        {
          error();
          return (false);
        }
      }while (pass == false);
      pass = false;
      // calibration 1
      do{
        c = myFile.read();
        if ((((c>='0') && (c<='9')) || c=='.') && (c!=',') && (cpt<4))
        {
          str[cpt] = c;
          cpt ++;
          Serial.print("ok12");
        }
        else if ((c = ',') && (cpt <= 4))
        {
          for (i = 0; i<cpt; i++)
          {
            buff[i] = str[i];
          }
          fileFormat[dataNumber].dataCal1 = atof(buff);
          for (i = 0; i<cpt; i++)
          {
            str[i] = 0;
          }
          for (i = 0; i<5; i++)
          {
            buff[i] = '\0';
          }
          cpt = 0;
          pass = true;
          Serial.print("ok13");
        }
        else
        {
          error();
          return (false);
        }
      }while (pass == false);
      pass = false;
      // calibration 2
      do{
        c = myFile.read();
        if ((((c>='0') && (c<='9')) || c=='.') && (c!=',') && (cpt<4))
        {
          str[cpt] = c;
          cpt ++;
          Serial.print("ok14");
        }
        else if ((c = ',') && (cpt <= 4))
        {
          for (i = 0; i<cpt; i++)
          {
            buff[i] = str[i];
          }
          fileFormat[dataNumber].dataCal2 = atof(buff);
          for (i = 0; i<cpt; i++)
          {
            str[i] = 0;
          }
          for (i = 0; i<5; i++)
          {
            buff[i] = '\0';
          }
          cpt = 0;
          pass = true;
          Serial.print("ok15");
        }
        else
        {
          error();
          return (false);
        }
      }while (pass == false);
      pass = false;
      // Unit
      do{
        c = myFile.read();
        if ((c!=';') && (cpt<3))
        {
          str[cpt] = c;
          cpt ++;
          Serial.print("ok16");
        }
        else if ((c == ';') && (cpt <= 1))
        {
          Serial.print("ok17");
          for (i = 0; i<cpt; i++)
          {
            fileFormat[dataNumber].dataUnit[i] = str[i];
          }
          for (i = 0; i<cpt; i++)
          {
            str[i] = 0;
          }
          cpt = 0;
          pass = true;
        }
        else
        {
          error();
          return (false);
        }
      }while (pass == false);
      
      }
    }
  }

void readSensorValues() // parameters sensorValues[], fileFormat and dataNumber
{
  int i = 0;
  int j = 0;

  for(i = 0; i <= dataNumber; i++)
  {
    if (fileFormat[i].dataType == "T")
    {
      if (fileFormat[i].dataAD == "D")
      {
        sensors.requestTemperatures();
      }
    }
    else if (fileFormat[i].dataType == "WS")
    {
      if (fileFormat[i].dataAD == "D")
      {
        // nothing
      }
    }
    else
    {
      sensorValues[i] = digitalRead(fileFormat[i].dataPin);
      for(j = 0; j < 25; j++)
        sensorValues[i] = ((sensorValues[i] + digitalRead(fileFormat[i].dataPin)) / 2);
    }
  }
}


void conversion ()     // parameters fileFormat, dataNumber, sensorValues, measuredValues
{
  int i = 0;
  int cptPulse = 0;
  float vane = 0.0;

  for(i = 0; i <= dataNumber; i++)
  {
    if (fileFormat[i].dataType[0] == 'V')
    {
      if (fileFormat[i].dataUnit[0] == 'u')
      {
        measuredValues[i] = ((sensorValues[i] * 3.3 / 1024.0) * ((fileFormat[i].dataCal2 + fileFormat[i].dataCal1) / fileFormat[i].dataCal2));
      }
      else if (fileFormat[i].dataUnit[0] == 'm')
      {
        measuredValues[i] = (((sensorValues[i] * 3.3 / 1024.0) * ((fileFormat[i].dataCal2 + fileFormat[i].dataCal1) / fileFormat[i].dataCal2)) * 1000);
      }
        
    }
    else if (fileFormat[i].dataType[0] == 'I')
    {
      if (fileFormat[i].dataUnit[0] == 'u')
      {
        measuredValues[i] = ((((sensorValues[i] * 3.3 / 1024.0) - fileFormat[i].dataCal2) * 1000) / fileFormat[i].dataCal1);
      }
      else if (fileFormat[i].dataUnit[0] == 'm')
      {
        measuredValues[i] = (((((sensorValues[i] * 3.3 / 1024.0) - fileFormat[i].dataCal2) * 1000) / fileFormat[i].dataCal1) * 1000);
      }
      
    }
    else if (fileFormat[i].dataType[0] == 'T')
    {
      if (fileFormat[i].dataAD == 'A')
      {
        
      }
      else if (fileFormat[i].dataAD == 'D')
      {
        measuredValues[i] = sensors.getTempCByIndex(0);
      }
      else
      {
        
      }

    }
    else if (fileFormat[i].dataType == "WS")
    {
      if (fileFormat[i].dataAD == 'A')
      {
        measuredValues[i] = ((sensorValues[i] *3.3 / 1024.0) / fileFormat[i].dataCal1);
      }
      else if (fileFormat[i].dataAD == 'D')
      {
        if (firstTimeWS == 1)
        {
          firstTimeWS = 0;
          pinMode(fileFormat[i].dataPin, INPUT);
          PCintPort::attachInterrupt(digitalPinToInterrupt(fileFormat[i].dataPin), pulse1_ISR, RISING);
        }
        else
        {
          measuredValues[i] = (cptBuff1 / fileFormat[i].dataCal1);     
        }
      }
      else
      {
       
      }
    }
    else if (fileFormat[i].dataType == "WV")
    {
      vane = ((sensorValues[i] * 3.3) / 1024.0);

      if ((vane <= 0.35) && (vane >= 0.25))
      {
        measuredValues[i] = 1.0;
      }
      else if ((vane < 0.7) && (vane >= 0.5))
      {
        measuredValues[i] = 2.2;
      }
      else if ((vane <= 0.85) && (vane >= 0.7))
      {
        measuredValues[i] = 3.3;
      }
      else if ((vane <= 0.1) && (vane >= 0.8))
      {
        measuredValues[i] = 3.9;
      }
      else if ((vane <= 1.9) && (vane >= 1.7))
      {
        measuredValues[i] = 8.2;
      }
      else if ((vane <= 2.1) && (vane >= 1.9))
      {
        measuredValues[i] = 16.0;
      }
      else if ((vane < 2.95) && (vane >= 2.8))
      {
        measuredValues[i] = 64.9;
      }
      else if ((vane <= 3.1) && (vane >= 2.95))
      {
        measuredValues[i] = 120.0;
      }
      else
      {
        
      }

    }
    else
    {
      
    }
  }
}

void writeHeaderOnFile()
{
  int i = 0;
  
  myFile = SD.open(pathMes, FILE_WRITE); 

  if (myFile){
    Serial.print("Writing...");
    myFile.print(rtc.getDateStr());
    myFile.print("\t");
    myFile.print(rtc.getTimeStr());
    
    for (i=0; i<=dataNumber; i++)
    {
      myFile.print("\t");
      myFile.print(fileFormat[i].dataName);
    }
  // close the file:
    myFile.close();
    Serial.println("done.");
  }
}

void writeDataOnFile() //parameters measuredValues, fileFormat, pathMes
{
  int i = 0;
  
  myFile = SD.open(pathMes, FILE_WRITE); 

  if (myFile){
    Serial.print("Writing...");
    myFile.print(rtc.getDateStr());
    myFile.print(",");
    myFile.print(rtc.getTimeStr());
    
    for (i=0; i<=dataNumber; i++)
    {
      myFile.print(",");
      myFile.print(fileFormat[i].dataName);
    }
    
    /*
    for (i=0; i<=dataNumber; i++)
    {
      myFile.print(",");
      
      myFile.print(" : ");
      if (fileFormat[i].dataType == "WV")
      {
        if (measuredValues[i] == 1.0)
          myFile.println("E");
        if (measuredValues[i] == 2.2)
          myFile.println("SE");
        if (measuredValues[i] == 3.3)
          myFile.println("N");
        if (measuredValues[i] == 3.9)
          myFile.println("S");
        if (measuredValues[i] == 8.2)
          myFile.println("NE");
        if (measuredValues[i] == 16.0)
          myFile.println("SW");
        if (measuredValues[i] == 64.9)
          myFile.println("NW");
        if (measuredValues[i] == 120.0)
          myFile.println("W");
      }
      else
      {
        myFile.print(measuredValues[i]);
      }

      myFile.print(",");

      if (fileFormat[i].dataType[0] == 'V')
      {
        if (fileFormat[i].dataUnit[0] == 'u')
        {
          myFile.println(" V");
        }
        else if (fileFormat[i].dataUnit[0] == 'm')
        {
          myFile.println(" mV");
        }
      }
      else if (fileFormat[i].dataType[0] == 'I')
      {
        if (fileFormat[i].dataUnit[0] == 'u')
        {
          myFile.println(" A");
        }
        else if (fileFormat[i].dataUnit[0] == 'm')
        {
          myFile.println(" mA");
        }
      }
      else if (fileFormat[i].dataType[0] == 'T')
      {
        myFile.println(" °C");
      }
      else if (fileFormat[i].dataType == "WS")
      {
        myFile.println(" m/s");
      }
      

    }
    myFile.println(" ");
    */
    // close the file:
    myFile.close();
    Serial.println("done.");
  }
}



