#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  dht.begin();
}

void loop() {
  float sum = 0;
  
  for(int i=0; i<6; i++){
    sum += dht.readHumidity();
    delay(1000);
  }

  float avg = sum / 6;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TB 6 lan do: "); 
  lcd.setCursor(0, 1);
  lcd.print(avg);
}
