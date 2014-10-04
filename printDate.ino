void printDate(){
  //print the date EG   3/1/11 23:59:59
  getTime();
  x = 105;
  y = 20;
  tft.setCursor(x, y);
  int wrkHr;
  wrkHr = mYhour;
  if (mYhour < 12){
      wrkHr = mYhour;
      }  else { 
               if (mYhour > 12) {
                   wrkHr = mYhour - 12;
                   }
      }
      if (wrkHr == 0){
          wrkHr = 12;
          }
      tft.print(wrkHr);
      tft.print(F(":"));
      if (mYminute < 10) tft.print(F("0"));
      tft.print(mYminute);
      tft.print(F(":"));
      if (mYsecond < 10) tft.print(F("0"));
      tft.print(mYsecond);
      tft.print(F(" "));
   
  if (mYmonthDay != prevDay) {                                     // If the date has changed Erase the previous date display
      prevDay = mYmonthDay;                                       // and print the new date
      x = 5;
      y = dateDisplaYy;
      tft.setCursor(x, y);
      tft.print(pF(&monthStrs[timeExtract.mon]));
      tft.print(F(" "));
      if (mYmonthDay < 10) tft.print("0");
      tft.print(mYmonthDay);
      tft.print(F(", "));
      tft.print(mYyear);
      tft.print(" ");
      x = 105;
      tft.setCursor(x, y);
      tft.print(pF(&dayStrs[timeExtract.wday]));
      tft.print(F("    "));
      x = 190;
      tft.setCursor(x, y);
      tft.print(F("Day "));
      tft.print(doy);
  }
}  

