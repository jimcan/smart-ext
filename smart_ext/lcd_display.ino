#include <LiquidCrystal_I2C.h>

#define BLANK "                "
#define ON "ON"
#define OFF "OFF"
#define ONLINE "Online"
#define OFFLINE "Offline"
#define WARN "Warning"
#define ERR "Error"

LiquidCrystal_I2C lcd(0x27, 16, 2);

String prevPower;
String prevStatus;

void initLcd() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  print("Smart Extension");
  delay(1000);
  print("Power : ");
  print2("Status: ");
}

void print(const char* text) {
  lcd.setCursor(0, 0);
  lcd.print(BLANK);
  lcd.setCursor(0, 0);
  lcd.print(text);
}

void print2(const char* text) {
  lcd.setCursor(0, 1);
  lcd.print(BLANK);
  lcd.setCursor(0, 1);
  lcd.print(text);
}

void printPower() {
  String s;
  switch (localStatus) {
    case 1:
      {
        s = WARN;
        break;
      }
    case 2:
      {
        s = ERR;
        break;
      }
    case 3:
      {
        s = OFFLINE;
        break;
      }
    case 0:
    default:
      {
        s = ONLINE;
      }
  }

  if (prevStatus != s) {
    lcd.setCursor(8, 1);
    lcd.print("         ");
    lcd.setCursor(8, 1);
    lcd.print(s.c_str());

    prevStatus = s;
  }
}

void printStatus() {
  String currPower = power ? ON : OFF;

  if (prevPower != currPower) {
    lcd.setCursor(8, 0);
    lcd.print("         ");
    lcd.setCursor(8, 0);
    lcd.print(currPower);

    prevPower = currPower;
  }
}

  void displayLoop() {
    printPower();
    printStatus();
  }