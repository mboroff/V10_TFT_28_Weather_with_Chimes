void displayTempgraphs()
{
//          display the temp high/low and humidity for the month
  int lowx = 10;
  int highy = 80; 
  drawMonthgraph(30, 280) ;

  while(1) {                             // pressure test aand timer loop will interrup for request to get weather upadte
     if (prevSec != mYsecond) {                  // display the time
         prevSec = mYsecond;       
         x = 95;
         y = 15;
         tft.setCursor(x, y);
         if (mYhour < 10 || (mYhour - 12) < 10){
             tft.print(F("0"));
             }
         if (mYhour < 13) {
             tft.print(mYhour);
             } else {
                     tft.print(mYhour - 12);
                     }
         tft.print(F(":"));
         if (mYminute < 10) tft.print(F("0"));
         tft.print(mYminute);
         tft.print(F(":"));
         if (mYsecond < 10) tft.print(F("0"));
         tft.print(mYsecond);
         }
    
      get_touch();
if (tsz > MINPRESSURE) {
   
//    Serial.print("Display temp graphs X = "); Serial.print(tsx);
//    Serial.print("\tDisplay temp graphs Y = "); Serial.print(tsy);
//    Serial.print("\tDisplay temp graphs Pressure = "); Serial.println(tsz);

        if (tsy > lowx && tsy < highy) {
          //Serial.print("tsx: "); Serial.println(tsx); 
            if (tsx < 80) {
                  mYmonth--;
//Serial.print("mYmonth: "); Serial.println(mYmonth); 
                  if (mYmonth < 0) {
                      mYmonth = 11;
                      }
              drawMonthgraph(30, 280) ;
              }
              if (tsx > 160) {
                  mYmonth++;
                  if (mYmonth > 11) {
                      mYmonth = 0;
                      }
                drawMonthgraph(30, 280) ;
                }
                
           }
        if (tsy > 150) {
            tsy = 0;
            tsz = 0;
            getTime();
            return;
            }
      }
      if (minute() ==  0 || minute() == 10 || minute() == 20 || 
          minute() == 30 || minute() == 40 || minute() == 50 ) {
          if (second() <10) {
              return;
              }
          } 

  }
}



