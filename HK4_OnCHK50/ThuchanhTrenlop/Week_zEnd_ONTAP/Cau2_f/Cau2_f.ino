#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define ldr A0
#define buzz 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  pinMode(ldr, INPUT);
  pinMode(buzz, OUTPUT);
}

void loop() {
  float sum = 0;

  for(int i=0; i < 10; i++){ // Exp: Chú ý dòng for
    sum += map(analogRead(ldr), 0, 1023, 0, 100);
    delay(500);
  }

  float avg = sum / 10;

  lcd.setCursor(0, 0);
  lcd.print("Nhiet do tb 10lan:"); 
  lcd.setCursor(0, 1);
  lcd.print(avg);

  if(avg > 30){
    digitalWrite(buzz, HIGH);
  }

  delay(100);
}
