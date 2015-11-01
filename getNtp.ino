void getNtp() {                     // update the system clock

//   Serial.println();
//   Serial.println(F("UpdateNTPTime"));

   internetCtr++;

  mysntp.UpdateNTPTime();

//  Serial.println(F("Current local time is:"));

   mysntp.ExtractNTPTime(mysntp.NTPGetTime(&now2, true), &timeExtract);

//    Serial.print(timeExtract.hour); Serial.print(F(":")); Serial.print(timeExtract.min); Serial.print(F(":"));Serial.print(timeExtract.sec); Serial.print(F("."));Serial.println(timeExtract.millis);
//    Serial.print(pF(&dayStrs[timeExtract.wday])); Serial.print(F(", ")); Serial.print(pF(&monthStrs[timeExtract.mon])); Serial.print(F(" ")); Serial.print(timeExtract.mday); Serial.print(F(", "));Serial.println(timeExtract.year);
//    Serial.print(F("Day of year: ")); Serial.println(timeExtract.yday + 1); 

  int localHour;
  int myMonth = timeExtract.mon, myMonthDay = timeExtract.mday, myYear = timeExtract.year;     // used for setDate
  int myHour = timeExtract.hour, myMinute = timeExtract.min, mySecond = timeExtract.sec;      // used for setTime

  int beginDSTDay = (14 - (1 + myYear * 5 / 4) % 7);  
  int beginDSTMonth=3;
  int endDSTDay = (7 - (1 + myYear * 5 / 4) % 7);
  int endDSTMonth=11;
  int workMonth, workDay, workYear, workHour;

  localHour = myHour;
  if (((workMonth > beginDSTMonth) && (workMonth < endDSTMonth))
   || ((workMonth == beginDSTMonth) && (workDay > beginDSTDay))
   || ((workMonth == beginDSTMonth) && (workDay == beginDSTDay) && (myHour >= 2))
   || ((workMonth == endDSTMonth) && (workDay < endDSTDay))
   || ((workMonth == endDSTMonth) && (workDay == endDSTDay) && (myHour < 1))) {
        localHour++;
        }
  doy = timeExtract.yday + 1;
  mYhour = localHour;
  mYminute = timeExtract.min;
  mYsecond = timeExtract.sec;
  mYweekDay = timeExtract.wday;
  mYmonth = timeExtract.mon;
  mYmonthDay = timeExtract.mday;
  mYyear = timeExtract.year;
  setTime(mYhour, mYminute, mYsecond, mYmonthDay, mYmonth, mYyear);
#ifdef DEBUG
  Serial.print("Time has been set to ");
  Serial.print(hour()); Serial.print(":"); Serial.print(minute()); Serial.print(":"); Serial.print(second());
  Serial.print(" "); Serial.print(month()+1); Serial.print("/"); Serial.print(day()); Serial.print("/"); Serial.println(year());
#endif
}
