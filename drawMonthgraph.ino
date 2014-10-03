 void drawMonthgraph(int xCorr2,int yCorr2){   // print a requested month at a certain x y coordinate
   tft.fillScreen(BLUE);  
   int x = xCorr2;
   int y = yCorr2;
   int m = mYmonth+1;
   switch (m) {                                  // pick a month file from the value of mYmonth
    case 1:
        listFile("jan.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 2:
        listFile("feb.txt");
        drawMygraph(monthLow, x, y);
        break; 
    case 3:
        listFile("march.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 4:
        listFile("april.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 5:
        listFile("may.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 6:
        listFile("june.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 7:
        listFile("july.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 8:
        listFile("aug.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 9:
        listFile("sept.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 10:
        listFile("oct.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 11:
        listFile("nov.txt");
        drawMygraph(monthLow, x, y);
        break;
    case 12:
        listFile("dec.txt");
        drawMygraph(monthLow, x, y);
        break;
    default:
        listFile("jan.txt");
        drawMygraph(monthLow, x, y);
   }  // end of switch

}



