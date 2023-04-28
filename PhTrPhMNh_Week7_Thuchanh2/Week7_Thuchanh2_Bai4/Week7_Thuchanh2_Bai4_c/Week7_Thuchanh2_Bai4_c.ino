#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinLM35 A0

#define gLed 11
#define yLed 12
#define rLed 13

LiquidCrystal_I2C lcd(0x27, 16, 2);

int typeShow = 0;

void setup() {
  pinMode(pinLM35, INPUT);
  pinMode(gLed, OUTPUT);
  pinMode(yLed, OUTPUT);
  pinMode(rLed, OUTPUT);
  lcd.init();
  Serial.begin(9600);
}

void loop() {
  // Đọc giá trị từ cảm biến LM35
  int rawValue = analogRead(pinLM35);
  float voltage = rawValue * (5.0 / 1023.0);
  float temp = voltage * 100.0;

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.print(" C");
  
  if(temp < 17){
    digitalWrite(gLed, 1);
    digitalWrite(yLed, 0);
    digitalWrite(rLed, 0);
  } else if(temp >= 17 && temp <= 30){
    digitalWrite(gLed, 0);
    digitalWrite(yLed, 1);
    digitalWrite(rLed, 0);
  } else if(temp > 30) {
    digitalWrite(gLed, 0);
    digitalWrite(yLed, 0);
    digitalWrite(rLed, 1);
  }

  delay(100);
}
