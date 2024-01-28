#define TEMP_WARNING_THRESHOLD 60
#define TEMP_ERROR_THRESHOLD 80
#define SMOKE_WARNING_THRESHOLD 800
#define SMOKE_ERROR_THRESHOLD 900

#define RED D6
#define GREEN D7
#define BLUE D8


int yellowState = LOW;

unsigned long previousMillis = 0;
const long interval = 100;

void off() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void error() {
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void normal() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, LOW);
}

void offline() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
}

void warning() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (yellowState == LOW) {
      yellowState = HIGH;  // Note that this switches the LED *off*
    } else {
      yellowState = LOW;  // Note that this switches the LED *on*
    }

    digitalWrite(RED, yellowState);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }
}

void initStatus() {
  localStatus = 3;

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  off();
}

void showStatus() {
  switch (localStatus) {
    case 0:
      {
        normal();
        break;
      }
    case 1:
      {
        warning();
        break;
      }
    case 2:
      {
        error();
        break;
      }
    case 3:
      {
        offline();
        break;
      }
  }
}

void statusLoop() {
  if (testing) return;

  if (temp >= TEMP_ERROR_THRESHOLD or smoke >= SMOKE_ERROR_THRESHOLD) {
    localStatus = 2;
  } else if (temp >= TEMP_WARNING_THRESHOLD or smoke >= SMOKE_WARNING_THRESHOLD) {
    localStatus = 1;
  } else {
    if (ArduinoCloud.connected() == 0) {
      localStatus = 3;
    } else {
      localStatus = 0;
    }
  }

  status = localStatus;
}