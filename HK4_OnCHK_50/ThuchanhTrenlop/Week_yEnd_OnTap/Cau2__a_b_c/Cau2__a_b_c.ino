#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define ledC 3

unsigned long time_cur = 0;
unsigned long time_last = 0;
unsigned long time_ledC = 2000;

void setup() {
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("21022008");
  lcd.setCursor(0, 1);
  lcd.print("Nguyen Huu Tho");
  // delay(15000);
  delay(1000);
  lcd.clear();
  dht.begin();

  pinMode(ledC, OUTPUT);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do: "); lcd.print(t); lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Do am: "); lcd.print(h); lcd.print("%");

  if(t  > 30){
      time_cur = millis();
      if(time_cur - time_last >= time_ledC){
        digitalWrite(ledC, !digitalRead(ledC));
        time_last = time_cur;
      }{
        digitalWrite(ledC, LOW);
      }
  }
}
