#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

#define ldr A0
#define btnD 4

int max, w = 0;

void setup() {
  lcd.init();
  pinMode(ldr, INPUT);
}

void check_max(){
  if(w > max) max = w;
}

void check_show_max(){
  if(digitalRead(btnD) == HIGH){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Light level max: "); 
    lcd.setCursor(0, 1);
    lcd.print(max);
  }
}

void loop() {
  float sum = 0;

  for(int i=0; i<10; i++){
    w = map(digitalRead(ldr), 0, 1023, 0, 100);
    check_max();
    sum += w;
    check_show_max();
    delay(1000);
  }

  float avg = sum / 10;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TB 10 lan do: "); 
  lcd.setCursor(0, 1);
  lcd.print(avg);
  check_show_max();
}
