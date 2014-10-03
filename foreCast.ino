void foreCast() {

 tft.fillScreen(BLUE);   
 tft.fillRect(0, 0, 240, 26, WHITE);                     // forecast is today plus three days
 tft.setCursor(80, 10);
 tft.setTextColor(BLACK, WHITE);
 tft.print(F("FORECAST "));  
 tft.setTextColor(WHITE, BLUE);
 y = 40;
 tft.setCursor(0, y);
 tft.print(title[1]);                                      // today
 tft.print(F(" ")); 
 tft.print(fahrenheit[0]);
 tft.print(F("/")); 
 tft.print(fahrenheit[1]); 
 tft.print(F(" ")); 
 tft.print(conditions1);
 y = y +20;
 tft.setCursor(0, y);
 tft.print(fcttext1);
 y = y + 50;
 
 tft.setCursor(0, y);                                    // tomorrow
 tft.print(title[3]); 
 tft.print(F(" ")); 
 tft.print(fahrenheit[2]); 
 tft.print(F("/")); 
 tft.print(fahrenheit[3]); 
 tft.print(F(" ")); 
 tft.print(conditions2);
 y = y +20;
 tft.setCursor(0, y);
 tft.print(fcttext2);
 y = y + 50;
 
 tft.setCursor(0, y);                                 // day after tomorrow
 tft.print(title[5]);  
 tft.print(F(" ")); 
 tft.print(fahrenheit[4]); 
 tft.print(F("/")); 
 tft.print(fahrenheit[5]); 
 tft.print(F(" ")); 
 tft.print(conditions3);
 y = y +20;
 tft.setCursor(0, y);
 tft.print(fcttext3);
 y = y + 50;
 

 tft.setCursor(0, y);                           // 2 days after tomorrow
 tft.print(title[7]); 
 tft.print(F(" ")); 
 tft.print(fahrenheit[6]); 
 tft.print(F("/")); 
 tft.print(fahrenheit[7]); 
 tft.print(F(" ")); 
 tft.print(conditions4);
 y = y +20;
 tft.setCursor(0, y);
 tft.print(fcttext4);

    while (1) {
      if (prevSec != second()) {          // if it is a different second than the previous do the clock thing
          prevSec = second();
          tft.setTextColor(BLACK, WHITE);
        /* time of day */
          tft.setCursor(150, 10);
          int tempHr;
          if (hour() > 12) {
              tempHr = hour() - 12;
              }
          else {
                tempHr = hour();
                }
         if (hour() == 0) {
             tempHr = 12;
             }    
         if (tempHr < 10) {
             tft.print(F("0"));
             }
         tft.print(tempHr);
         tft.print(F(":"));
         if (minute() < 10) {
            tft.print(F("0"));
            }
         tft.print(minute());
         tft.print(F(":"));
         if (second() < 10) {
             tft.print(F("0"));
             }
         tft.print(second());
         if (hour() > 11) {
             tft.print(F(" P.M. "));
             }
         else {
               tft.print(F(" A.M. "));
               }
          tft.setTextColor(WHITE, BLUE);
      if (minute() ==  0 || minute() == 10 || minute() == 20 || 
          minute() == 30 || minute() == 40 || minute() == 50 ) {
            return;
          } 
      get_touch();
      if (tsz > MINPRESSURE) {
 //     Serial.print("Forecast menu X = "); Serial.print(tsx);
 //     Serial.print("\tForecast menu Y = "); Serial.println(tsy);
 //     Serial.print("\tForecast menu Pressure = "); Serial.println(tsz);
          return;
           }
      }
      tsz = 0;
  
    }
}
