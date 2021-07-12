void sensor_display(uint8_t i)
{
  switch (i)
  {
    case 0:
      read_for_display();
      if (ack._sw01) {
        ui.sw01(true, data.temperature, data.humidity, data.pressure);
      } else {
        ui.sw01(false, data.temperature, data.humidity, data.pressure);
      }
      break;
    case 1:
      read_for_display();
      if (ack._sg33) {
        ui.sg33(true, data.co2 + "ppm", data.tvoc + "ppb");
      } else {
        ui.sg33(false, data.co2 + "ppm", data.tvoc + "ppb");
      }
      break;
    case 2:
      read_for_display();
      if (ack._sn01 && ((atof(data.hdop.c_str()) < 20) && atof(data.hdop.c_str()) > 0)) {
        ui.sn01(0, data.latitude, data.longitude, data.altitude);
      } else if (ack._sn01 && atof(data.hdop.c_str()) > 20) {
        ui.sn01(1, data.latitude, data.longitude, data.altitude);
      } else {
        ui.sn01(2, data.latitude, data.longitude, data.altitude);
      }
      break;
    case 3:
      read_for_display();
      if (ack._sg35) {
        ui.sg35(true, data.pm10, data.pm25, data.pm100);
      } else {
        ui.sg35(false, data.pm10, data.pm25, data.pm100);
      }
      break;
    default:
      for (uint8_t i = 0; i < 20; i++) {
        read_for_display();
        if (ack._sw01) {
          ui.sw01(true, data.temperature, data.humidity, data.pressure);
        } else {
          ui.sw01(false, data.temperature, data.humidity, data.pressure);
        }
        delay(50);
      }
      for (uint8_t i = 0; i < 20; i++) {
        read_for_display();
        if (ack._sg33) {
          ui.sg33(true, data.co2 + "ppm", data.tvoc + "ppb");
        } else {
          ui.sg33(false, data.co2 + "ppm", data.tvoc + "ppb");
        }
        delay(50);
      }
      for (uint8_t i = 0; i < 20; i++) {
        read_for_display();
        if (ack._sn01) {
          ui.sn01(0, data.latitude, data.longitude, data.altitude);
        } else {
          ui.sn01(2, data.latitude, data.longitude, data.altitude);
        }

        delay(50);
      }
      for (uint8_t i = 0; i < 20; i++) {
        read_for_display();
        if (ack._sg35) {
          ui.sg35(true, data.pm10, data.pm25, data.pm100);
        } else {
          ui.sg35(false, data.pm10, data.pm25, data.pm100);
        }
        delay(50);
      }
  }
}

void read_for_display()
{
  sensor_read();
  if (mode==2) {
  if (atof(data.hours.c_str()) < 10) {
    data.hours = "0" + data.hours;
  }
  if (atof(data.minutes.c_str()) < 10) {
    data.minutes = "0" + data.minutes;
  }
  if (atof(data.seconds.c_str()) < 10) {
    data.seconds = "0" + data.seconds;
  }

  if (atof(data.day.c_str()) < 10) {
    data.day = "0" + data.day;
  }
  if (atof(data.month.c_str()) < 10) {
    data.month = "0" + data.month;
  }
  }
  ui.info(mode, data.hours + ":" + data.minutes + ":" + data.seconds + " Z", data.year + "-" + data.month + "-" + data.day, data.hdop, data.sats);
}
