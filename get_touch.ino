/**********************************************
            get_touch - get touch screen x y and pressure
***********************************************/

void get_touch() 
{

// clear the coordinates
tsx = 0;
tsy = 0;
tsz = 0;
px = 0;
py = 0;
pz = 0;
//Serial.println("Get touch");
 // while (pz > 0)
 if (touch.touched()) {
   
    // read px & py & pz;
    while (! touch.bufferEmpty()) {
//      Serial.println(ts.bufferSize());
      touch.readData(&px, &py, &pz);
      while(touch.bufferSize()>0){
       touch.readData(&px, &py, &pz);
        //           ts.getPoint();  
             }
/*
      Serial.print(F("Before constrain ->(")); 
      Serial.print(px); Serial.print(F(", ")); 
      Serial.print(py); Serial.print(F(", ")); 
      Serial.print(pz);
      Serial.println(F(")"));
*/
              delay(50);

    touch.writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
    }

      if (pz > MINPRESSURE) {
          px = map(px, TS_MINX, TS_MAXX, 0, tft.width());
          py = map(py, TS_MINY, TS_MAXY, 0, tft.height());
/* 
          Serial.print(F("->(")); 
          Serial.print(px); Serial.print(F(", ")); 
          Serial.print(py); Serial.print(F(", ")); 
          Serial.print(pz);
          Serial.println(F(")"));
*/
          if (pz > tsz) {
             tsx = px;   // get max
             tsy = py;
             tsz = pz;
          }
           while(touch.bufferSize()>0){
            touch.getPoint();  
             }
           px = 0;
           py = 0;
           pz = 0;
      }
  }  
}


