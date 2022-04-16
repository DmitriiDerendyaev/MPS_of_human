
#include <SPI.h>
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_ST7735.h>   // include Adafruit ST7735 TFT library
#include "RTClib.h"            // include Adafruit RTC library
#include <Wire.h>
 
#define TFT_RST   5      // TFT RST pin is connected to arduino pin 8,
#define TFT_CS    6      // TFT CS  pin is connected to arduino pin 9,
#define TFT_DC    7     // TFT DC  pin is connected to arduino pin 10,
// initialize ST7735 TFT library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
 
// initialize RTC library
RTC_DS1307 rtc;
DateTime   now;
 
// buttons definition
#define button1    3     // button B1 is connected to Arduino pin 7
#define button2    4     // button B2 is connected to Arduino pin 6
#define button_sos  2     // button B3 is connected to Arduino pin 2
#define button_res  8     // button B4 is connected to Arduino pin 8

unsigned long timing; // Переменная для хранения точки отсчета
 
void setup(void)
{
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button_sos, INPUT_PULLUP);
  pinMode(button_res, INPUT_PULLUP);
 
  rtc.begin();   // initialize RTC chip
 
  tft.initR(INITR_BLACKTAB);     // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);  // fill screen with black color
  tft.drawRect(0, 0, 64, 26, ST7735_BLUE); // прямоугольник
  tft.drawRect(64, 0, 128, 26, ST7735_BLUE); // прямоугольник
  tft.drawRect(0, 26, 100, 26, ST7735_BLUE); // прямоугольник
  tft.drawRect(100, 26, 128, 26, ST7735_BLUE); // прямоугольник
  tft.drawRect(0, 52, 129, 52, ST7735_BLUE); // прямоугольник
  tft.drawRect(0, 133, 64, 160, ST7735_BLUE); // прямоугольник
  tft.drawRect(64, 133, 129, 160, ST7735_BLUE); // прямоугольник
  
  //tft.drawFastHLine(0, 44,  tft.width(), ST7735_BLUE);    // draw horizontal blue line at position (0, 44)
  //tft.drawFastHLine(0, 53, tft.width(), ST7735_BLUE);    // draw horizontal blue line at position (0, 53)
 
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);     // set text color to white and black background
  tft.setTextSize(1);                 // text size = 1
  tft.setCursor(4, 10);               // move cursor to position (4, 10) pixel
  tft.print("BAT: ");                    // вывод BAT + function
  tft.setCursor(70, 10);              // move cursor to position (70, 10) pixel
  tft.print("GSM: ");
  tft.setTextSize(2);                 // text size = 2
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);     // set text color to magneta and black background
  tft.setCursor(2, 33);               // move cursor to position (4, 30) pixel
  tft.print("MONITOR:");
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);     // set text color to magneta and black background
  tft.setCursor(102, 33);               // move cursor to position (4, 30) pixel
  tft.print("OK");                     // вывод содержимого переменной общего состояния устройства
  tft.setTextSize(2);                 // text size = 2
  tft.setTextColor(ST7735_MAGENTA, ST7735_BLACK);     // set text color to magneta and black background
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);     // set text color to magneta and black background
  tft.setCursor(15, 140);               // move cursor to position (4, 30) pixel
  tft.print("SET");
  tft.setCursor(80, 140);               // move cursor to position (4, 30) pixel
  tft.print("SEL");
  /*
  tft.setCursor(37, 112);             // move cursor to position (37, 112) pixel
  tft.print("TIME:");
  */
}


// a small function for button1 (B1) debounce
bool debounce ()
{
  byte count = 0;
  for(byte i = 0; i < 5; i++)
  {
    if ( !digitalRead(button1) )
      count++;
    delay(10);
  }
 
  if(count > 2)  return 1;
  else           return 0;
}
 
void RTC_display()
{
  char _buffer[11];
  char dow_matrix[7][10] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
  byte x_pos[7] = {29, 29, 23, 11, 17, 29, 17};
  static byte previous_dow = 8;


  // print day of the week
  if( previous_dow != now.dayOfTheWeek() )
  {
    previous_dow = now.dayOfTheWeek();
    tft.fillRect(11, 55, 108, 14, ST7735_BLACK);     // draw rectangle (erase day from the display)
    tft.setCursor(x_pos[previous_dow], 59);
    tft.setTextColor(ST7735_CYAN, ST7735_BLACK);     // set text color to cyan and black background
    tft.print( dow_matrix[now.dayOfTheWeek()] );
  }
  // print date

  sprintf( _buffer, "%02u-%02u-%04u", now.day(), now.month(), now.year() );
  tft.setCursor(4, 79);
  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);     // set text color to yellow and black background
  tft.print(_buffer);
  // print time
  sprintf( _buffer, "%02u:%02u:%02u", now.hour(), now.minute(), now.second() );
  tft.setCursor(16, 110);
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);     // set text color to green and black background
  tft.print(_buffer);
}
 
byte edit(byte parameter)
{
  static byte i = 0, y_pos,
              x_pos[5] = {4, 40, 100, 16, 52};
  char text[3];
  sprintf(text,"%02u", parameter);
 
  if(i < 3) {
    tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);     // set text color to green and black background
    y_pos = 79;
  }
  else {
    tft.setTextColor(ST7735_GREEN, ST7735_BLACK);     // set text color to yellow and black background
    y_pos = 136;
  }
 
  while( debounce() );   // call debounce function (wait for B1 to be released)
 
  while(true) {
    while( !digitalRead(button2) ) {  // while B2 is pressed
      parameter++;
      if(i == 0 && parameter > 31)    // if day > 31 ==> day = 1
        parameter = 1;
      if(i == 1 && parameter > 12)    // If month > 12 ==> month = 1
        parameter = 1;
      if(i == 2 && parameter > 99)    // If year > 99 ==> year = 0
        parameter = 0;
      if(i == 3 && parameter > 23)    // if hours > 23 ==> hours = 0
        parameter = 0;
      if(i == 4 && parameter > 59)    // if minutes > 59 ==> minutes = 0
        parameter = 0;
 
      sprintf(text,"%02u", parameter);
      tft.setCursor(x_pos[i], y_pos);
      tft.print(text);
      delay(200);       // wait 200ms
    }
 
    tft.fillRect(x_pos[i], y_pos, 22, 14, ST7735_BLACK);
    unsigned long previous_m = millis();
    while( (millis() - previous_m < 250) && digitalRead(button1) && digitalRead(button2)) ;
    tft.setCursor(x_pos[i], y_pos);
    tft.print(text);
    previous_m = millis();
    while( (millis() - previous_m < 250) && digitalRead(button1) && digitalRead(button2)) ;
 
    if(!digitalRead(button1))
    {                     // if button B1 is pressed
      i = (i + 1) % 5;    // increment 'i' for the next parameter
      return parameter;   // return parameter value and exit
    }
  }
}

void times()
{
  if( !digitalRead(button1) )  // if B1 is pressed
  if( debounce() )             // call debounce function (make sure B1 is pressed)
  {
    while( debounce() );  // call debounce function (wait for B1 to be released)
 
    byte day    = edit( now.day() );          // edit date
    byte month  = edit( now.month() );        // edit month
    byte year   = edit( now.year() - 2019 );  // edit year
    byte hour   = edit( now.hour() );         // edit hours
    byte minute = edit( now.minute() );       // edit minutes
 
    // write time & date data to the RTC chip
    rtc.adjust(DateTime(2000 + year, month, day, hour, minute, 0));
 
    while(debounce());  // call debounce function (wait for button B1 to be released)
  }

  now = rtc.now();  // read current time and date from the RTC chip
 
  RTC_display();   // diaplay time & calendar
  delay(100);      // wait 100ms
}

void week()
{
  char _buffer[11];
  char dow_matrix[7][10] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
  byte x_pos[7] = {29, 29, 23, 11, 17, 29, 17};
  static byte previous_dow = 8;
  
    previous_dow = now.dayOfTheWeek();
    tft.fillRect(11, 55, 108, 14, ST7735_BLACK);     // draw rectangle (erase day from the display)
    tft.setCursor(x_pos[previous_dow], 59);
    tft.setTextColor(ST7735_CYAN, ST7735_BLACK);     // set text color to cyan and black background
    tft.print( dow_matrix[now.dayOfTheWeek()] );
}

void sos()
{
  tft.fillRect(0, 0, 128, 160, ST7735_BLACK);
  tft.setCursor(20, 10);               // move cursor to position (4, 30) pixel
  tft.setTextSize(3);                 // text size = 2
  tft.setTextColor(ST7735_RED, ST7735_BLACK);     // set text color to magneta and black background
  tft.print("!SOS!");
  tft.setCursor(15, 45);               // move cursor to position (4, 30) pixel
  tft.setTextSize(2,3);                 // text size = 2
  tft.print("CALL:112");
  tft.setTextSize(2);                 // text size = 2
  tft.drawRect(0, 0, 129, 40, ST7735_BLUE); // прямоугольник
  tft.drawRect(0, 70, 129, 60, ST7735_BLUE); // прямоугольник
  tft.drawLine(0, 100, 129, 100, ST7735_BLUE); // прямоугольник
  
  /*
  tft.fillRect(0, 0, 30, 40, ST7735_BLUE);     // draw rectangle (erase day from the display)
  tft.fillRect(95, 0, 129, 40, ST7735_BLUE);     // draw rectangle (erase day from the display)
  tft.fillRect(95, 0, 129, 40, ST7735_BLUE);     // draw rectangle (erase day from the display)
  */
  
}
 
void loop()
{
  if( !digitalRead(button_sos))
  {
    sos();
  }
  else
  {
    times();
  }

  if( !digitalRead(button_res))
  {
    setup();
    week();
  }
  else
  {
    times();
  }
   
}
 
// end of code.
