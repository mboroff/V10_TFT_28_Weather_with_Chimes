void getNtp() {                     // update the system clock
   Serial.println();
   Serial.println(F("UpdateNTPTime"));
   internetCtr++;
  mysntp.UpdateNTPTime();

  Serial.println(F("Current local time is:"));
  mysntp.ExtractNTPTime(mysntp.NTPGetTime(&nnow, true), &timeExtract);

  Serial.print(timeExtract.hour); Serial.print(F(":")); Serial.print(timeExtract.min); Serial.print(F(":"));Serial.print(timeExtract.sec); Serial.print(F("."));Serial.println(timeExtract.millis);
  Serial.print(pF(&dayStrs[timeExtract.wday])); Serial.print(F(", ")); Serial.print(pF(&monthStrs[timeExtract.mon])); Serial.print(F(" ")); Serial.print(timeExtract.mday); Serial.print(F(", "));Serial.println(timeExtract.year);
  Serial.print(F("Day of year: ")); Serial.println(timeExtract.yday + 1); 
  doy = timeExtract.yday + 1;
  mYhour = timeExtract.hour;
  mYminute = timeExtract.min;
  mYsecond = timeExtract.sec;
  mYweekDay = timeExtract.wday;
  mYmonth = timeExtract.mon;
  mYmonthDay = timeExtract.mday;
  mYyear = timeExtract.year;
  setTime(mYhour, mYminute, mYsecond, mYmonthDay, mYmonth, mYyear);
  Serial.print("Time has been set to ");
  Serial.print(hour()); Serial.print(":"); Serial.print(minute()); Serial.print(":"); Serial.print(second());
  Serial.print(" "); Serial.print(month()+1); Serial.print("/"); Serial.print(day()); Serial.print("/"); Serial.println(year());
}
