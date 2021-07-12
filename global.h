#ifndef _GLOBAL_
#define _GLOBAL_

#include <xCore.h>
#include <xSG35.h>
#include <xSW01.h>
#include <xSN01.h>
#include <xSG33.h>
#include <SPI.h>
#include <SD.h>
#include <math.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;
xSG35 SG35;
xSG35::DATA sg35Data;
xSW01 SW01;
xSN01 SN01;
xSG33 SG33;

#define debugPrint(x) Serial.print(x)
#define ITR_FW_VERSION "0.1.1"

#define DEVELOPER_DEBUG 1
enum xchipAddr {
  _sn01_i2c = 0x42,
  _sw01_i2c = 0x76,
  _sg33_i2c = 0x5A,
  _sg33_i2c_1 = 0x58,
  _sg35_i2c = 0x4D,
  _od01_i2c = 0x3C,
  _sd_cs = 16,
};

struct acks {
  bool _sn01 = false;
  bool _sw01 = false;
  bool _sg33 = false;
  bool _sg35 = false;
  bool _im01 = false;
  bool _od01 = false;
  bool _sd = false;
  bool _sn01_gps_ready = false;
  bool _sg35_awake = false;
} ack;

struct sensor_data {
#ifdef DEVELOPER_DEBUG
  const String dataHeading = "millis(), Latitude,Longitude,Latitude(DMS),Longitude(DMS),Altitude(m),Speed(kmph),HDOP,Day,Month,Year,Hours,Minutes,Seconds,"
#else
  const String dataHeading = "Latitude,Longitude,Latitude(DMS),Longitude(DMS),Altitude(m),Speed(kmph),HDOP,Day,Month,Year,Hours,Minutes,Seconds,"
#endif
                             "Temperature(C),Pressure(hPa),Humidity(%),"
                             "C02(ppm),TVOC(ppb),"
                             "PM 1.0(ug/m3),PM 2.5(ug/m3),PM 10.0(ug/m3)";
  String latitude;
  String longitude;
  String latitudedms;
  String longitudedms;
  String altitude;
  String speed;
  String hdop;
  String sats;
  String day;
  String month;
  String year;
  String hours;
  String minutes;
  String seconds;
  String temperature;
  String pressure;
  String humidity;
  String co2;
  String tvoc;
  String pm10;
  String pm25;
  String pm100;
  String _time = hours + ":" + minutes + ":" + seconds + " Z";
  String _date = year + "-" + month + "-" + day;
} data;

struct vars {
  String ssid = "";
  String pass = "";
  String TOKEN = "";
  String DEVICE_ID = "";
  String asset_name = "temperature";
  String NEWLINE = "\r\n";
} cw01_vars;

#endif
