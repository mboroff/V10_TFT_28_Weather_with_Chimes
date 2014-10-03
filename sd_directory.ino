/**********************************************
             SD Directory
***********************************************/
void displayDirectory(){                  // display SD Directory

  uint16_t px, py;
  uint8_t pz;
  int x = 0;
  int y = 0;
  tft.fillScreen(BLUE);

  int width = 86;
  int height = 15;
  fileCols = 1;
  fileRows = 18;
  startCol = 10;
  texTsize = 0;
  fileSearch = "*";
  xinCr = 100;
  tft.drawLine(180, 20, 230, 20, WHITE);
  tft.drawLine(180, 40, 230, 40, WHITE);
  tft.drawLine(180, 20, 180, 40, WHITE);
  tft.drawLine(230, 20, 230, 40, WHITE);
  tft.drawLine(160, 25, 205, 5, WHITE);
  tft.drawLine(205, 5, 240, 25, WHITE);
  tft.setTextColor(WHITE, BLUE);
  texTx = 192;
  texTy = 26;
  tft.setCursor(texTx, texTy);
  tft.print(F("Home"));
  texTx = 80;
  texTy = 30;
  tft.setTextColor(WHITE, BLUE);
  tft.setCursor(texTx, texTy);
  tft.print(F("SD Directory"));
  x = 40;
  y = 280;
  width = 160;
  height = 20;
  tft.fillRect(x-4, y-4, width+8, height+8, BLACK);
  tft.fillRect(x, y, width, height, WHITE);          //draw the   menu
  texTx = 60;
  texTy = 285;
  tft.setTextColor(BLACK, WHITE);
  tft.setCursor(texTx, texTy);
  tft.print(F("List more files"));
  tft.setTextColor(WHITE, BLUE);
  menuCtr = 1;
  fileCtr = 0;
  fileIndex = 0;
  fileButtons = false;
  fileLookup();
  
  while (1) {  
     getTime();
     if (prevSec != mYsecond) {
         prevSec = mYsecond;       
         texTx = 100;
         texTy = 10;
         tft.setCursor(texTx, texTy);
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
   if (minute() ==  0 || minute() == 10 || minute() == 20 || 
          minute() == 30 || minute() == 40 || minute() == 50 ) {
            return;
          } 
   
    get_touch();
  if (tsz > MINPRESSURE ) {
   // scale from 0->1023 to tft.width
      if (tsx > 180 || tsy < 200) return;
      if (tsy > 200) {
   tft.fillRect(0, 50, 240, 210, BLUE);
//      Serial.print(F("end of while buffer flush - SD Pressure "));
//      Serial.print(F("menuCtr = ")); Serial.println(menuCtr);
      menuCtr++;
      if (fileIndex == fileCtr) return;
       fileCtr = 0;
      fileLookup();
      }
   }
  } // end of while

}

void fileLookup(){                // scan the directory of the SD

 // int x = 60;
 // int y = 285;
 // int width = 160;
 // int height = 20; 
  drawHomered();    
  tft.setTextColor(BLACK, WHITE);
  texTx = 60;
  texTy = 285;
  tft.setCursor(texTx, texTy);
  tft.print(F("Reading Files      "));
  root = SD.open("/");
  printDirectory(root, 0);
 // tft.fillRect(x, y, width, height, BLUE);
  tft.setTextColor(BLACK, WHITE);
  texTx = 60;
  texTy = 285;
  tft.setCursor(texTx, texTy);
  if (fileSearch == String("MP3")){
    tft.print(F("List more songs"));
  }
  else {
    tft.print(F("List more files"));
  }
  drawHomeBlue();
 // selectionSort2d();
  Serial.println(F("done!"));

}

void printDirectory(File dir, int numTabs) {    // Extract filenames and sizes - display of sizes takes up too much real estate
  tft.fillRect(0, 50, 240, 220, BLUE);
  if (fileButtons == true) {
      int x = startCol - 12;
      int y = 68;
      int width = 70;
      int height = 20;
      mp3Ctr = 0;
      for (int colCtr = 0; colCtr < fileCols; colCtr++){
           for (int rowCtr = 0; rowCtr < fileRows+1; rowCtr++) {
                tft.fillRect(x-4, y-4, width+8, height+8, BLACK);
                tft.fillRect(x, y, width, height, WHITE); 
                strcpy(fileName[mp3Ctr], "");
                mp3Ctr++;
                y = y + 40;
                }
      y = 68;          
      x = x + xinCr;
      }
  }

  int x = startCol;
  int y = 70;
 // fileIndex = (menuCtr * 68) - 68;
 
  if (fileSearch == String("MP3")) {
      tft.setTextColor(BLACK, WHITE);
      y = 75;
      }
  else {
  tft.setTextColor(WHITE, BLUE);
  }


  // Begin at the start of the directory

  dir.rewindDirectory();
  String fn;
  String fr;
  String ext;
  mp3Ctr = 0;
  int colCtr = 0;
  int rowCtr = 0;
  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
//       Serial.print('\t');   // we'll have a nice indentation
     }
     // Print the 8.3 name
     fn = "";
     fr = "";
     ext = "";
//     Serial.print(entry.name());
     // Recurse for directories, otherwise print the file size
     if (entry.isDirectory()) {
//       Serial.println(F("/"));
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
//       Serial.print(F("\t\t"));
//       Serial.println(entry.size(), DEC);
       fileCtr++;
 //      Serial.print(F("fileCtr = ")); Serial.print(fileCtr); Serial.print(F(" fileIndex = ")); Serial.print(fileIndex); Serial.print(F(" colCtr = ")); Serial.print(colCtr); Serial.print(F(" rowCtr = ")); Serial.println(rowCtr);
        int inDex;
       fn = fn+entry.name();
       int dotPosition = fn.indexOf(".");
       fr = fn.substring(0, dotPosition);
       ext =  fn.substring(dotPosition +1, dotPosition +4);
 //      Serial.print(F("fn = ")); Serial.print(fn); Serial.print(F(" ")); Serial.print(F("ext = ")); Serial.println(ext);
       if (fileCtr > fileIndex && colCtr < fileCols) {
           fileIndex++;
           if (ext == fileSearch || fileSearch == String("*")) {
               tft.setCursor(x, y);
               if (fileSearch == String("MP3")){ 
                   strcpy(fileName[mp3Ctr], entry.name());
//                   Serial.println(fileName[mp3Ctr]);
                   mp3Ctr++;
                   tft.print(fr);
                   y = y + 30;
                   }
               else {
                   tft.print(entry.name());
                   }

           tft.setCursor(x + 90, y);                  // just in case I want to display sizes
           y = y+10;  
           if (fileSearch == String("*")) {
               tft.print(entry.size(), DEC);
           }
           rowCtr++;
           if (rowCtr > fileRows) {
               rowCtr = 0;
               colCtr++;
               x = x + xinCr;
              if (fileSearch == String("MP3")){ 
                  y = 73;
              } else {
                y = 70;
              }
               }
           } 
    }
     }
        entry.close();
  } 

}

