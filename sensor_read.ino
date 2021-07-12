void sensor_read()
{
  if (!check_xchips()) {
    //Serial.println("chip not there");
    xchip_setup();
  }
  //#ifdef _MICROBIT_V2_
  Wire.begin();
  //#endif

  if (ack._sg35) {
    //Serial.println("SG35 ACK");
    if (ack._sn01_gps_ready || mode == 1) {
      //Serial.println("SN01 GPS READY");
      if (!ack._sg35_awake) {
        SG35.begin();
        //Serial.println("SG35 ENABLE");
        SG35.enable();
        ack._sg35_awake = true;
      }
      uint8_t sg35Count = 0;
      while (!SG35.read(sg35Data)) {
        sg35Count++;
        if (sg35Count == 20) break;
      }

      if (sg35Count < 20) {
        data.pm10 = String(sg35Data.PM_AE_UG_1_0);
        data.pm25 = String(sg35Data.PM_AE_UG_2_5);
        data.pm100 = String(sg35Data.PM_AE_UG_10_0);
      }
    }  else {
      SG35.disable();
      ack._sg35_awake = false;
      data.pm10 = "";
      data.pm25 = "";
      data.pm100 = "";
    }
  } else {
    data.pm10 = "";
    data.pm25 = "";
    data.pm100 = "";
  }
  if (mode == 2) {
    if (ack._sn01) {
      SN01.poll();
      data.day = String(SN01.getDay());
      data.month = String(SN01.getMonth());
      data.year = String(SN01.getYear());

      data.hours = String(SN01.getHour());
      data.minutes = String(SN01.getMinute());
      data.seconds = String(SN01.getSecond());
      data.sats = String(SN01.getSatelitesConnected());

      float _lat = SN01.getLatitude();
      float _long = SN01.getLongitude();
      data.latitude = String(_lat, 6);
      data.longitude = String(_long, 6);
      data.latitudedms = DegreesToDegMinSec(_lat);
      data.longitudedms = DegreesToDegMinSec(_long);
      data.altitude = String(SN01.getAltitude());
      data.hdop = String((int)SN01.getHDOP());
      data.speed = String(SN01.getCOG());

      if ((atof(data.hdop.c_str()) < 20 && atof(data.hdop.c_str()) > 0 ) || (millis() > 600000UL)) {
        ////Serial.println("HDOP: " + data.hdop);
        ack._sn01_gps_ready = true;
      } else {
        data.latitude = "";
        data.longitude = "";
        data.latitudedms = "";
        data.longitudedms = "";
        data.altitude = "";
        data.speed = "";
      }
    } else {
      data.latitude = "";
      data.longitude = "";
      data.latitudedms = "";
      data.longitudedms = "";
      data.altitude = "";
      data.hdop = "";
      data.speed = "";
      data.day = "";
      data.month = "";
      data.year = "";
      data.hours = "";
      data.minutes = "";
      data.seconds = "";
    }
  }

  if (ack._sw01) {
    SW01.poll();
    data.temperature = String(SW01.getTempC());
    data.humidity = String(SW01.getHumidity());
    data.pressure = String(SW01.getPressure() / 100);
  } else {
    data.temperature = "";
    data.humidity = "";
    data.pressure = "";
  }

  if (ack._sg33) {
    if (xCore.ping(_sg33_i2c)) {
      if (SG33.dataAvailable())
      {
        SG33.getAlgorithmResults();
        if (ack._sw01) {
          SG33.setEnvironmentData(atof(data.humidity.c_str()), atof(data.temperature.c_str()));
        }
        data.co2 = String(SG33.getCO2());
        data.tvoc = String(SG33.getTVOC());
      } else {
        //        data.co2 = "";
        //        data.tvoc = "";
      }
    } else if (xCore.ping(_sg33_i2c_1)) {
      if (ack._sw01) {
        sgp.setHumidity(getAbsoluteHumidity(atof(data.temperature.c_str()), atof(data.humidity.c_str())));
      }
      if (sgp.IAQmeasure()) {
        data.co2 = String(sgp.eCO2);
        data.tvoc = String(sgp.TVOC);
      } else {
        //        data.co2 = "";
        //        data.tvoc = "";
      }
    }
  } else {
    data.co2 = "";
    data.tvoc = "";
  }
}

String DegreesToDegMinSec(float x)
{
  double decimal_degrees = (double)x;
  double fractional_degrees, integer_degrees;
  fractional_degrees = modf(decimal_degrees, &integer_degrees);

  int degrees = (int)integer_degrees;
  int minutes = (int)(fractional_degrees * 60);
  double seconds = minutes * 60;

  return String(degrees) + "°" + String(minutes) + "'" + String(seconds, 2) + "\"";
}

uint32_t getAbsoluteHumidity(float temperature, float humidity) {
  // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
  const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
  const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
  return absoluteHumidityScaled;
}
