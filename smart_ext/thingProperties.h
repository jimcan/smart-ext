#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[] = "17ad7fc0-343a-43e4-8317-9166130a5a01";

const char SSID[] = "Smart Ext";                      // Network SSID (name)
const char PASS[] = "SmartExt";                    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[] = "LVGELQMVDAOEPZOT1QKP";  // Secret device password

int localStatus;

void onStatusChange();
void onPowerChange();
void onTestingChange();

int status = 3;
float smoke;
bool power = true;
bool testing = false;
CloudTemperature temp;

void initProperties() {

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(status, READWRITE, ON_CHANGE, onStatusChange);
  ArduinoCloud.addProperty(power, READWRITE, ON_CHANGE, onPowerChange);
  ArduinoCloud.addProperty(testing, READWRITE, ON_CHANGE, onTestingChange);
  ArduinoCloud.addProperty(temp, READ, 10 * SECONDS, NULL);
  ArduinoCloud.addProperty(smoke, READ, 10 * SECONDS, NULL);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
