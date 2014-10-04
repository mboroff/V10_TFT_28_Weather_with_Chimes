void displayInsidetemp () {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 dhtCtr++; 
 if (dhtCtr < 5) return;
 dhtCtr = 0;
 float h = dht.readHumidity();
  float t = dht.readTemperature();
  float dewPoint;
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println(F("Failed to read from DHT"));
  } else {
    float temperatureF = (t * 9.0 / 5.0) + 32.0;
    char tempBuff[8];
    int j;
    int hp;
    hp = h;
    int tf;
    tf = temperatureF;
    x = 0;
    y = iNy;
    tft.setCursor(x,y);
    char printBuff[80];                      // display indore temp and humidity
    j = sprintf(printBuff, " In: %d", tf);
    strcat(printBuff, "F ");
    tft.print(printBuff);
    j = sprintf(printBuff, "%d", hp);
    strcat(printBuff, "% ");
    tft.print(printBuff);
     }
   } 

