void drawPlay()                                  // MP3 buttons
{
  
  x = 30;
  y = 220;
  
  tft.fillRect(x-4, y-4, 10+8, 40+8, BLUE);
  tft.fillRect(x+20-4, y-4, 10+8, 40+8, BLUE);                      // print triangle
  y = 260;
  tft.fillTriangle(x, y, x, y-40, x +35, y -20, BLACK);
}
void drawPause()                                                 // draw ||
{
  x = 30;
  y = 220;
  tft.fillRect(x-4, y-4, 60, 40+8, BLUE);
  tft.fillRect(x-4, y-4, 10+8, 40+8, BLACK);
  tft.fillRect(x, y, 10, 40, WHITE);
  tft.fillRect(x+20-4, y-4, 10+8, 40+8, BLACK);  
  tft.fillRect(x+20, y, 10, 40, WHITE); 
 } 
 
 void drawStop()                                        //      draw a square
 {
  x = 150;
 y = 230;
  tft.fillRect(x-4, y-4, 28, 28, WHITE);
 tft.fillRect(x, y, 20, 20, BLACK);  
   
 }   
 
 void drawClear() {                             // clear the area
   x = 30;
   y = 220;
     tft.fillRect(x-4, y-4, 200, 48, BLUE);
 }
