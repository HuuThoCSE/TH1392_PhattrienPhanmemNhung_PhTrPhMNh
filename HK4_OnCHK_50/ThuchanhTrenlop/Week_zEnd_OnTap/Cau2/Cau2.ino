#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE SDA
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

float h, t = 0;

unsigned long time_cur = 0;
unsigned long time_last = 0;
unsigned long time_ledC = 2000;


#define ledC 3

void setup() {
  lcd.init();
  dht.begin();

  pinMode(ledC, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("21022008");
  lcd.setCursor(0, 1);
  lcd.print("Nguyen Huu Tho");
  // delay(15000);
  delay(100);
  lcd.clear();
}

void showlcd(){
  h = dht.readHumidity();
  t = dht.readTemperature();

  lcd.setCursor(0, 0);
  lcd.print("Nhiet do: ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Do am: ");
  lcd.print(h);
  lcd.print("%");  
}

void loop() {
  showlcd();
  time_cur = millis();
  if(t > 30){
    if(time_cur - time_last > time_ledC){
      digitalWrite(ledC, !digitalRead(ledC));
      time_last = time_cur;
    } else {
      digitalWrite(ledC, LOW);
    }
  }
}
