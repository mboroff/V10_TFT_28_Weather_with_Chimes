void drawFace() {                             // Draw the face of the clock - The numbers are based off the top left pixle

  tft.fillScreen(BLUE);  

  //   draw two circles
  tft.drawCircle(clockCenterX, clockCenterY, circleSize, WHITE);
  tft.drawCircle(clockCenterX, clockCenterY, circleSize + 3, WHITE);
  tft.drawCircle(clockCenterX, clockCenterY, circleSize - 20, WHITE);
  tft.drawCircle(clockCenterX, clockCenterY, circleSize - 17, WHITE);

//      XII
  int x = clockCenterX-19;
  int y = clockCenterY-75;

  tft.drawRect(x,y,9,1, WHITE);
  tft.drawRect(x+13,y,8,1, WHITE);
  tft.drawRect(x,y+8,9,1, WHITE);         
  tft.drawRect(x+13,y+8,8,1, WHITE); 
  tft.drawLine(x+3,y+1,x+15,y+7, WHITE);     
  tft.drawLine(x+4,y+1,x+16,y+7, WHITE);   
  tft.drawLine(x+5,y+1,x+17,y+7, WHITE);                 
  tft.drawLine(x+16,y+1,x+3,y+7, WHITE);
     
  tft.drawRect(x+23,y,8,1, WHITE);
  tft.drawRect(x+26,y+1,2,8, WHITE);
  tft.drawRect(x+23,y+8,8,1, WHITE);  
  
  tft.drawRect(x+35,y,8,1, WHITE);
  tft.drawRect(x+38,y+1,2,8, WHITE);
  tft.drawRect(x+35,y+8,8,1, WHITE);  
    

//         III

  x = clockCenterX+66;
  y = clockCenterY-15;
  tft.drawRect(x+1, y+3, 9, 2, WHITE);
  tft.drawRect(x+1, y+11, 9, 2, WHITE); 
  tft.drawRect(x+1, y+20, 9, 2, WHITE);        
  tft.drawRect(x, y, 1, 8, WHITE); 
  tft.drawRect(x,y+9, 1, 7, WHITE); 
  tft.drawRect(x, y+17, 1, 7, WHITE);     
  tft.drawRect(x+10, y, 1, 8, WHITE); 
  tft.drawRect(x+10, y+9, 1, 7, WHITE); 
  tft.drawRect(x+10, y+18, 1, 7, WHITE);     


//     upside dowm VI

  x = clockCenterX-10;
  y = clockCenterY+65;

  tft.fillRect(x+3, y, 3,10, WHITE);
  tft.drawLine(x, y, x+8, y, WHITE);
  tft.drawLine(x, y+9, x+7,y+9, WHITE);

  tft.drawLine(x+17,y,x+12,y+9, WHITE);   
  tft.drawLine(x+17,y,x+21,y+9, WHITE);          
  tft.drawLine(x+18,y,x+22,y+9, WHITE); 
  tft.drawLine(x+19,y,x+23,y+9, WHITE); 
  tft.drawLine(x+9,y+9,x+16,y+9, WHITE);
  tft.drawLine(x+19,y+9,x+25,y+9, WHITE);     
     
//   sideways XI 
  x = clockCenterX-76;
  y = clockCenterY-15;

  tft.drawLine(x+9,y,x+9,y+9, WHITE); 
  tft.drawLine(x+9,y+14,x+9,y+23, WHITE);          
  tft.drawLine(x,y, x,y+9, WHITE); 
  tft.drawLine(x,y+14, x,y+23, WHITE);          
  tft.drawLine(x,y+4,x+8,y+19, WHITE); 
  tft.drawLine(x+1,y+3,x+8,y+18, WHITE); 
  tft.drawLine(x+8,y+4,x,y+19, WHITE);       


  tft.fillRect(x,y+28,10,3,WHITE);
  tft.drawLine(x+9,y+26,x+9,y+33, WHITE);     
  tft.drawLine(x,y+26,x,y+33, WHITE);     

}

void drawHour() {                             // Draw the hour hand
  float x1, y1, x2, y2;
  int ph = prevHour;

  if (prevMin ==0){
      ph=((ph-1)*30)+((prevMin+59)/2);
      }
  else
      {
     ph= (ph*30)+((prevMin-1)/2);
     }

  ph = ph+270;

  x1=50*cos(ph*0.0175)+xDiff;                 // calculate the angle of the hand from center then erase the previous display the write the new display
  y1=50*sin(ph*0.0175)-yDiff;
  x2=1*cos(ph*0.0175)+xDiff;
  y2=1*sin(ph*0.0175)-yDiff;

  tft.drawLine(x1+clockCenterX,y1+clockCenterY, x2+clockCenterX,y2+clockCenterY,BLUE);
  ph = mYhour;
  if (mYminute ==0){
      ph=((ph-1)*30)+((mYminute+59)/2);
      }
  else
      {
      ph= (ph*30)+((mYminute-1)/2);
      }
  ph = ph+270;


  x1=50*cos(ph*0.0175)+xDiff;                 // calculate the angle of the hand from center then erase the previous display the write the new display
  y1=50*sin(ph*0.0175)-yDiff;
  x2=1*cos(ph*0.0175)+xDiff;
  y2=1*sin(ph*0.0175)-yDiff;
  tft.drawLine(x1+clockCenterX,y1+clockCenterY, x2+clockCenterX,y2+clockCenterY,WHITE);
  prevHour = mYhour;

}

void drawSec(){                                                // Draw the second hand

  float x1, y1, x2, y2;
  int ps = prevSec;

  ps=ps*6;
  ps=ps+270;
  x1=58*cos(ps*0.0175) + xDiff ;
  y1=58*sin(ps*0.0175) - yDiff;
  x2=1*cos(ps*0.0175) + xDiff;
  y2=1*sin(ps*0.0175) - yDiff;
  tft.drawLine(x1+clockCenterX,y1+clockCenterY, x2+clockCenterX,y2+clockCenterY,BLUE);


  ps=mYsecond*6;
  ps=ps+270;

  x1=58*cos(ps*0.0175) + xDiff ;
  y1=58*sin(ps*0.0175) - yDiff;
  x2=1*cos(ps*0.0175) + xDiff;
  y2=1*sin(ps*0.0175) - yDiff;
  tft.drawLine(x1+clockCenterX,y1+clockCenterY, x2+clockCenterX,y2+clockCenterY,RED);

  prevSec = mYsecond;

}

void drawMin(){                                   // Draw the minute hand
 
  float x1, x2, y1, y2, x3, y3, x4, y4;
  int pm = prevMin;

  if (pm==-1) pm = 59;
  pm = pm*6;
  pm=pm+270;

  x1=58*cos(pm*0.0175) + xDiff ;
  y1=58*sin(pm*0.0175) - yDiff;
  x2=1*cos(pm*0.0175) + xDiff;
  y2=1*sin(pm*0.0175) - yDiff;
  tft.drawLine(x1+clockCenterX,y1+clockCenterY, x2+clockCenterX,y2+clockCenterY,BLUE);

  pm = mYminute;

  if (pm==-1) pm = 59;
  pm = pm*6;
  pm=pm+270;

  x1=58*cos(pm*0.0175) + xDiff ;
  y1=58*sin(pm*0.0175) - yDiff;
  x2=1*cos(pm*0.0175) + xDiff;
  y2=1*sin(pm*0.0175) - yDiff;
  tft.drawLine(x1+clockCenterX,y1+clockCenterY, x2+clockCenterX,y2+clockCenterY,WHITE);
  
  prevMin = mYminute;

}

