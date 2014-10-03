void drawMygraph(int lowTemp,int xCorr1, int yCorr1) {     // draw a monthly temperature graph

 int x = 5;
 int y = 10;
 int height = 20;
 int width = 60;

 int radius = 4;            // draw left box
 tft.fillRect(0, 0, 0, 60, BLUE);
 tft.fillRect(x-2, y-2, width+5, height+4, BLACK);
 tft.fillRect(x, y, width, height, WHITE);

  tft.fillRect(x+163, y-2,width+5, height+4, BLACK);  // right box
  tft.fillRect(x+165, y, width, height, WHITE);
  
  tft.setTextColor(BLACK, WHITE);
  tft.setCursor(25, 15);
  tft.print(F("Prev"));
  tft.setCursor(190, 15);
  tft.print(F("Next")); 
  tft.setTextColor(WHITE, BLUE); 
 x = xCorr1;
 y = yCorr1;
 int yTemp = 0;
 tft.drawLine(x,y, x, y-210, WHITE);                         // lay out the x and y axis
 tft.drawLine(x,y, x+200, y, WHITE);
 tft.drawLine(x - 10,y-20, x+10, y-20, WHITE); //10               // layout the y axis points
 tft.drawLine(x - 10,y-40, x+10, y-40, WHITE);//20
 tft.drawLine(x - 10,y-60, x+10, y-60, WHITE);//30
 tft.drawLine(x - 10,y-80, x+10, y-80, WHITE);//40
 tft.drawLine(x - 10,y-100, x+10, y-100, WHITE);//50
 tft.drawLine(x - 10,y-120, x+10, y-120, WHITE); //60
 tft.drawLine(x - 10,y-140, x+10, y-140, WHITE);//70
 tft.drawLine(x - 10,y-160, x+10, y-160, WHITE);//80
 tft.drawLine(x - 10,y-180, x+10, y-180, WHITE);//90
 tft.drawLine(x - 10,y-200, x+10, y-200, WHITE);//100

 tft.drawLine(x +44,y-10, x+44, y+10, WHITE);  //10             lay out the x axis points
 tft.drawLine(x +104,y-10, x+104, y+10, WHITE);  // 20
 tft.drawLine(x +164,y-10, x+164, y+10, WHITE);  // 30
 tft.drawLine(x + 150, y - 220, x+170, y-220, RED);            // legends
 tft.drawLine(x + 150, y - 230, x+170, y-230, GREEN);
 tft.setCursor(x +178, y - 235);
 tft.setTextColor(WHITE, BLUE);
 tft.print("Highs");
 tft.setCursor(x +178, y - 225);
 tft.print("Lows");
 tft.setCursor(x +68, y+20);
 tft.print(pF(&monthStrs[mYmonth]));

 x = xCorr1;
 y = yCorr1;
 tft.setCursor(x+40, y+14);
 tft.print("10");
 tft.setCursor(x+100, y+14);
 tft.print("20");
 tft.setCursor(x+160, y+14);
 tft.print("30");
 
 tft.setCursor(x-24, y-43);
 tft.print("20");
 tft.setCursor(x-24, y-83);
 tft.print("40");
 tft.setCursor(x-24, y-123);
 tft.print("60");
 tft.setCursor(x-24, y-163);
 tft.print("80");
 tft.setCursor(x-30, y-203);
 tft.print("100");

 int curx=0;
//Serial.println("D Hi Lo");
 for (int d = 1 ; d <32; d++) {                    // Now spin through the array will be used for plotting
 
/*
      if (weatherTempLowDay[d] == -25){               // used in testing
          weatherTempLowDay[d] = 20;
          weatherTempLowDay[d+1] = 20;
          } 
      if (weatherTempHighDay[d] == 120){
          weatherTempHighDay[d] = 90;
          weatherTempHighDay[d+1] = 90;          
          }
*/
      if (weatherTempLowDay[d] != -25 && weatherTempLowDay[d+1] != -25 && weatherTempLowDay[d+1] < 110 ) {
          int ytemp1 = weatherTempLowDay[d] *-2;
          int ytemp2 = weatherTempLowDay[d+1]*-2 ;
 //  Serial.print(d); Serial.print(" "); Serial.print(weatherTempLowDay[d]); Serial.print(" ");  //   Serial.print(" X = "); Serial.print(curx+x); Serial.print(" y = "); Serial.println(ytemp1);    
 // Serial.print(weatherTempLowDay[d+1]);      Serial.print(" X+1day = "); Serial.print(curx+x+12); Serial.print(" Y+1day = "); Serial.println(ytemp2);
          tft.drawLine(curx+x,yCorr1+ ytemp1+1,curx+x+5,yCorr1+ ytemp2+1, RED);
          }
      if (weatherTempHighDay[d] != 120 && weatherTempHighDay[d+1] != 120 && weatherTempHighDay[d+1] > -10) {  
          int ytemp1 = weatherTempHighDay[d] * -2;
          int ytemp2 = weatherTempHighDay[d+1] * -2;
// Serial.println(weatherTempHighDay[d]);    //    Serial.print("Left point = "); Serial.print(ytemp1);Serial.print(" X = "); Serial.print(curx+x); Serial.print(" y = "); Serial.println(ytemp1);    
// Serial.print(weatherTempHighDay[d]);          Serial.print("Right point = "); Serial.print(ytemp2);Serial.print(" X+1day = "); Serial.print(curx+x+12); Serial.print(" Y+1day = "); Serial.println(ytemp2);
          tft.drawLine(curx+x, yCorr1+ytemp1+1,curx+x+5,yCorr1+ ytemp2+1, GREEN);
          }
      curx = curx+5;
      }
 
}    
