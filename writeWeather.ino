void writeWeather()
{
    switch (month()+1) {                                  // which month to log 
    case 1:
//       Serial.println(F("Writing to jan.txt"));  
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("jan.txt")) SD.remove("jan.txt");
        }
        myFile = SD.open("jan.txt", FILE_WRITE);
        break;
    case 2:
//       Serial.println(F("Writing to feb.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("feb.txt")) SD.remove("feb.txt");
        }
        myFile = SD.open("feb.txt", FILE_WRITE);
        break; 
    case 3:
//       Serial.println(F("Writing to march.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("march.txt")) SD.remove("march.txt");
        }
        myFile = SD.open("march.txt", FILE_WRITE);
        break;
    case 4:
//       Serial.println(F("Writing to april.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("april.txt")) SD.remove("april.txt");
        }
        myFile = SD.open("april.txt", FILE_WRITE);
        break;
    case 5:
//       Serial.println(F("Writing to may.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("may.txt")) SD.remove("may.txt");
        }
        myFile = SD.open("may.txt", FILE_WRITE);
        break;
    case 6:
//       Serial.println(F("Writing to june.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("june.txt")) SD.remove("june.txt");
        }
        myFile = SD.open("june.txt", FILE_WRITE);
        break;
    case 7:
//       Serial.println(F("Writing to july.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("july.txt")) SD.remove("july.txt");
        }
        myFile = SD.open("july.txt", FILE_WRITE);
        break;
    case 8:
//       Serial.println(F("Writing to aug.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("aug.txt")) SD.remove("aug.txt");
        }
        myFile = SD.open("aug.txt", FILE_WRITE);
        break;
    case 9:
///       Serial.println(F("Writing to sept.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("sept.txt")) SD.remove("sept.txt");
        }
        myFile = SD.open("sept.txt", FILE_WRITE);
        break;
    case 10:
//       Serial.println(F("Writing to oct.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("oct.txt")) SD.remove("oct.txt");
        }
        myFile = SD.open("oct.txt", FILE_WRITE);
        break;
    case 11:
//       Serial.println(F("Writing to nov.txt"));
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("nov.txt")) SD.remove("nov.txt");
        }
        myFile = SD.open("nov.txt", FILE_WRITE);
        break;
    case 12:
//       Serial.println(F("Writing to dec.txt"));    
        if (mYmonthDay == 1 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("dec.txt")) SD.remove("dec.txt");
        }
        myFile = SD.open("dec.txt", FILE_WRITE);
        break;
    default:
//       Serial.println(F("Writing to weather.txt"));
        if (mYmonth == 0 && mYhour == 0 && mYminute == 0) {
             if (SD.exists("weather.txt")) SD.remove("weather.txt");
        }
        myFile = SD.open("weather.txt", FILE_WRITE);
   }
   //-------------------   writing weather info to SD ----------------
if (sizeof(temp_f) > 0) {   
  if (mYmonth < 10) myFile.print(F("0")); myFile.print(mYmonth);  myFile.print(F("/")); 
  if (mYmonthDay < 10) myFile.print(F("0")); myFile.print(mYmonthDay);  myFile.print(F("/"));  
  myFile.print(mYyear); myFile.print(F(","));
  if (mYhour < 10) myFile.print(F("0")); myFile.print(mYhour);  myFile.print(F(":"));  
  if (mYminute < 10) myFile.print(F("0")); myFile.print(mYminute);  myFile.print(F(":")); 
  if (mYsecond < 10) myFile.print(F("0")); myFile.print(mYsecond);

  myFile.print(F(","));               
  myFile.print(mYhour); 
  myFile.print(F(":")); 
  myFile.print(mYminute); 
  myFile.print(F(" "));
  if (mYhour < 12) {
      myFile.print(F("AM"));
  } else {
    myFile.print(F("PM"));
  }
  myFile.print(F(","));
  myFile.print(humidity);
  myFile.print(F(","));
  myFile.print(weather);  
  myFile.print(F(","));
  myFile.print(temp_c);   
  myFile.print(F(","));
  myFile.print(temp_f);  
  myFile.print(F(","));
  myFile.print(visibilitymi);  
  myFile.print(F(","));
  myFile.print(winddir);  
  myFile.print(F(","));
  myFile.println(wind_mph);  
}
  myFile.close();
}
