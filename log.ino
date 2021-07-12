String _fileName;

bool log_heading(String heading)
{
  //#ifdef _MICROBIT_V2_
  SD.begin(_sd_cs);
  //#endif
  uint16_t count = getFileCount("DATA");

  String fileName = "DATA/DATA_" + String(count + 1) + ".CSV";
  _fileName = fileName;
  File dataFile = SD.open(_fileName, FILE_WRITE);
  if (dataFile) {
    dataFile.println(heading);
    dataFile.close();
    // print to the serial port too:
    //Serial.println(heading);
    return true;
  }
  return false;
}

String data_string()
{
  String finalDataString = "";
#ifdef DEVELOPER_DEBUG
  finalDataString += String(millis()) + "," +
#endif
                     finalDataString +=       data.latitude + "," +
                         data.longitude + "," +
                         data.latitudedms + "," +
                         data.longitudedms + "," +
                         data.altitude + "," +
                         data.speed + "," +
                         data.hdop + "," +
                         data.day + "," +
                         data.month + "," +
                         data.year + "," +
                         data.hours + "," +
                         data.minutes + "," +
                         data.seconds + "," +
                         data.temperature + "," +
                         data.pressure + "," +
                         data.humidity + "," +
                         data.co2 + "," +
                         data.tvoc  + "," +
                         data.pm10  + "," +
                         data.pm25  + "," +
                         data.pm100;
  return finalDataString;
}

void log_data(String data)
{
  //#ifdef _MICROBIT_V2_
  SD.begin(_sd_cs);
  //#endif
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(_fileName, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    // print to the serial port too:
    ////Serial.println(data);
  }
  // if the file isn't open, pop up an error:
  else {
    //debugPrint("error opening " + _fileName);
  }
}

int getFileCount(String dir)
{
  File d = SD.open(dir);
  int count_files = 0;
  while (true)
  {
    File entry =  d.openNextFile();
    if (!entry)
    {
      // no more files. Let's return the number of files.
      return count_files;
    }
    String file_name = entry.name();  //Get file name so that we can check
    //if it's a duplicate
    if ( file_name.indexOf('~') != 0 )  //Igrnore filenames with a ~. It's a mac thing.
    { //Just don't have file names that have a ~ in them
      count_files++;
    }
  }
}

void getDetails()
{
//  Wire.begin();
//  xOD01 OD01;
//  OD01.begin();
//  OD01.clear();

  if (!SD.begin(_sd_cs)) {
    Wire.begin();
    ui.sdFail();
    return;
  }
  SD.begin(_sd_cs);
  File myFile;
  if (SD.exists("CONFIG/WIFISSID.txt")) {
    myFile = SD.open("CONFIG/WIFISSID.txt", FILE_READ);
    while (myFile.available()) {
      cw01_vars.ssid += (char)myFile.read();
    }
    myFile.close();
    Wire.begin();
    //OD01.println(cw01_vars.ssid);
    ui.sdPass();
  }
  SD.begin(_sd_cs);
  if (SD.exists("CONFIG/WIFIPASS.txt")) {
    myFile = SD.open("CONFIG/WIFIPASS.txt", FILE_READ);
    while (myFile.available()) {
      cw01_vars.pass += (char)myFile.read();
    }
    myFile.close();
    Wire.begin();
    //OD01.println(cw01_vars.pass);
    ui.sdPass();
  }
  SD.begin(_sd_cs);
  if (SD.exists("CONFIG/ATTID.txt")) {
    myFile = SD.open("CONFIG/ATTID.txt", FILE_READ);
    while (myFile.available()) {
      cw01_vars.DEVICE_ID += (char)myFile.read();
    }
    myFile.close();
    Wire.begin();
    //OD01.println(cw01_vars.DEVICE_ID);
    ui.sdPass();
  }
  SD.begin(_sd_cs);
  if (SD.exists("CONFIG/ATTTOKEN.txt")) {
    myFile = SD.open("CONFIG/ATTTOKEN.txt", FILE_READ);
    while (myFile.available()) {
      cw01_vars.TOKEN += (char)myFile.read();
    }
    myFile.close();
    Wire.begin();
    //OD01.println(cw01_vars.TOKEN);
    ui.sdPass();
  }
}
