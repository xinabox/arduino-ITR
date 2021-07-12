#include "uiITR.h"
#include "global.h"

volatile int8_t screenCount = 0;
volatile bool screenMode = false;
uint8_t mode = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(PIN_BUTTON_B, INPUT);
  Wire.begin();
  ui.begin();
  ui.drawXinaBoxLogo();
  delay(2000);
  ui.selectMode();
  while (mode == 0) {
    if (!digitalRead(PIN_BUTTON_A))
    {
      mode = 1;
    }
    if (!digitalRead(PIN_BUTTON_B))
    {
      mode = 2;
    }
    if (millis() > 180000UL) {
      mode=2;
      break;
    }
  }
  getDetails();
  connectToWifi(cw01_vars.ssid, cw01_vars.pass);
  connectToATT(cw01_vars.DEVICE_ID, cw01_vars.TOKEN);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_A), pina_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_B), pinb_ISR, RISING);
  //#ifndef _MICROBIT_V2_
  //Wire.begin();
  //#endif

  xchip_setup();
  delay(1000);
  log_heading(data.dataHeading);
  
}
unsigned long previousMillis;
void loop() {
  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis > 500) {
//    previousMillis = currentMillis;
    sensor_read();
    sendDataToAtt();
//  }
  
//  currentMillis = millis();
//  if (currentMillis - previousMillis > 200) {
//    previousMillis = currentMillis;
    sensor_display(screenCount);
//  }
  
  currentMillis = millis();
  if (currentMillis - previousMillis > 3000) {
    previousMillis = currentMillis;
    //sensor_read();
    log_data(data_string());
  }
}

void pina_ISR() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200)
  {
    screenCount--;
    if (mode != 2) {
      if (screenCount == 2) {
        screenCount--;
      }
    }
    if (screenCount == -1) screenCount = 3;
  }
  last_interrupt_time = interrupt_time;
}

void pinb_ISR() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200)
  {
    screenCount++;
    if (mode != 2) {
      if (screenCount == 2) {
        screenCount++;
      }
    }
    if (screenCount == 4) screenCount = 0;
  }
  last_interrupt_time = interrupt_time;
}
