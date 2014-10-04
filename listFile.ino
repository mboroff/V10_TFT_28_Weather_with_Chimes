void listFile(char *filename) {           // scans the montly file of collected temps into a 32 entry array save high low and humidity
//Serial.println("Listing ");
//Serial.println(filename);
  pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
   // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  for (int x = 0 ; x <32; x++) {
       weatherTempHighDay[x] = 120;
       weatherTempLowDay[x]  = -25;
       }
  File myFile = SD.open(filename);
  String buff = "";
  int foundIndex = 0;
  int searchIndex = 0;
  int j;
  monthLow = 200;
  // if the file is available, read it
  if (myFile) {
    while (myFile.available()) {
      char c = myFile.read();

      if (c == 0x0D || c == 0x0A) {
        j = buff.length();
        if (j > 0) {
          wRdd = buff.substring(3, 5);
//          find first comma
          searchIndex = buff.indexOf(",");
          for (int x = 0; x < 3; x++) {
          foundIndex = buff.indexOf(",", searchIndex + 1);
          searchIndex = buff.indexOf(",", foundIndex + 1);  
          } 
          wRtempF = buff.substring(foundIndex + 1, searchIndex);
          int mo = wRdd.toInt();
          int tempf = wRtempF.toInt();
//          Serial.print(tempf); Serial.print(" "); Serial.println(monthLow);
        if (tempf > -10 && tempf < 110) {
          if (tempf < monthLow) monthLow = tempf;
          if (weatherTempHighDay[mo] == 120) weatherTempHighDay[mo] = tempf;  // prime the array for the day high and low
          if (weatherTempLowDay[mo] == -25) weatherTempLowDay[mo] = tempf;
          if (tempf > weatherTempLowDay[mo]) weatherTempHighDay[mo] = tempf;   // figure out if the current read char is high or low
          if (tempf < weatherTempHighDay[mo]) weatherTempLowDay[mo] = tempf;   
        }
          buff = "";
        }
       c = myFile.read();

        buff = "";
      }
      else
      buff += c;

     }
    myFile.close();
      for (int x = 0 ; x <32; x++) {                    // Now spin through the array willbe used for plotting
       if (weatherTempLowDay[x] != -25) {

         Serial.print(x);
           Serial.print(" ");
           Serial.print(weatherTempLowDay[x]);
           Serial.print(" ");
           Serial.println(weatherTempHighDay[x]);

          }
       }

  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.print("error opening "); Serial.println(filename);
  } 
}


