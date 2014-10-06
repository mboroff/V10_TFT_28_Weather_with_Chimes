bool getWeb(void) {
    
 String buff;
 int titleCtr = 0;
 int precipCtr = 0;
 int weatherCodeCtr = 0;
 int windspeedMilesCtr = 0;
 int winddir16PointCtr = 0;
 int fahrenheitCtr = 0;
 int tempMaxCCtr = 0;
 int tempMaxFCtr = 0;
 int fcttextCtr = 0;
 int conditionsCtr = 0;
 int tempMinCCtr = 0;
 int tempMinFCtr = 0;
 int weatherHourCtr = 0;
 int weatherMinuteCtr = 0;
 
 internetCtr++;  
 tft.fillRect(0, 280, 240, 40, BLUE);
 tft.setCursor(60, 285);
 tft.print(F("Free RAM: ")); 
 tft.print(getFreeRam(), DEC);
 tft.setCursor(60, 295);
 tft.print(F("Getting Weather Info"));
 uint32_t startTime = millis();
 endTime = 0;
  /* Try connecting to the website.
     Note: HTTP/1.1 protocol is used to keep the server from closing the connection before all data is read.
  */
  Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);
 
              if (www.connected()) {
                  www.fastrprint(F("GET "));
                  www.fastrprint(WEBPAGE2);
                  www.fastrprint(F(" HTTP/1.1\r\n"));
                  www.fastrprint(F("Host: ")); www.fastrprint(WEBSITE); www.fastrprint(F("\r\n"));
                  www.fastrprint(F("\r\n"));
                  www.println();
                  } else {
                           tft.fillRect(0, 300, 240, 30, BLUE);
                           tft.setCursor(60, 305);
                           tft.print(F("Connection failed"));
                           Serial.println(F("Connection failed"));  
                           Serial.flush();
                           return false;
//                          www.close();
//                          cc3000.stop();
//                          Serial.println("RESET!");
//                          Serial.flush();
//                          void(* resetFunc) (void) = 0; //declare reset function @ address 0
//                          resetFunc();  //call reset
                          }
//  Serial.println();
//  Serial.println(F("-------------------------------------"));


  /* Read data until either the connection is closed, or the idle timeout is reached. */ 
  unsigned long lastRead = millis();
  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    while (www.available()) {
      char c = www.read();
      Serial.print(c);
      lastRead = millis();
      if (c == '"') {
          if (startQuote == false) {
              startQuote = true;
              buff = "";
          }
        else  {
                   if (startQuote == true) {
                       startQuote = false;
                       if (lookingForobservationtime == true) {
                           lookingForobservationtime = false; 
                           l = buff.length();
                           observationtime = "";
                           observationtime = buff.substring(0, l-6);
//                           Serial.println(); Serial.println(observationtime); Serial.println(buff);
                           buff = "";                         
                           }
                       else                         
                       if (buff == String("local_time_rfc822")){
                           lookingForobservationtime = true;
                           buff = "";      
                           }
                        else
                        if (lookingForweather == true) {
                            lookingForweather = false; 
                            l = buff.length();
                            wl = l;
                            buff.toCharArray(weather, l+1);
//                                 Serial.println(); Serial.println(weather); Serial.println(buff);
                            buff = "";
                            }
                        else                         
                        if (buff == String("weather")){
                            lookingForweather = true;
                            buff = "";
                            }
                        else
                        if (lookingFortemp_f == true) {
                            lookingFortemp_f = false; 
                            String temp_temp;
                            int index;
                            index = buff.indexOf(",");
                            temp_temp = buff.substring(1,index);
                            temp_temp.toCharArray(temp_f, 3);
//                                 Serial.println(); Serial.println(temp_f); Serial.println(buff);
                            buff = "";
                            startQuote = true;
                            }
                        else
                        if (buff == String("temp_f")){
                            buff = "";  
                            lookingFortemp_f = true;                         
                            startQuote = true;
                            }                  
                       else
                       if (lookingFortemp_c == true) {
                            lookingFortemp_c = false; 
                            String temp_temp;
                            int index;
                            index = buff.indexOf(",");
                            temp_temp = buff.substring(1,index);
                            temp_temp.toCharArray(temp_c, 3);
//                                 Serial.println(); Serial.println(temp_f); Serial.println(buff);
                            buff = "";
                            startQuote = true;
                            }
                        else
                        if (buff == String("temp_c")){
                            buff = "";  
                            lookingFortemp_c = true;                         
                            startQuote = true;
                            }                  
                        else
                        if (lookingFortemperaturestring == true) {
                            lookingFortemperaturestring = false; 
                            l = buff.length();
                            buff.toCharArray(temperaturestring, l+1);
//                         Serial.println(buff);
//                         Serial.print("buff length = "); Serial.println(l);
                           buff = "";                         
                           }
                        else
                        if (buff == String("temperature_string")){
                           lookingFortemperaturestring = true;
//                         Serial.print(buff);    Serial.print(F(" "));
                           buff = "";
                           }
                        else 
                        if (lookingForfahrenheit == true) {
                            lookingForfahrenheit = false; 
                            l = buff.length();
                            buff.toCharArray(fahrenheit[fahrenheitCtr], l+1);
                           fahrenheitCtr++;
//                         Serial.println(buff);
//                         Serial.print("buff length = "); Serial.println(l);
                           buff = "";                         
                           }
                        else
                        if (buff == String("fahrenheit")){
                            lookingForfahrenheit = true;
//                         Serial.print(buff);    Serial.print(F(" "));
                            buff = "";
                            }
                        else                    
                        if (lookingForwind_mph == true) {
                            lookingForwind_mph = false; 
                            String wind_temp;
                            int index = buff.indexOf(",");
                            wind_temp = buff.substring(1,index);
                            l = wind_temp.length();
                            wind_temp.toCharArray(wind_mph, l+1);
//                                 Serial.println(); Serial.println(wind_mph); Serial.println(buff);
                            buff = "";
                            startQuote = true;
                            }
                        else                             
                        if (buff == String("wind_mph")){
                            buff = "";
                            lookingForwind_mph = true;
                            startQuote = true;
                            }
                        else
                        if (lookingForhumidity == true) {
                            lookingForhumidity = false; 
                            l = buff.length();
                            buff.toCharArray(humidity, l+1);
//                         Serial.println(buff); 
//                         Serial.print("buff length = "); Serial.println(l);
                            buff = "";                         
                           }
                       else                         
                       if (buff == String("relative_humidity")){
                           lookingForhumidity = true;
//                         Serial.print(buff);   Serial.print(F(" "));
                           buff = "";
                           }
                       else
                       if (lookingForwinddir == true) {
                           lookingForwinddir = false; 
                           l = buff.length();
                           buff.toCharArray(winddir, l+1);
//                           Serial.println(buff);
//                           Serial.print("buff length = "); Serial.println(l);
                           buff = "";
                           }
                       else
                       if (buff == String("wind_dir")){
                           lookingForwinddir = true;
//                          Serial.print(buff);    Serial.print(F(" "));
                           buff = "";                         
                           }
                       else 
                       if (lookingForfeelslikestring == true) {
                           lookingForfeelslikestring = false; 
                           l = buff.length();
                           buff.toCharArray(feelslikestring, l+1);
//                         Serial.println(buff);
//                         Serial.print(buff); Serial.print(F(" ")); 
                           buff = "";
                           }
                       else                         
                       if (buff == String("feelslike_string")){
                           lookingForfeelslikestring = true;
//                         Serial.print(buff);  Serial.print(F(" "));
                           buff = "";
                           }
                       else
                       if (lookingForfeelslikef == true) {
                           lookingForfeelslikef = false; 
                           l = buff.length();
                           buff.toCharArray(feelslikef, l+1);
//                         Serial.println(buff); 
//                         Serial.print("buff length = "); Serial.println(l);
                           buff = "";
                           }
                       else                         
                       if (buff == String("feelslike_f")){
                           lookingForfeelslikef = true;
//                         Serial.print(buff);  Serial.print(F(" "));
                           buff = "";
                           }
                       else
                       if (lookingForvisibilitymi == true) {
                           lookingForvisibilitymi = false; 
                           l = buff.length();
                           buff.toCharArray(visibilitymi, l+1);
//                         Serial.println(buff);
//                         Serial.print("buff length = "); Serial.println(l);                         
                           buff = "";
                           }
                       else                         
                       if (buff == String("visibility_mi")){
                           lookingForvisibilitymi = true;
//                         Serial.print(buff);  Serial.print(F(" "));
                           buff = "";
                           }
                       else
                       if (lookingFortitle == true) {
                           lookingFortitle = false; 
                           l = buff.length();
//                         Serial.println(buff);
//                         Serial.print("buff length = "); Serial.println(l);
                           buff.toCharArray(title[titleCtr], l+1);
                           titleCtr++;
                           buff = "";
                           }
                       else
                       if (buff == String("title")){
                           lookingFortitle = true;
//                         Serial.print(buff);    Serial.print(F(" "));
                           buff = "";
                           }
                        else
                             if (lookingForfcttext == true) {
                                 lookingForfcttext = false; 
                                 l = buff.length();
                                 if (l > 230) {
                                     l = 230;
                                 } 
// Serial.println();  Serial.print("fcttextCtr: "); Serial.print(fcttextCtr); Serial.print(" L: "); Serial.print(l); Serial.print(" buff: "); Serial.print(buff);  
                                 if (fcttextCtr ==0) {
                                     buff.toCharArray(fcttext1, l);
// Serial.println();                   Serial.print(" fcttext1: ");Serial.println(fcttext1);
                                     }
                                 if (fcttextCtr ==3) {
                                     buff.toCharArray(fcttext2, l);
// Serial.println();                   Serial.print(" fcttext2: ");Serial.println(fcttext2);                                     
                                     }
                                 if (fcttextCtr ==5) {
                                     buff.toCharArray(fcttext3, l);
// Serial.println();                   Serial.print(" fcttext3: ");Serial.println(fcttext3);                                     
                                     }
                                 if (fcttextCtr ==7) {
                                     buff.toCharArray(fcttext4, l);
 //Serial.println();                   Serial.print(" fcttext4: ");Serial.println(fcttext4);                                     
                                     }
                                 fcttextCtr++;
                                 buff = "";
                                 }
                             else
                             if (buff == String("fcttext")){
                                 lookingForfcttext = true;
                                 buff = "";
                                 }
                             else 
                             if (lookingForconditions == true) {
                                 lookingForconditions = false; 
                                 l = buff.length();
// Serial.println();  Serial.print("fcttextCtr: "); Serial.print(fcttextCtr); Serial.print(" L: "); Serial.print(l); Serial.print(" buff: "); Serial.print(buff);  
                                 if (conditionsCtr ==0) {
                                     buff.toCharArray(conditions0, l+1);
// Serial.println();                   Serial.print(" conditions0: ");Serial.println(conditions0);
                                     }
                                 if (conditionsCtr ==1) {
                                     buff.toCharArray(conditions1, l+1);
// Serial.println();                   Serial.print(" conditions1: ");Serial.println(conditions1);                                     
                                     }
                                 if (conditionsCtr ==2) {
                                     buff.toCharArray(conditions2, l+1);
// Serial.println();                   Serial.print(" conditions2: ");Serial.println(conditions2);                                     
                                     }
                                 if (conditionsCtr ==3) {
                                     buff.toCharArray(conditions3, l+1);
 //Serial.println();                   Serial.print(" conditions3: ");Serial.println(conditions3);                                     
                                     }
                                 if (conditionsCtr ==4) {
                                     buff.toCharArray(conditions4, l+1);
                                     endTime = millis() - startTime;  
 //Serial.println();                   Serial.print(" conditions4: ");Serial.println(conditions4);                                     
                                     }

                                 conditionsCtr++;
                                 buff = "";
                                 }
                             else
                             if (buff == String("conditions")){
                                 lookingForconditions = true;
                                 buff = "";
                                 }
                        
                         }  // end of  startQuote == true              
                  } // end of else not quote
              } // end c ==
               else
              if (startQuote == true) buff += c;
              }  // end of while available   
          } // end of while connected
//  Serial.println();

  www.close();

  Serial.print("Weather retrieved in ");
  Serial.print(endTime);   
  Serial.println(" milliseconds");

  writeWeather();

 tft.setCursor(60, 305);
 tft.print(F("Free RAM: ")); 
 tft.print(getFreeRam(), DEC);
 delay(5000);
  tft.fillRect(0, 280, 240, 40, BLUE);
  
  return true;
//  Serial.println(F("-------------------------------------"));
  
  /* You need to make sure to clean up after yourself or the CC3000 can freak out */
  /* the next time your try to connect ... */
//  Serial.println(F("\n\nDisconnecting"));
//  Serial.println();

 //displayWeather();
}
