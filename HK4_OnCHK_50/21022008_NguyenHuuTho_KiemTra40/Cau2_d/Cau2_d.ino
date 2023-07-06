#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "DHT.h"
#define DHTPIN 8

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  dht.begin();
  
  lcd.init();
  lcd.backlight();
}

float arr_humi[6];

void loop() {
  for(int i=6; i >= 0; i--){
    arr_humi[i] = arr_humi[i-1];
  }

  float h = dht.readHumidity();
  arr_humi[0] = h;
 
  float sum = 0;
  float avg = 0;
  for(int i=0; i<6; i++){
    sum += arr_humi[i];
  }

  avg = sum / 6;

  lcd.setCursor(0,0);
  lcd.print("Do am t/b: ");
  lcd.setCursor(0,1);
  lcd.print(avg);
  lcd.print("%");

  delay(500);
}
