void menuShell(boolean left, boolean right){            // common top & bottom of data screens

 int x = 5;
 int y = 10;
 int height = 20;
 int width = 60;
 int radius = 4;
 tft.fillRect(0, 0, 0, 60, BLUE);
 if (left == true) {
     tft.fillRect(x-2, y-2, width+5, height+4, BLACK);
     tft.fillRect(x, y, width, height, WHITE);
     }
 if (right == true){
     tft.fillRect(x+163, y-2,width+5, height+4, BLACK);  
     tft.fillRect(x+165, y, width, height, WHITE);
     }
 height = 13;
 width = 160;
 x = 30;
 y = 303;
 tft.fillRoundRect(x-2, y-2, width+5, height+4,radius, BLACK);
 tft.fillRoundRect(x, y, width, height,radius, WHITE);
 tft.setTextColor(BLACK, WHITE);
   if (left == true) {
       tft.setTextColor(BLACK, WHITE);
       tft.setCursor(25, 15);
       tft.print(F("Prev"));
       }
   if (right == true) {
       tft.setTextColor(BLACK, WHITE);
       tft.setCursor(190, 15);
       tft.print(F("Next"));
       tft.setTextColor(WHITE, BLUE);
        }

}
