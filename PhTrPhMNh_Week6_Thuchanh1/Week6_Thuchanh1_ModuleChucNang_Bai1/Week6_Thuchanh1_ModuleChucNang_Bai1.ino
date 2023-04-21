#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
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
  lcd.init();
  lcd.createChar(0, customChar);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("21022008");
  lcd.setCursor(0,1);
  lcd.print("Nguyen Huu Tho");
  delay(3000);
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.write(0);
  delay(1000);
  lcd.clear();
}
