void xchip_setup()
{
  if (!ack._sd) {
    //debugPrint("Initializing SD card...\n");
    if (SD.begin(_sd_cs)) {
      //ui.sdPass();
      //delay(1000);
      //debugPrint("card initialized.\n");
      ack._sd = true;
    } else {
      //ui.sdFail();
      //delay(1000);
      ack._sd = false;
    }
  }
  //#ifdef _MICROBIT_V2_
  Wire.begin();
  //#endif

  if (!ack._sg35) {
    if (xCore.ping(_sg35_i2c)) {
    //  if (SG35.begin()) {
        //Serial.println("SG35 BEGIN");
        ack._sg35 = true;
    //  } else {
        ack._sg35 = false;
    //  }
    } else {
      ack._sg35 = false;
    }
  }
  if (mode == 2) {
    if (!ack._sn01) {
      if (xCore.ping(_sn01_i2c)) {
        if (SN01.begin()) {
          ack._sn01 = true;
        } else {
          ack._sn01 = false;
        }
      }
    }
  }
  if (!ack._sw01) {
    if (xCore.ping(_sw01_i2c)) {
      if (SW01.begin()) {
        ack._sw01 = true;
      } else {
        ack._sw01 = false;
      }
    }
  }
  if (!ack._sg33) {
    if (xCore.ping(_sg33_i2c)) {
      if (SG33.begin()) {
        ack._sg33 = true;
      } else {
        ack._sg33 = false;
      }
    } else if (xCore.ping(_sg33_i2c_1)) {
      if (sgp.begin()) {
        ack._sg33 = true;
      } else {
        ack._sg33 = false;
      }
    }
  }

  if (!ack._od01) {
    if (xCore.ping(_od01_i2c)) {
      if (ui.begin()) {
        ack._od01 = true;
      } else {
        ack._od01 = false;
      }
    }
  }
}

bool check_xchips()
{
  Wire.begin();
  if (xCore.ping(_sw01_i2c)) {
    ack._sw01 = true;
  } else {
    ack._sw01 = false;
  }

  if (mode == 2) {
    if (xCore.ping(_sn01_i2c)) {
      ack._sn01 = true;
    } else {
      ack._sn01 = false;
    }
  }
    if (xCore.ping(_sg33_i2c) || xCore.ping(_sg33_i2c_1)) {
      ack._sg33 = true;
    } else {
      ack._sg33 = false;
    }

  if (xCore.ping(_od01_i2c)) {
    ack._od01 = true;
  } else {
    ack._od01 = false;
  }

  if (xCore.ping(_sg35_i2c)) {
    ack._sg35 = true;
  } else {
    ack._sg35 = false;
  }

  if ((ack._sg33 & ack._sg35 & ack._sw01 & ack._sn01 & ack._od01) != 0) return true;
  return false;
}
