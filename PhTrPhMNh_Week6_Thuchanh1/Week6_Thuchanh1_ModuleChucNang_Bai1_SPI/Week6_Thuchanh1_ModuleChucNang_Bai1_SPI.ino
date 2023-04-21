#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte customChar[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(1, customChar);
  lcd.setCursor(0,0);
  lcd.print("21022008");
  lcd.setCursor(0,1);
  lcd.print("Nguyen Huu Tho");
  delay(3000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.write(1);
  delay(1000);
  lcd.clear();
}
