/**
   @file uiITR.cpp
   @support (support@xinabox.cc)
   @brief Class for displaying information to OD01 on XK07 Flight Station
*/

#include "uiITR.h"
#include "imgOD01.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(-1);

/**
   @brief Construct a new uiXK01::uiITR object

*/
uiITR::uiITR(void)
{
  //Adafruit_SSD1306 display(-1);
}

bool uiITR::begin()
{
  if (xCore.ping(0x3C))
  {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  } else {
    return false;
  }
  display.clearDisplay();
  display.display();
  return false;
}

/**
   @brief Destroy the uiITR::uiITR object

*/
uiITR::~uiITR(void)
{
  // nothing to destruct
}

/**
   @brief

*/
void uiITR::drawConfigSaved(void)
{
  //Adafruit_SSD1306 display(-1);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.drawBitmap(0, 17, PassLogo, PassLogo_Width, PassLogo_Height, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(57, 36);
  display.println(F("UPLOADED"));
  display.setCursor(57, 45);
  display.print(F("COMPLETE"));
  display.display();
}

/**
   @brief

*/
void uiITR::drawProvisionSuccess(void)
{
  //Adafruit_SSD1306 display(-1);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.drawBitmap(0, 17, PassLogo, PassLogo_Width, PassLogo_Height, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(57, 36);
  display.println(F("UPLOADED"));
  display.setCursor(57, 45);
  display.print(F("COMPLETE"));
  display.display();
}

/**
   @brief

*/
void uiITR::drawWiFiConnected(void)
{
  if (xCore.ping(0x3C))
  {
    //Adafruit_SSD1306 display(-1);
    //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.drawBitmap(0, 17, PassLogo, PassLogo_Width, PassLogo_Height, WHITE);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(57, 36);
    display.println(F("UPLOADED"));
    display.setCursor(57, 45);
    display.print(F("COMPLETE"));
    display.display();
  }
}

/**
   @brief

*/
void uiITR::drawXinaBoxLogo(void)
{
  if (xCore.ping(0x3C))
  {
    //Adafruit_SSD1306 display(-1);
    //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(29, 0);    // Start at top-left corner
    display.println(F("XinaBox ITR"));
    display.setCursor(16, 9); // Start at top-left corner
    display.print(F("FIRMWARE : 0.1.1"));
    if (firmwareVersion[0] == '/0')
    {
      display.print("?.?.?");
    }
    else
    {
      display.print(firmwareVersion);
    }
    display.drawBitmap(0, 14, xinaboxLogo, xinaboxLogo_Width, xinaboxLogo_Height, WHITE);
    display.display();
  }
}

/**
   @brief

*/
void uiITR::drawLogoFS(void)
{
  if (xCore.ping(0x3C))
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(26, 0);    // Start at top-left corner
    display.print(F("Flight Station"));
    display.drawBitmap(40, 16, fsLogo, fsLogo_Width, fsLogo_Height, WHITE);
    display.display();
  }
}

/**
   @brief

*/
void uiITR::drawLogoGS(void)
{
  if (xCore.ping(0x3C))
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(26, 0);    // Start at top-left corner
    display.print(F("Ground Station"));
    display.drawBitmap(40, 16, gsLogo, gsLogo_Width, gsLogo_Height, WHITE);
    display.display();
  }
}

/**
   @brief

   @param _version
*/
void uiITR::setFirmwareVersion(String _firmwareVersion)
{
  firmwareVersion = _firmwareVersion;
}

/**
   @brief

*/
void uiITR::drawConnectingWiFi(void)
{
  //Adafruit_SSD1306 display(-1);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.clearDisplay();

  display.drawBitmap(0, 17, connectingWiFi1, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.drawBitmap(0, 17, connectingWiFi2, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.display();
  delay(100);

  display.drawBitmap(0, 17, connectingWiFi3, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.display();
  delay(100);

  display.drawBitmap(0, 17, connectingWiFi4, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.display();
  delay(100);

  display.drawBitmap(0, 17, connectingWiFi5, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.display();
  delay(100);
}

/**
   @brief

   @param _countDown
*/
void uiITR::drawConnectingWiFi(uint8_t _countDown)
{
  //Adafruit_SSD1306 display(-1);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  //display.display();
  //display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40, 0);
  display.print(F("T-"));
  display.print(9 - _countDown);
  display.print(F("s"));

  display.drawBitmap(0, 17, connectingWiFi2, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.display();
  delay(115);

  display.drawBitmap(0, 17, connectingWiFi3, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.display();
  delay(115);

  display.drawBitmap(0, 17, connectingWiFi4, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.display();
  delay(115);

  display.drawBitmap(0, 17, connectingWiFi5, connectingWiFi_Width, connectingWiFi_Height, WHITE);
  delay(10);
  display.display();
  delay(115);
}

/**
   @brief

*/
void uiITR::drawPixel(int16_t, int16_t, uint16_t)
{
  //display.drawPixel(x, y, z);
}

void uiITR::clearScreen()
{
  display.clearDisplay();
}
void uiITR::iconAndString(const uint8_t *bitmap, const char *str, int x, int y, int x1, int y1)
{
  if (xCore.ping(0x3C))
  {
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println((str));
    display.drawBitmap(x1, y1, bitmap, x, y, WHITE);
    display.display();
  }
}

void uiITR::connectingToWifi(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(1);
    iconAndString(wifiSolid1, str);
    delay(150);
    iconAndString(wifiSolid2, str);
    delay(150);
    iconAndString(wifiSolid3, str);
    delay(150);
  }
}

void uiITR::wifiPass(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(2);
    iconAndString(wifiSolid3, str);
    delay(1500);
  }
}
void uiITR::wifiFail(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.invertDisplay(true);
    iconAndString(wifiSolid3, str);
    delay(1500);
  }
}

void uiITR::loading(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(1);
    switch (cnt)
    {
      case 0:
        iconAndString(loading1, str, 96, 48, 18, 16);
        break;
      case 1:
        iconAndString(loading2, str, 96, 48, 18, 16);
        break;
      case 2:
        iconAndString(loading3, str, 96, 48, 18, 16);
        break;
      case 3:
        iconAndString(loading4, str, 96, 48, 18, 16);
        break;
      case 4:
        iconAndString(loading5, str, 96, 48, 18, 16);
        break;
      case 5:
        iconAndString(loading6, str, 96, 48, 18, 16);
        break;
      case 6:
        iconAndString(loading7, str, 96, 48, 18, 16);
        break;
      case 7:
        iconAndString(loading8, str, 96, 48, 18, 16);
        break;
    }
    cnt++;
    if (cnt == 7)
      cnt = 0;
  }
}

void uiITR::provFail(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.invertDisplay(true);
    iconAndString(loading8, str, 96, 48, 18, 16);
    delay(1500);
  }
}

void uiITR::provPass(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(2);
    iconAndString(loading8, str, 96, 48, 18, 16);
    delay(1500);
  }
}

void uiITR::fsPass(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(2);
    iconAndString(broadcastTower2, str, 98, 48, 18, 16);
    delay(1500);
  }
}

void uiITR::fsFail(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.invertDisplay(true);
    iconAndString(broadcastTower2, str, 98, 48, 18, 16);
    delay(1500);
  }
}

void uiITR::fsConnecting(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(1);
    iconAndString(broadcastTower0, str, 98, 48, 18, 16);
    iconAndString(broadcastTower1, str, 98, 48, 18, 16);
    iconAndString(broadcastTower2, str, 98, 48, 18, 16);
  }
}

void uiITR::almDownloading(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(1);
    iconAndString(calender, str, 98, 48, 18, 16);
    delay(1000);
  }
}

void uiITR::almDownloaded(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(1);
    iconAndString(calender, str, 98, 48, 15, 16);
    delay(1500);
  }
}

void uiITR::almDownloadedFail(const char *str)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(true);
    display.clearDisplay();
    display.setTextSize(1);
    iconAndString(calender, str, 98, 48, 15, 16);
    delay(1500);
  }
}

void uiITR::info(uint8_t mode, String time, String date, String rssi, String batPercentage)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextColor(WHITE);
    if (mode == 2) {
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println(time);
      display.setCursor(0, 8);
      display.println(date);
      display.setCursor(70, 0);
      display.println("HDOP");
      display.setCursor(100, 0);
      display.println("SATS");
      display.setCursor(70, 8);
      display.println(rssi);
      display.setCursor(100, 8);
      display.println(batPercentage);
    } else {
      display.setTextSize(2);
      display.setCursor(27, 0);
      display.println("INDOOR");
    }
display.setTextSize(1);
    display.setCursor(0, 56);
    display.println("XinaBox");
    display.setCursor(55, 56);
    display.println("0.1.1");
    display.setCursor(104, 56);
    display.println("ITR");
  }
}

void uiITR::sn01(uint8_t status, String lat, String lon, String alt)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    if (status == 0)
    {
      double _lat = atof(lat.c_str());
      if ((_lat < 0) && (_lat > -10))
      {
        display.setCursor(32, 24);
        display.println("Lat:   " + lat);
      }
      else if ((_lat < -10) && (_lat > -100))
      {
        display.setCursor(32, 24);
        display.println("Lat:  " + lat);
      }
      else if (_lat <= -100)
      {
        display.setCursor(32, 24);
        display.println("Lat: " + lat);
      }
      else if ((_lat >= 0) && (_lat < 10))
      {
        display.setCursor(32, 24);
        display.println("Lat:    " + lat);
      }
      else if ((_lat >= 10) && (_lat < 100))
      {
        display.setCursor(32, 24);
        display.println("Lat:   " + lat);
      }
      else if (_lat >= 100)
      {
        display.setCursor(32, 24);
        display.println("Lat:  " + lat);
      }


      double _lon = atof(lon.c_str());
      if ((_lon < 0) && (_lon > -10))
      {
        display.setCursor(32, 32);
        display.println("Lon:   " + lon);
      }
      else if ((_lon < -10) && (_lon > -100))
      {
        display.setCursor(32, 32);
        display.println("Lon:  " + lon);
      }
      else if (_lon <= -100)
      {
        display.setCursor(32, 32);
        display.println("Lon: " + lon);
      }
      else if ((_lon >= 0) && (_lon < 10))
      {
        display.setCursor(32, 32);
        display.println("Lon:    " + lon);
      }
      else if ((_lon >= 10) && (_lon < 100))
      {
        display.setCursor(32, 32);
        display.println("Lon:   " + lon);
      }
      else if (_lon >= 100)
      {
        display.setCursor(32, 32);
        display.println("Lon:  " + lon);
      }

      int32_t _alt = atof(alt.c_str());
      if ((_alt < 0) && (_alt > -10))
      {
        display.setCursor(32, 40);
        display.println("Alt:   " + alt);
      }
      else if ((_alt < -10) && (_alt > -100))
      {
        display.setCursor(32, 40);
        display.println("Alt:  " + alt);
      }
      else if (_alt <= -100)
      {
        display.setCursor(32, 40);
        display.println("Alt: " + alt);
      }
      else if ((_alt >= 0) && (_alt < 10))
      {
        display.setCursor(32, 40);
        display.println("Alt:    " + alt);
      }
      else if ((_alt >= 10) && (_alt < 100))
      {
        display.setCursor(32, 40);
        display.println("Alt:   " + alt);
      }
      else if (_alt >= 100)
      {
        display.setCursor(32, 40);
        display.println("Alt:  " + alt);
      }

    }
    else if (status == 1)
    {
      display.setCursor(49, 32);
      display.println("SN01 No Fix");
    }
    else
    {
      display.setCursor(35, 32);
      display.println("SN01 undetected");
    }
    display.drawBitmap(0, 20, markerIcon, 30, 27, WHITE);
    display.display();
  }
}

void uiITR::si01(bool status, String x, String y, String z)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.setTextSize(1);
    if (status)
    {
      display.setCursor(40, 24);
      display.println("Roll   : " + x);
      display.setCursor(40, 32);
      display.println("Pitch  : " + y);
      display.setCursor(40, 40);
      display.println("G-Force: " + z);
    }
    else
    {
      display.setCursor(37, 32);
      display.println("SI01 undetected");
    }
    display.drawBitmap(0, 22, tachIcon, 30, 27, WHITE);
    display.display();
  }
}

void uiITR::sw01(bool status, String temp, String hum, String pres)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.setTextSize(1);
    if (status)
    {
      display.setCursor(48, 24);
      display.println(temp + "   *C");
      display.setCursor(48, 32);
      display.println(hum + "   %RH");
      display.setCursor(48, 40);
      display.println(pres + " hPa");
    }
    else
    {
      display.setCursor(37, 32);
      display.println("SW01 undetected");
    }
    display.drawBitmap(0, 23, weatherIcon, 30, 24, WHITE);
    display.display();
  }
}

void uiITR::sw01_bitmap()
{
  display.drawBitmap(0, 23, weatherIcon, 30, 24, WHITE);
  //display.display();
}

void uiITR::sg33(bool status, String co2, String voc)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.setTextSize(1);
    if (status)
    {
      display.setCursor(40, 27);
      display.println("CO2 : " + co2);
      display.setCursor(40, 38);
      display.println("VOC : " + voc);
    }
    else
    {
      display.setCursor(37, 32);
      display.println("SG33 undetected");
    }
    display.drawBitmap(0, 23, smogIcon, 30, 24, WHITE);
    display.display();
  }
}

void uiITR::sl01(bool status, String lux, String uvi)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.setTextSize(1);
    if (status)
    {
      display.setCursor(40, 27);
      display.println("Lux : " + lux);
      display.setCursor(40, 38);
      display.println("UVI : " + uvi);
    }
    else
    {
      display.setCursor(37, 32);
      display.println("SL01 undetected");
    }
    display.drawBitmap(0, 21, sunIcon, 30, 30, WHITE);
    display.display();
  }
}

void uiITR::sdPass()
{
  if (xCore.ping(0x3C))
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.invertDisplay(false);
    iconAndString(sdIcon, "  SD PASS", 90, 44, 18, 18);
    //delay(1500);
  }
}

void uiITR::sdFail()
{
  if (xCore.ping(0x3C))
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.invertDisplay(true);
    iconAndString(sdIcon, "  SD FAIL", 90, 44, 18, 18);
    delay(1500);
  }
}

void uiITR::uifs(bool sn01, bool sg33, bool si01, bool sw01, bool sl01, bool rl0x, bool pb04)
{
  if (xCore.ping(0x3C))
  {
    fsState = "";
    if (sn01)
    {
      fsState += "SN01 pass\n";
    }
    else
    {
      fsState += "SN01 undetected\n";
    }

    if (sg33)
    {
      fsState += "SG33 pass\n";
    }
    else
    {
      fsState += "SG33 undetected\n";
    }

    if (si01)
    {
      fsState += "SI01 pass\n";
    }
    else
    {
      fsState += "SI01 undetected\n";
    }

    if (sw01)
    {
      fsState += "SW01 pass\n";
    }
    else
    {
      fsState += "SW01 undetected\n";
    }
    if (sl01)
    {
      fsState += "SL01 pass\n";
    }
    else
    {
      fsState += "SL01 undetected\n";
    }
    if (rl0x)
    {
      fsState += "RL0x pass\n";
    }
    else
    {
      fsState += "RL0x undetected\n";
    }

    if (pb04)
    {
      fsState += "PB04 pass\n";
    }
    else
    {
      fsState += "PB04 undetected\n";
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.invertDisplay(false);
    display.print(fsState);
    display.display();
    //Watchdog.reset();
  }
}

void uiITR::sg35(bool status, String p10, String p25, String p100)
{
  if (xCore.ping(0x3C))
  {
    display.invertDisplay(false);
    display.setTextSize(1);
    if (status)
    {
      display.setCursor(38, 24);
      display.println("1.0: " + p10);
      display.setCursor(95, 24);
      display.println("ug/m3");
      display.setCursor(38, 32);
      display.println("2.5: " + p25);
      display.setCursor(95, 32);
      display.println("ug/m3");
      display.setCursor(32, 40);
      display.println("10.0: " + p100);
      display.setCursor(95, 40);
      display.println("ug/m3");
    }
    else
    {
      display.setCursor(37, 32);
      display.println("SG35 undetected");
    }
    display.drawBitmap(0, 23, tachograph, 30, 24, WHITE);
    display.display();
  }
}

void uiITR::selectMode()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Select mode with Bttn");
  display.setTextSize(2);
  display.setCursor(0, 18);
  display.println("A: Indoor");
  display.setCursor(0, 40);
  display.println("B: Outdoor");
  display.setTextSize(1);
  display.display();
}
uiITR ui = uiITR();
