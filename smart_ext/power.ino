#define POWER D0

void initPower() {
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, LOW);
}

void powerLoop() {
  power = power && localStatus != 2;

  if (power) {
    digitalWrite(POWER, LOW);
  } else {
    digitalWrite(POWER, HIGH);
  }
}