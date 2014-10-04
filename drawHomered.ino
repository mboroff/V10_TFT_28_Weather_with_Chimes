void drawHomered(){               /// draw home button with wait

    int x = 181;
    int y = 21;
    int width = 48;
    int height = 18;
    tft.fillRect(x, y, width, height, RED);
    tft.setTextColor(WHITE, RED);
    x = 192;
    y = 26;
    tft.setCursor(x, y);
    tft.print(F("Wait"));

}

