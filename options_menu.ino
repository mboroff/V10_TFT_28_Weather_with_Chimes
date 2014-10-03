void optionsMenu(){              // Options menu
   menuCtr = 1; 
   drawOptions();
   while (1) {                                     // stay in this loop until the user selects the return to options 
      if (minute() ==  0 || minute() == 10 || minute() == 20 || 
          minute() == 30 || minute() == 40 || minute() == 50 ) {
          if (second() < 10) {
              getWeb();
              return;  //  trigger return on next while compare
            } 
          }
       get_touch();                               // by pressing at the botton of display 
        if (tsz > MINPRESSURE) {
 //     Serial.print("Options menu X = "); Serial.print(tsx);
 //     Serial.print("\tOptions menu Y = "); Serial.println(tsy);
 //     Serial.print("\tOptions menu Pressure = "); Serial.println(tsz);


        if (tsy > 280) {                            // check if bottom pressed
             tsy = 0;
             menuCtr = 0;
             return;
             }

         else if (tsy > 20 && tsy < 100) {                           // user selected graphs
             tsz = 0;
             displayTempgraphs();  
             tft.fillScreen(BLUE);  
             menuCtr = 1; 
             drawOptions();
             }

         else if (tsy > 110 && tsy < 140) {                       // user selectd sounds
             tsz = 0;
             playMp3();
             tft.fillScreen(BLUE);  
             menuCtr = 1; 
             drawOptions();
             }
         else if (tsy > 150 && tsy < 180) {               // display sd directory
             tsz = 0;
             displayDirectory();
             tft.fillScreen(BLUE);  
             menuCtr = 1; 
             drawOptions();
             }
         else if (tsy > 190 && tsy < 250) {                  // forecast
             tsz = 0;
             foreCast();
             tft.fillScreen(BLUE);  
             menuCtr = 1; 
             drawOptions();
             }
          }
  }// end of menu while

}
