/**********************************************
             Play MP3
***********************************************/
void playMp3(){                  // display SD Directory

  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  

  uint16_t px, py;                      // pressure coordinates
  uint8_t pz;
  int x = 0;
  int y = 0;
  tft.fillScreen(BLUE);               // clear the screen
  fileCols = 2;                       // display 2 cols of four choices
  fileRows = 3;
  fileSearch = "MP3";
  fileButtons = true;
  xinCr = 100;
  startCol = 40;

  int width = 86;
  int height = 15;
 
  tft.drawLine(180, 20, 230, 20, WHITE);
  tft.drawLine(180, 40, 230, 40, WHITE);
  tft.drawLine(180, 20, 180, 40, WHITE);
  tft.drawLine(230, 20, 230, 40, WHITE);
  tft.drawLine(160, 25, 205, 5, WHITE);
  tft.drawLine(205, 5, 240, 25, WHITE);
  tft.setTextColor(WHITE, BLUE);
  x = 192;
  y = 26;
  tft.setCursor(x, y);
  tft.print(F("Home"));
  x = 80;
  y = 30;
  tft.setTextColor(WHITE, BLUE);
  tft.setCursor(x, y);
  tft.print(F("Play MP3 Music"));
  x = 40;
  y = 280;
  width = 160;
  height = 20;

  tft.fillRect(x-4, y-4, width+8, height+8, BLACK);
  tft.fillRect(x, y, width, height, WHITE);          //draw the   menu
  x = 60;
  y = 285;
  tft.setTextColor(BLACK, WHITE);
  tft.setCursor(x, y);
  tft.print(F("List more somgs"));
  tft.setTextColor(WHITE, BLUE);
  menuCtr = 1;
  fileCtr = 0;
  fileIndex = 0;
  fileButtons = true;
  fileLookup();
  
  while (1) {  
     getTime();                    
     if (prevSec != mYsecond) {               // display the time
         prevSec = mYsecond;       
         x = 100;
         y = 10;
         tft.setCursor(x, y);
         if (mYhour < 10 || (mYhour - 12) < 10){
             tft.print(F("0"));
             }
         if (mYhour < 13) {
             tft.print(mYhour);
             } else {
                     tft.print(mYhour - 12);
                     }
         tft.print(F(":"));
         if (mYminute < 10) tft.print(F("0"));
         tft.print(mYminute);
         tft.print(F(":"));
         if (mYsecond < 10) tft.print(F("0"));
         tft.print(mYsecond);
         }
  get_touch();
  if (tsz > MINPRESSURE) {                             //      pressure check
     // scale from 0->1023 to tft.width
//      Serial.print(F("->(")); Serial.print(tsx); Serial.print(F(", ")); Serial.print(tsy); Serial.print(F(", ")); Serial.print(tsz); Serial.println(")");
      if (tsx > 180 || tsy < 68){
           musicPlayer.stopPlaying();
           return;
           }
      if (tsy > 280) {
          musicPlayer.stopPlaying();
          tft.fillRect(0, 50, 240, 210, BLUE);
//          Serial.print(F("end of while buffer flush - SD Pressure "));
//          Serial.print(F("menuCtr = ")); Serial.println(menuCtr);
          menuCtr++;
          if (fileIndex == fileCtr) return;
          fileCtr = 0;
          fileLookup();
          }
      if (tsx > 30 && tsx < 70 && tsy > 230 && tsy < 270) {
          if (! musicPlayer.paused()) {
//              Serial.println("Paused");
              drawPlay();
              musicPlayer.pausePlaying(true);
              } else { 
                drawPause();
//                Serial.println("Resumed");
                musicPlayer.pausePlaying(false);
                }
      }
      if (tsx > 150 & tsx < 170 && tsy > 230 && tsy < 270) {
//          Serial.println("Stopped");
          musicPlayer.stopPlaying();
          drawClear();
      }
      if (tsx > 23 && tsx <= 110 && tsy >68 && tsy < 110) {
          drawHomered();      
          Serial.println(F("Option 1 Selected"));
          Serial.println(fileName[0]);
          drawPause();
          drawStop();
          if (fileName[0] != "") musicPlayer.startPlayingFile(fileName[0]);
          drawHomeBlue();
          }
      if (tsx > 23 && tsx <= 110 && tsy >114 && tsy < 140) {
          drawHomered();      
          Serial.println(F("Option 2 Selected"));
          Serial.println(fileName[1]);
          drawPause();
          drawStop();
          if (fileName[1] != "") musicPlayer.startPlayingFile(fileName[1]);
          drawHomeBlue();
          }
      if (tsx > 23 && tsx <= 110 && tsy >148 && tsy < 190) {
          drawHomered();      
          Serial.println(F("Option 3 Selected"));
          Serial.println(fileName[2]);
          drawPause();
          drawStop();
          if (fileName[2] != "") musicPlayer.startPlayingFile(fileName[2]);
          drawHomeBlue();
          }
      if (tsx > 23 && tsx <= 110 && tsy >197 && tsy < 226) {
          drawHomered();      
          Serial.println(F("Option 4 Selected"));
          Serial.println(fileName[3]);
          drawPause();
          drawStop();
          if (fileName[3] != "") musicPlayer.startPlayingFile(fileName[3]);
          drawHomeBlue();
          }

      if (tsx > 125 && tsx <= 210 && tsy >68 && tsy < 110) {
          drawHomered();      
          Serial.println(F("Option 5 Selected"));
          Serial.println(fileName[4]);
          drawPause();
          drawStop();          
          if (fileName[4] != "") musicPlayer.startPlayingFile(fileName[4]);
          drawHomeBlue();
          }
      if (tsx > 125 && tsx <= 210 && tsy >114 && tsy < 140) {
          drawHomered();      
          Serial.println(F("Option 6 Selected"));
          Serial.println(fileName[5]);
          drawPause();
          drawStop();          
          if (fileName[5] != "") musicPlayer.startPlayingFile(fileName[5]);
          drawHomeBlue();
          }

      if (tsx > 125 && tsx <= 210 && tsy >148 && tsy < 190) {
          drawHomered();      
          Serial.println(F("Option 7 Selected"));
          Serial.println(fileName[6]);
          drawPause();
          drawStop();
          if (fileName[6] != "") musicPlayer.startPlayingFile(fileName[6]);
          drawHomeBlue();
          }
      if (tsx > 125 && tsx <= 210 && tsy >197 && tsy < 226) {
          drawHomered();      
          Serial.println(F("Option 8 Selected"));
          Serial.println(fileName[7]);
          drawPause();
          drawStop();          
          if (fileName[7] != "") musicPlayer.startPlayingFile(fileName[7]);
          drawHomeBlue();
          }
  }    // end of pressure
  } // end of while
 
}

