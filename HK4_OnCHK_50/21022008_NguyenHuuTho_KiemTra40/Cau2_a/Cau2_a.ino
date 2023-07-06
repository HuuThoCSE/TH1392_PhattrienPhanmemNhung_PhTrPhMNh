#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "DHT.h"
#define DHTPIN 8

#define DHTTYPE DHT11

#define pinLedC 11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

bool ledState = LOW;
unsigned long time_ledC = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  // Hiểm thị MSSV, Họ tên và xóa giá trị  đó sau 15s
  lcd.setCursor(0,0);
  lcd.print("21022008");
  lcd.setCursor(0,1);
  lcd.print("Nguyen Huu Tho");
  delay(15000);
  lcd.clear();

  dht.begin();

  pinMode(pinLedC, OUTPUT);
}

void loop() {
  long cur_time = millis();
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Hiểm thị nhiệt độ, độ ẩm
  lcd.setCursor(0,0);
  lcd.print("Nhiet do: ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.print(h);
  lcd.print("%");

  // Nếu nhiệt độ lớn hơn 30 thì Led C sáng tắt tuần tự trong 2s không sử dụng delay
  if(t > 30){
    if(cur_time - time_ledC > 200){
      ledState = !ledState;
      digitalWrite(pinLedC, ledState);
      time_ledC = millis();
    } else {
      digitalWrite(pinLedC, LOW);
    }
  }
}
