void playHourly(){                                         // time the play the chimes unless it is 11 on Ina's or my birthday
 if (donotPlay == true) {
     return;
 }
  Serial.println(F("Music started"));
  Serial.print(hour()); Serial.print(":"); Serial.print(minute()); Serial.print(":"); Serial.println(second());

 // musicPlayer.begin(); // initialise the music player
 // SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
//  musicPlayer.setVolume(20,20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
 // musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
 
  digitalWrite(10, HIGH);                                 // Chimes are played 10 A.M. to 8 P.M.
//#ifdef DEBUG
//  Serial.println(F("Starting Music"));
//#endif
  if (hour() == 10) musicPlayer.playFullFile("houra.mp3");
  if (hour() == 11) {
      if (mYmonth == 7 && mYmonthDay == 31) {
          musicPlayer.playFullFile("Marty.mp3");
      }
      else {
        if (mYmonth == 11 && mYmonthDay == 2) {
          musicPlayer.playFullFile("Ina.mp3");
        }
    else {
     musicPlayer.playFullFile("hourb.mp3");
         }
      }
  }
  if (hour() == 12) musicPlayer.playFullFile("hourc.mp3");
  if (hour() == 13) musicPlayer.playFullFile("hour1.mp3");
  if (hour() == 14) musicPlayer.playFullFile("hour2.mp3");
  if (hour() == 15) musicPlayer.playFullFile("hour3.mp3");
  if (hour() == 16) musicPlayer.playFullFile("hour4.mp3");
  if (hour() == 17) musicPlayer.playFullFile("hour5.mp3");
  if (hour() == 18) musicPlayer.playFullFile("hour6.mp3");
  if (hour() == 19) musicPlayer.playFullFile("hour7.mp3");
  if (hour() == 20) musicPlayer.playFullFile("hour8.mp3");     
  if (hour() == 21) musicPlayer.playFullFile("hour9.mp3");   
  musicPlayer.stopPlaying();
  delay(1000);
  Serial.println(F("Music stopped"));
  Serial.print(hour()); Serial.print(":"); Serial.print(minute()); Serial.print(":"); Serial.println(second());
}


