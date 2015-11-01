/*************************************************** 
  This code is based on an example for the 
  Adafruit CC3000 Wifi Breakout & Shield

  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
//#define DEBUG 1 
 
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include "sntp.h"
#include <Time.h>                          // time
#include <Adafruit_VS1053.h>              // MP3 card
#include <SD.h>                           // disc for bmps and music
#include "Adafruit_GFX.h"                 // Graphics library
#include <Wire.h>                         //  Touch sensor uses I2C
#include <DHT.h>                          // Temp sensor
#include <avr/wdt.h>


#include <Adafruit_TFTLCD.h>                  // Hardware-specific library
#include <Adafruit_STMPE610.h>                 // touch controller

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define TS_MINX 150                  //  map the screen point to the display
#define TS_MINY 120
#define TS_MAXX 3800
#define TS_MAXY 4000

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define MINPRESSURE 10
#define MAXPRESSURE 1000

Adafruit_STMPE610 touch = Adafruit_STMPE610();

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
                 // touch screen coordinates
uint16_t px, py;
uint8_t pz;
uint16_t tsx, tsy;
uint8_t tsz;

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "internet2.4"           // cannot be longer than 32 characters!
#define WLAN_PASS       "martylou9512"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  6000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

// What page to grab!
#define WEBSITE      "api.wunderground.com"
#define WEBPAGE2      "/api/f6d42935c5858b54/conditions/forecast/q/IL/Skokie.json"
// These can be any pins:
#define RESET 41      // formerly 9 VS1053 reset pin (output)
#define CS 40        // formerly 10  VS1053 chip select pin (output)
#define DCS 38        // formerly 8 VS1053 Data/command select pin (output)
#define CARDCS 43     // formeerly 4 Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 18       // formerly 3 VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(RESET, CS, DCS, DREQ, CARDCS);

#define DHTPIN 2     // what pin we're connected to Changed from 2

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
int dhtCtr = 0;

/**************************************************************************/
/*!
    @brief  Sets up the HW and the CC3000 module (called automatically
            on startup)
*/
/**************************************************************************/

uint32_t ip;
/**************************************************
          misc.   counters
***************************************************/

int menuCtr = 1;  // used in paging routines
int fileCtr = 0;  // number files on sd
int mp3Ctr;       // number of mp3 files on sd
int internetCtr = 0;  // enternet ccess count
int x, y;
unsigned long endTime;

/********************************************************
                time
********************************************************/

int dayOfYear;                         // time variables
int mYsecond;
int mYminute;
int mYhour;
int mYweekDay;
int mYmonthDay;
int mYmonth;
int mYyear;
int prevSec;
int prevMin;
int prevHour;
int prevDay;

/********************************************************
                                  Calendar
********************************************************/

int doy;

/***********************************************************
       booleans
************************************************************/

boolean fileButtons;
boolean lookingForwinddir = false;
boolean startQuote = false;
boolean lookingForhumidity = false;
boolean lookingFortemperaturestring = false;
boolean lookingForfahrenheit = false;
boolean lookingForfcttext = false;
boolean lookingFortitle = false;
boolean lookingForvisibilitymi = false;
boolean lookingForfeelslikef = false;
boolean lookingForfeelslikestring = false;
boolean lookingForweather = false;
boolean lookingForobservationtime = false;
boolean lookingFortemp_f = false;
boolean lookingFortemp_c = false;
boolean lookingForwind_mph = false;
boolean lookingForconditions = false;
boolean donotPlay = false;

/***************************************************
      Buffers
****************************************************/

/******************************************************
            Weather
******************************************************/

int l;
int wl;
int wdl;
int wmph;

String observationtime;
static char conditions0[40];
static char conditions1[40];
static char conditions2[40];
static char conditions3[40];
static char conditions4[40];
static char conditions5[40];
static char feelslikestring[25];
static char fahrenheit[8][10];
static char fcttext1[230];
static char fcttext2[230];
static char fcttext3[230];
static char fcttext4[230];
static char feelslikef[10];
static char humidity[20];
static char humidity2[10];
static char temperaturestring[25];
static char temp_f[7]; 
static char temp_c[7]; 
static char title[9][20];
static char visibilitymi[10];
static char weather[36];
static char winddir[10];
static char wind_mph[5];

static char weatherChars[19][36] = { "Light Drizzle", "Light Rain", "Heavy Rain", "Rain", 
                                     "Light Snow", "Heavy Snow", "Snow",  "Hail", 
                                     "Light Fog", "Heavy Fog", "Fog",  "Haze",
                                     "Heavy Thunderstorm",  "Thunderstorm", "Overcast", "Clear",  
                                     "Partly Cloudy", "Mostly Cloudy",  "Scattered Clouds"};


static int weatherBmps[19] = { 3, 3, 3, 3, 5, 8, 8,  11, 2, 2, 2, 6, 10, 10, 6, 9, 1, 1, 1};


/***************************************************************************
                          NTP
*****************************************************************************/

//Arguments to SNTP client constructor:
//	1 - Primary Network Time Server URL (can be NULL)
//	2 - Secondary Network Time Server URL (also can be NULL)
//	3 - Local UTC offset in minutes (US Eastern Time is UTC - 5:00
//	4 - Local UTC offset in minutes for Daylight Savings Time (US Eastern DST is UTC - 4:00
//	5 - Enable Daylight Savings Time adjustment (not implemented yet)
//
sntp mysntp = sntp(NULL, "time.nist.gov", (short)(-6 * 60), (short)(-6 * 60), true);

// Type SNTP_Timestamp is 64-bit NTP time. High-order 32-bits is seconds since 1/1/1900
//   Low order 32-bits is fractional seconds
SNTP_Timestamp_t now2;

// Type NetTime_t contains NTP time broken out to human-oriented values:
//	uint16_t millis; ///< Milliseconds after the second (0..999)
//	uint8_t	 sec;    ///< Seconds after the minute (0..59)
//	uint8_t	 min;    ///< Minutes after the hour (0..59)
//	uint8_t	 hour;   ///< Hours since midnight (0..23)
//	uint8_t	 mday;   ///< Day of the month (1..31)
//	uint8_t	 mon;    ///< Months since January (0..11)
//	uint16_t year;   ///< Year.
//	uint8_t	 wday;	 ///< Days since Sunday (0..6)
//	uint8_t	 yday;   ///< Days since January 1 (0..365)
//	bool	 isdst;  ///< Daylight savings time flag, currently not supported	
NetTime_t timeExtract;

#define pF(string_pointer) (reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(string_pointer)))

const prog_char   janStr[] PROGMEM = "January";
const prog_char   febStr[] PROGMEM = "February";
const prog_char   marStr[] PROGMEM = "March";
const prog_char   aprStr[] PROGMEM = "April";
const prog_char   mayStr[] PROGMEM = "May";
const prog_char   junStr[] PROGMEM = "June";
const prog_char   julStr[] PROGMEM = "July";
const prog_char   augStr[] PROGMEM = "August";
const prog_char   sepStr[] PROGMEM = "September";
const prog_char   octStr[] PROGMEM = "October";
const prog_char   novStr[] PROGMEM = "November";
const prog_char   decStr[] PROGMEM = "December"; 

PROGMEM const char* const monthStrs[] = { janStr, febStr, marStr, aprStr, mayStr, junStr,
                                          julStr, augStr, sepStr, octStr, novStr, decStr}; 

const prog_char   sunStr[] PROGMEM = "Sunday";
const prog_char   monStr[] PROGMEM = "Monday";
const prog_char   tueStr[] PROGMEM = "Tuesday";
const prog_char   wedStr[] PROGMEM = "Wednesday";
const prog_char   thuStr[] PROGMEM = "Thursday";
const prog_char   friStr[] PROGMEM = "Friday";
const prog_char   satStr[] PROGMEM = "Saturday"; 

PROGMEM const char* const dayStrs[] = { sunStr, monStr, tueStr,  wedStr,
                                        thuStr, friStr, satStr};


/*****************************************************************************
             clock stuff
*****************************************************************************/

int clockCenterX=120;   // Using 240 X 320 resolution
int clockCenterY=120;   // Center is offset to allow character lines of information
int circleSize = 80;

int xDiff = 0;
int yDiff = 0;
int roTation = 0;

int texTsize = 1;
int iNy = 210;
int timeDisplaYy = 15;
int dateDisplaYy = 5;     
int weatherTempHighDay[32];          // array for collecting the month's hgh and low temperatures
int weatherTempLowDay[32];

String wRmm;                         // variables from reading in the weather log
String wRdd;
String wRyyyy;
String wRhr;
String wRmin;
String wRsec;
String wRobTime;
String wRdesc;
String wRtempc;
String wRtempF;
String wRvisibility;
String wRwinddir;
String wRwindspeed;
int monthLow=200;
/*************************************************
          File
**************************************************/
File myFile;
File root;
int fileIndex = 0;
String fileSearch;
int startCol;
int xinCr;
int fileCols;
int fileRows;

#define MAXFILES 16
static char fileName[MAXFILES][13];

/************************************************
                    Setup
************************************************/
void setup(void)
{
  Serial.begin(115200);
  pinMode(53, OUTPUT);         // spi must be defined oupt  
  pinMode(43, OUTPUT);         // used for sd card
  digitalWrite(43,HIGH);


  tft.reset();                 // reset the tft display copied from Adafruit examples
  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
#ifdef DEBUG    
    Serial.println(F("Found ILI9325 LCD driver"));
#endif    
    } 
  else if(identifier == 0x9328) {
#ifdef DEBUG    
    Serial.println(F("Found ILI9328 LCD driver"));
#endif    
  } else if(identifier == 0x7575) {
#ifdef DEBUG    
    Serial.println(F("Found HX8347G LCD driver"));
#endif    
  } else if(identifier == 0x9341) {
#ifdef DEBUG    
    Serial.println(F("Found ILI9341 LCD driver"));
#endif    
  } else {
#ifdef DEBUG    
     Serial.print(F("Unknown LCD driver chip: "));
     Serial.println(identifier, HEX);
     Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
     Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
     Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
     Serial.println(F("If using the breakout board, it should NOT be #defined!"));
     Serial.println(F("Also if using the breakout, double-check that all wiring"));
     Serial.println(F("matches the tutorial."));
#endif     
     return;
     }

  tft.begin(identifier);          // Let's start the tft
  tft.setTextColor(WHITE, BLUE);  // all text is white over blue background
  tft.setRotation(roTation);       // using default rotation but could easily change. Would require adjustment to face and numbers
  tft.fillScreen(BLUE);           // clear the screen BLUE
  delay(500);
  x = 40;                            // Starting coordinates for setup messages
  y = 0;
  tft.setTextSize(2);
  tft.setCursor(x, y);
  tft.print(F("Hello World!"));
  x = 10;
  y = 20;
#ifdef DEBUG
  Serial.print("Screen "); Serial.print(tft.width());          // display the screen dimensions
  Serial.print(" X "); Serial.println(tft.height());
#endif
 tft.setCursor(x, y);
 tft.print("Screen Size "); 
 y = y + 20;   //40
  tft.setCursor(x, y); 
 tft.print(tft.width());
 tft.print(" X "); 
 tft.println(tft.height()); 
 y = y + 20;  //60
 
 if (! touch.begin()) {                                         // start the ts controller
 #ifdef DEBUG
    Serial.println("STMPE not found!");
#endif
    while(1);
  }

 tft.setCursor(x , y);
 tft.print(F("TS started"));
#ifdef DEBUG
  Serial.println(F("Touchscreen started"));
#endif
  y = y + 20; // 80                                            display free memory
  tft.setCursor(x, y);
  tft.print(F("Free RAM: ")); 
  tft.print(getFreeRam(), DEC);
  
  y = y + 20;  // 100
  tft.setCursor(x , y);
  tft.print(F("Start MP3"));                                 // start the MP3 card
 #ifdef DEBUG
  Serial.println("Adafruit VS1053 Simple Test");
#endif
  musicPlayer.begin(); // initialise the music player
#ifdef DEBUG
 Serial.print(F("Initializing SD card..."));
#endif
   if (!SD.begin(CARDCS)) {                       // using vs1053 sd card
 #ifdef DEBUG
       Serial.println("initialization failed!");
#endif       
       return;
       }
 #ifdef DEBUG       
   Serial.println("initialization done.");
#endif  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  // Play one file, don't return until complete                  used in testing
//  musicPlayer.playFullFile("track001.mp3");
  // musicPlayer.playFullFile("hour1.mp3");
  // Play another file in the background, REQUIRES interrupts!
//  musicPlayer.startPlayingFile("track002.mp3");
// mYhour = 13;
// playHourly();

//  Serial.println(F("Hello, CC3000!\n"));                               // start wi-fi card
//  Serial.print(F("Free RAM: ")); Serial.println(getFreeRam(), DEC); 
  //* Initialise the module 
//  Serial.println(F("\nInitializing..."));
 
  y = y + 20; //120
  tft.setCursor(x, y);
  tft.print(F("Begin CC3000"));

  if (!cc3000.begin())
  {
#ifdef DEBUG    
    Serial.println(F("Couldn't begin()! Check your wiring?"));
#endif    
    while(1);
  }
  
  if (!cc3000.begin())
  {
 #ifdef DEBUG    
    Serial.println(F("Couldn't begin()! Check your wiring?"));
#endif    
    while(1);
  }
#ifdef DEBUG  
  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
#endif  
  y = y + 20; // 140
  tft.setCursor(x, y);
  tft.print(F("Connecting to")); 
  y = y +20;  //160
  tft.setCursor(x, y); 
  tft.print(WLAN_SSID); 
  
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
 #ifdef DEBUG    
    Serial.println(F("Failed!"));
#endif    
    while(1);
  }
 #ifdef DEBUG   
  Serial.println(F("Connected!"));
#endif  
  y = y +20;  //180
  tft.setCursor(x, y);
  tft.print(F("Connected"));  
  y = y +20; //200
  tft.setCursor(x, y);
  tft.print(F("Requesting DHCP")); 
  //* Wait for DHCP to complete 
 #ifdef DEBUG  
  Serial.println(F("Request DHCP"));
#endif  
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  ip = 0;
   while (ip == 0) {
  // Try looking up the website's IP address
#ifdef DEBUG 
  Serial.print(WEBSITE); Serial.print(F(" -> "));
#endif  
 
    if (! cc3000.getHostByName(WEBSITE, &ip)) {
#ifdef DEBUG      
        Serial.println(F("Couldn't resolve!"));
#endif        
        cc3000.stop();
#ifdef DEBUG        
        Serial.println("RESET!");
        Serial.flush();
#endif        
        void(* resetFunc) (void) = 0; //declare reset function @ address 0
        resetFunc();  //call reset
    }
    delay(500);
  }

 // cc3000.printIPdotsRev(ip);
  
  tft.fillScreen(BLUE);                                           // start drawing the clock face and initial get time and weather
  tft.setTextSize(texTsize);
  getNtp();
  prevSec = 99;
  prevMin = mYminute;
  prevHour = mYhour;
  drawFace();
  if (!getWeb()) {                                              // if conncetion fails display a message
      tft.fillRect(0, 300, 240, 30, BLUE);
      tft.setCursor(60, 305);
      tft.print(F("Connection failed"));
      delay(10000);
  }else {
         displayWeather(); 
  }
}

void loop(void)
{
     get_touch();     // check for touch

     if (tsz > MINPRESSURE) {          // minimum pressure means someone touched screen
        optionsMenu();                // display optional apps
        tsz = 0;
        drawFace();                  // clear screen and display clock
        displayWeather();
        prevDay = 99;
        }
     if (hour() == 0 && minute() == 0 && second() == 0) {
#ifdef DEBUG       
        Serial.println("RESET!");
        Serial.flush();
#endif        
        void(* resetFunc) (void) = 0; //declare reset function @ address 0
        resetFunc();  //call reset
        }       
     if (minute() == 55 && second() < 2) {          //  on the hour play westminester chimes
         getNtp();
     }
     if (minute() == 0 && second() < 2) {          //  on the hour play westminester chimes
         playHourly();
         donotPlay = true;
         if (!getWeb()) {                         // get weather info
            tft.fillRect(0, 300, 240, 30, BLUE);
            tft.setCursor(60, 305);
            tft.print(F("Connection failed"));
            delay(10000);
#ifdef DEBUG            
            Serial.println("RESET!");
            Serial.flush();
#endif            
            void(* resetFunc) (void) = 0; //declare reset function @ address 0
            resetFunc();  //call reset
            }else {
                   displayWeather(); 
                  }
         prevDay = 99;
         printDate();
         }
      if (minute() == 10 || minute() == 20 || minute() == 30 ||  // every ten minutes get weather update
          minute() == 40 || minute() == 50) {
          if (second()  < 2) {
              donotPlay = false;
              if (!getWeb()) {  
                  tft.fillRect(0, 300, 240, 30, BLUE);
                  tft.setCursor(60, 305);
                  tft.print(F("Connection failed"));
                  delay(10000);
#ifdef DEBUG                  
                  Serial.println("RESET!");
                  Serial.flush();
#endif            
                  void(* resetFunc) (void) = 0; //declare reset function @ address 0
                  resetFunc();  //call reset
                  }else {
                         displayWeather(); 
                         }
              }
          }
      getTime();
      if (prevSec != mYsecond) {                            // draw the hour minute second hands once a second
          printDate(); 
          drawSec();
          drawHour();
          drawMin();
          displayInsidetemp();
          prevSec = mYsecond;
      }
}

void getTime() {                  //  Systemclock updated by ntp request easy to switch to rtc      
                                 //  also used if time event was detected and I want to freeze time
  mYsecond = second();           //  so everything uses saame hour min and second
  mYminute = minute();
  mYhour = hour();
  mYweekDay = weekday();
  mYmonthDay = day();
  mYmonth = month();
  mYyear = year();

  }
// helper function to determine free ram at runtime
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

