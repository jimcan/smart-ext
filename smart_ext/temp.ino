#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to GPIO2
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setupTemp() {
  sensors.begin();
}

void tempLoop() {
  sensors.requestTemperatures();  
  temp = sensors.getTempCByIndex(0);
}
