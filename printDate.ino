void printDate(){
  //print the date EG   3/1/11 23:59:59
  getTime();
  texTx = 105;
  texTy = 20;
  tft.setCursor(texTx, texTy);
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
      texTx = 5;
      texTy = dateDisplaYy;
      tft.setCursor(texTx, texTy);
      tft.print(pF(&monthStrs[timeExtract.mon]));
      tft.print(F(" "));
      if (mYmonthDay < 10) tft.print("0");
      tft.print(mYmonthDay);
      tft.print(F(", "));
      tft.print(mYyear);
      texTx = 105;
      tft.setCursor(texTx, texTy);
      tft.print(pF(&dayStrs[timeExtract.wday]));
      tft.print(F("    "));
      texTx = 190;
      tft.setCursor(texTx, texTy);
      tft.print(F("Day "));
      tft.print(doy);
  }
}  

