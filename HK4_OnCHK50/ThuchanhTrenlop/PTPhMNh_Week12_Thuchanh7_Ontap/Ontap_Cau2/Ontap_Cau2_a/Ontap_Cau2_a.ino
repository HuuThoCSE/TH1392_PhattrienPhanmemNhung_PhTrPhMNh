#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "DHT.h"
#define DHTPIN 8

#define DHTTYPE DHT11
#define pinLedC 10
#define pinBuzzer 2

LiquidCrystal_I2C lcd(0x27,16,2);

DHT dht(DHTPIN, DHTTYPE);

unsigned long now = 0;
unsigned long timeLedC = 0;

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(pinLedC, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  now = millis();
  // float t = dht.readTemperature();
  // float t = 29;
  float t = 31;
  // float t = 40;
  // float h = dht.readHumidity();
  // float h = 33;
  float h = 32;

  lcd.setCursor(0,0);
  lcd.print("Nhiet do: ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.print(h);
  lcd.print("%");

  if(t > 30){
    if(now - timeLedC >= 2000){
      digitalWrite(pinLedC, !digitalRead(pinLedC));
      timeLedC = now;
    }
  } else {
    digitalWrite(pinLedC, LOW);
  }

  if(h > 32 && t < 40){
    digitalWrite(pinBuzzer, 1);
  } else {
    digitalWrite(pinBuzzer, 0);
  }
}
