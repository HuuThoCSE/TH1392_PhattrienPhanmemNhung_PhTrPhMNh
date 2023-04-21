#include <LiquidCrystal.h>

#include <DHT.h>
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define pinSOIL A0

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  pinMode(pinSOIL, INPUT);
}

void loop() {
  float temp = dht.readTemperature();
  float doam = analogRead(pinSOIL);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nhiet do: ");
  delay(temp);
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  delay(500);
}
