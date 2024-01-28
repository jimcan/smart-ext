#include "thingProperties.h"

void setup() {
  Serial.begin(19200);
  delay(1500);
  initStatus();
  initProperties();
  setupTemp();
  initLcd();
  initPower();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  tempLoop();
  smkLoop();
  statusLoop();
  powerLoop();
  showStatus();
  displayLoop();
}

void onStatusChange() {
  if (testing) localStatus = status;
}

void onPowerChange() {}
void onTestingChange() {}