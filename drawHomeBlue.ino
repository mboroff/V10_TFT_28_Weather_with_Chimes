void drawHomeBlue(){      // draw home button blue background ok to go to option menu

    int x = 181;
    int y = 21;
    int width = 48;
    int height = 18;
    tft.fillRect(x, y, width, height, BLUE);
    tft.setTextColor(WHITE, BLUE);
  x = 192;
  y = 26;
  tft.setCursor(x, y);
  tft.print(F("Home"));

}
