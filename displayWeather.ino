void displayWeather()                          // display the weather information
{
    x = 0;                                   // TFT Display info
    y = 220;
    tft.fillRect(0, y-10, 240, 110, BLUE);
    tft.setCursor(x, y);
    tft.print("Out: ");                 // Out:
    tft.print(temp_f);
    tft.print("F ");
    tft.print(humidity);                     // Humidity %
    tft.print(" Wind  ");
    tft.print(winddir);                  // Humidity
    tft.print(" ");
    tft.print(wind_mph);                   // Wind speed
    tft.print(" Mph");
    
    
    x = 30;                               
    y = y+10;
    tft.setCursor(x, y);
    tft.print("Feels Like ");                // Feels like
    tft.print(feelslikestring);
    x = 30;
    y = y+20;
    tft.setCursor(x, y);                 
    tft.print("FORECAST");                // Forecast
    x = 0;
    y = y + 20;
    tft.setCursor(x, y);       
    tft.print(title[1]);                // Today
    tft.print(F(" "));                   
    tft.print(fahrenheit[0]);               // High temp of the day
    tft.print(F("/")); 
    tft.print(fahrenheit[1]);                 // Low temp of the day
    tft.print(F("F "));
    tft.print(conditions1);                 // conditions
    y = y + 10;
    tft.setCursor(x, y);       
    tft.print(title[3]);                  // Tomorrow
    tft.print(F(" ")); 
    tft.print(fahrenheit[2]);           // High temp of the day
    tft.print(F("/")); 
    tft.print(fahrenheit[3]);           // Low temp of the day
    tft.print(F("F "));
    tft.print(conditions2);
    y = y + 10;
    tft.setCursor(x, y);       
    tft.print(title[5]);              // Day after tomorrow
    tft.print(F(" ")); 
    tft.print(fahrenheit[4]); 
    tft.print(F("/")); 
    tft.print(fahrenheit[5]); 
    tft.print(F("F "));
    tft.print(conditions3);
    y = y + 10;
    tft.setCursor(x, y);           
    tft.print(title[7]); 
    tft.print(F(" ")); 
    tft.print(fahrenheit[6]); 
    tft.print(F("/")); 
    tft.print(fahrenheit[7]); 
    tft.print(F("F "));
    tft.print(conditions4);         //   2 Days after tomorrow
 //   Serial.print("Web accesses ");   Serial.println(internetCtr); 

    for (int i = 0; i < 20; i++) {          // based upon weather description display bmp
         int result = strcmp(weather, weatherChars[i]); // compare the value of weather charaters to find bmp file
         if (result == 0) {
             switch (weatherBmps[i]){
             case 1:
                    bmpDraw("cloudy.bmp", 0,clockCenterY-15);
                    break;
             case 2:
                    bmpDraw("fog.bmp", 0,clockCenterY-15);
                    break;
             case 3:
                    bmpDraw("lteran32.bmp", 0,clockCenterY-15);
                    break;
             case 4:
                    bmpDraw("lteShowr.bmp", 0,clockCenterY-15);
                    break;
             case 5:
                    bmpDraw("ltesnow.bmp", 0,clockCenterY-15);
                    break;
             case 6:
                    bmpDraw("Ovrc32.bmp", 0,clockCenterY-15);
                    break;
             case 7:
                    bmpDraw("rain.bmp", 0,clockCenterY-15);
                    break;
             case 8:
                    bmpDraw("snow.bmp", 0,clockCenterY-15);
                    break;
             case 9:
                    bmpDraw("sunny.bmp", 0,clockCenterY-15);
                    break;
             case 10:
                    bmpDraw("Tstorms.bmp", 0,clockCenterY-15);
                    break;
             case 11:
                    bmpDraw("hail.bmp", 0,clockCenterY-15);
                    break;
                   }  // end of switch               
                 }   // end of result
               }  // end of for
  }   
