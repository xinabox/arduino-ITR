#include <xOD01.h>
void connectToWifi(String ssid, String pass)
{
  String _temp = "AT+CWMODE=1";
  Serial.println(_temp.c_str());
  delay(100);
  Serial.readString();
  _temp = "AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"" + "";
  Serial.println(_temp.c_str());
  delay(200);

  uint16_t loop_count = 0;
  String res;
  do {
    res = Serial.readString();
    //    xOD01 OD01;
    //    OD01.begin();
    //    OD01.clear();
    //    OD01.println(res);
    Wire.begin();
    ui.connectingToWifi("  Connecting to WiFi");
    delay(1000);
    loop_count++;

    if (loop_count == 20)
      break;
  } while (strstr(res.c_str(), "WIFI CONNECTED") == NULL);
  if (strstr(res.c_str(), "WIFI CONNECTED") != NULL) {
    Wire.begin();
    ui.wifiPass(" WIFI PASS");
    delay(2000);
    res = "";
    return;
  }

  if (loop_count == 20)
  {
    Wire.begin();
    ui.wifiFail(" WIFI FAIL");
    delay(2000);
  }
}

void connectToATT(String ID, String TKN)
{
  cw01_vars.DEVICE_ID = ID;
  cw01_vars.TOKEN = TKN;
  Serial.println("AT+CIPSTART=\"TCP\",\"api.allthingstalk.io\",80");
  delay(500);
}

void IoTSendValueToATT(int value, String asset)
{
  String att_connected = "";

  //  while (cw01_button_object.sending_data) {
  //    basic.pause(100)
  //  }
  //
  //  cw01_button_object.sending_data = true

  do {
    sensor_display(screenCount);
    cw01_vars.asset_name = asset;
    Serial.println("AT+CIPMODE=0");
    String payload = "{\"value\": " + String(value) + "}";
    String request = "PUT /device/" + cw01_vars.DEVICE_ID + "/asset/" + cw01_vars.asset_name + "/state" + " HTTP/1.1" + cw01_vars.NEWLINE +
                     "Host: api.allthingstalk.io" + cw01_vars.NEWLINE +
                     "User-Agent: CW01/1.0" + cw01_vars.NEWLINE +
                     "Accept: */*" + cw01_vars.NEWLINE +
                     "Authorization: Bearer " + cw01_vars.TOKEN + cw01_vars.NEWLINE +
                     "Content-Type:application/json" + cw01_vars.NEWLINE +
                     "Content-Length: " + String(payload.length()) + cw01_vars.NEWLINE + cw01_vars.NEWLINE + payload;


    Serial.println("AT+CIPSEND=" + String((request.length() + 2)));
    delay(50);
    Serial.println(request);
    //delay(1000);

    att_connected = Serial.readString();

    //OD01.println("ATT: " + String(att_connected));
    if (strstr(att_connected.c_str(), "link is not valid") != NULL) {
      connectToATT(cw01_vars.TOKEN, cw01_vars.DEVICE_ID);
    } else {
      att_connected = "";
    }

    //get_status()

  } while (strstr(att_connected.c_str(), "link is not valid") != NULL);

  //cw01_button_object.sending_data = false
}

void sendLocationToAtt(String asset)
{
  String att_connected = "";

  //  while (cw01_button_object.sending_data) {
  //    basic.pause(100)
  //  }
  //
  //  cw01_button_object.sending_data = true

  do {
    sensor_display(screenCount);
    cw01_vars.asset_name = asset;
    Serial.println("AT+CIPMODE=0");
    delay(100);
    String payload = "{\"value\": {\"latitude\":" + data.latitude + ", \"longitude\":" + data.longitude + "} }";
    String request = "PUT /device/" + cw01_vars.DEVICE_ID + "/asset/" + cw01_vars.asset_name + "/state" + " HTTP/1.1" + cw01_vars.NEWLINE +
                     "Host: api.allthingstalk.io" + cw01_vars.NEWLINE +
                     "User-Agent: CW01/1.0" + cw01_vars.NEWLINE +
                     "Accept: */*" + cw01_vars.NEWLINE +
                     "Authorization: Bearer " + cw01_vars.TOKEN + cw01_vars.NEWLINE +
                     "Content-Type:application/json" + cw01_vars.NEWLINE +
                     "Content-Length: " + String(payload.length()) + cw01_vars.NEWLINE + cw01_vars.NEWLINE + payload;


    Serial.println("AT+CIPSEND=" + String((request.length() + 2)));
    delay(50);
    Serial.println(request);
    //delay(1000);
    att_connected = Serial.readString();
    //OD01.println("ATT: " + String(att_connected));
    if (strstr(att_connected.c_str(), "link is not valid") != NULL) {
      connectToATT(cw01_vars.TOKEN, cw01_vars.DEVICE_ID);
    } else {
      att_connected = "";
    }

    //get_status()

  } while (strstr(att_connected.c_str(), "link is not valid") != NULL);

  //cw01_button_object.sending_data = false
}

void IoTSendStringToATT(String value, String asset)
{

  String att_connected = "";
  //  while (cw01_button_object.sending_data) {
  //    basic.pause(100)
  //  }
  //
  //  cw01_button_object.sending_data = true
  do {
    sensor_display(screenCount);
    cw01_vars.asset_name = asset;
    Serial.println("AT+CIPMODE=0");
    delay(100);
    String payload = "{\"value\": \"" + value + "\"}";
    String request = "PUT /device/" + cw01_vars.DEVICE_ID + "/asset/" + cw01_vars.asset_name + "/state" + " HTTP/1.1" + cw01_vars.NEWLINE +
                     "Host: api.allthingstalk.io" + cw01_vars.NEWLINE +
                     "User-Agent: CW01/1.0" + cw01_vars.NEWLINE +
                     "Accept: */*" + cw01_vars.NEWLINE +
                     "Authorization: Bearer " + cw01_vars.TOKEN + cw01_vars.NEWLINE +
                     "Content-Type:application/json" + cw01_vars.NEWLINE +
                     "Content-Length: " + String(payload.length()) + cw01_vars.NEWLINE + cw01_vars.NEWLINE + payload;
    Serial.println("AT+CIPSEND=" + String((request.length() + 2)));
    delay(50);
    Serial.println(request);
    //delay(1000);
    att_connected = Serial.readString();
    //OD01.println("ATT: " + String(att_connected));
    if (strstr(att_connected.c_str(), "link is not valid") != NULL) {
      connectToATT(cw01_vars.TOKEN, cw01_vars.DEVICE_ID);
    } else {
      att_connected = "";
    }
    //get_status()
  } while (strstr(att_connected.c_str(), "link is not valid") != NULL);
  //cw01_button_object.sending_data = false
}

void sendDataToAtt()
{
  if (ack._sw01) {
    IoTSendValueToATT(atof(data.pressure.c_str()), "9");
    IoTSendValueToATT(atof(data.temperature.c_str()), "8");
    IoTSendValueToATT(atof(data.humidity.c_str()), "10");
  }

  if (ack._sg35) {
    if (ack._sn01_gps_ready || mode == 1) {
      IoTSendValueToATT(atof(data.pm25.c_str()), "3");
      IoTSendValueToATT(atof(data.pm100.c_str()), "2");
      IoTSendValueToATT(atof(data.pm10.c_str()), "1");
    }
  }

  if (ack._sg33) {
    IoTSendValueToATT(atof(data.tvoc.c_str()), "12");
    IoTSendValueToATT(atof(data.co2.c_str()), "11");
  }

  if (ack._sn01) {
    if (mode == 2) {
      if ((atof(data.hdop.c_str()) < 30) && (atof(data.hdop.c_str()) > 0)) {
        sendLocationToAtt("Location");
      }
      IoTSendStringToATT(data.hours + ":" + data.minutes + ":" + data.seconds + " Z" , "7");
      IoTSendStringToATT(data.year + "-" + data.month + "-" + data.day, "6");
    }
  }
}
