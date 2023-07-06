#define pinLDR A0
#define pinBtnD 3

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(pinLDR, INPUT); 
  pinMode(pinBtnD, INPUT); 
}

int val_max = 0;
int val_min = 0;

void loop() {
  lcd.init();
  lcd.backlight();
  
  int val_light = map(analogRead(pinLDR), 0, 1023, 0, 100);

  if(val_light > val_max)
    val_max = val_light;

  if(val_light < val_min)
    val_min = val_light;

  if(digitalRead(pinBtnD) == HIGH){
    lcd.setCursor(0,0);
    lcd.print("Max: ");
    lcd.print(val_max);
  
    lcd.setCursor(0,1);
    lcd.print("Min: ");
    lcd.print(val_min);
  }
}
