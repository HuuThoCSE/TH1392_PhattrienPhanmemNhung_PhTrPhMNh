#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  dht.begin();
}

void loop() {
  float sum = 0;

  for(int i=0; i < 6; i++){ // Exp: Chú ý dòng for
    sum += dht.readTemperature();;
    delay(500);
  }

  float avg = sum / 6;

  lcd.setCursor(0, 0);
  lcd.print("Nhiet do tb 6lan: "); 
  lcd.setCursor(0, 1);
  lcd.print(avg); lcd.print("C");

  delay(1000);
}
