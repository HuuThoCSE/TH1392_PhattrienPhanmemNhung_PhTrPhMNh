#include <LiquidCrystal.h>

#define pinSOIL A0
#define DHTPIN A1


#include <DHT.h>
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  pinMode(pinSOIL, INPUT);
  Serial.begin(9800);
}

void loop() {
  float temp = dht.readTemperature();
  float doam = map(analogRead(pinSOIL), 0, 1023, 0, 100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nhiet do: ");
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.print(doam);

  Serial.print("Nhiet do: ");
  Serial.println(temp);
  Serial.print("Do am: ");
  Serial.println(doam);
  Serial.println();
  delay(500);
}
