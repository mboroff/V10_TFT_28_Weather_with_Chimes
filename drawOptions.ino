void drawOptions() {                 // Display options menu
   tft.fillScreen(BLUE);  
   if (menuCtr == 1) {              // if displaying first page of menus do not display page back info
       menuShell(0, 0);                 // draw the bottom button, no prev or next
       }

  x = 70;                        // text for bottom button
  y = 305;
  tft.setCursor(x, y);
  tft.setTextColor(BLACK, WHITE);
  tft.print("Return to Clock");  
  int x = 40;                      // construct the menu
  int y = 75;
  int radius = 4;
  int height = 20;
  int width = 50;                  // draw the title
  tft.fillRect(94, 18, width+4, height+4, BLACK);
  tft.fillRect(96, 20, width, height, WHITE);        
  width = 140;                  // draw the buttons
  tft.fillRoundRect(x-2, y-2, width+5, height+4,radius, BLACK);
  tft.fillRoundRect(x, y, width, height,radius, WHITE);          
 
  tft.fillRoundRect(x-2, y+38, width+5, height+4,radius, BLACK);
  tft.fillRoundRect(x, y+40,width, height,radius, WHITE);

  tft.fillRoundRect(x-2, y+78, width+5, height+4,radius, BLACK);
  tft.fillRoundRect(x, y+80,width, height,radius, WHITE);

  tft.fillRoundRect(x-2, y+118, width+5, height+4,radius, BLACK);
  tft.fillRoundRect(x, y+120,width, height,radius, WHITE);

                     // display the option item text
  tft.setCursor(100, 25);
  tft.print(F("Options")); 
  tft.setCursor(50, 80); 
  tft.print(F("Tempurature Graphs"));  
  tft.setCursor(80, 120);  
  tft.print(F("Sounds"));  
  tft.setCursor(60, 160);  
  tft.print(F("SD Directory"));
  tft.setCursor(60, 200);  
  tft.print(F("Forecast"));
  tft.setTextColor(WHITE, BLUE);  
}
