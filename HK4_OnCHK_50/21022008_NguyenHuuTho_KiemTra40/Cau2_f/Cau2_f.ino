#define pinLDR A0

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(pinLDR, INPUT); 
}

int arr_light[10];

void loop() {
  lcd.init();
  lcd.backlight();
  
  for(int i=9; i >= 0; i--){
    arr_light[i] = arr_light[i-1];
  }

  int val_light = map(analogRead(pinLDR), 0, 1023, 0, 100);
  arr_light[0] = val_light;

  float sum = 0;
  float avg = 0;
  for(int i=0; i<10; i++){
    sum += arr_light[i];
  }

  avg = sum / 10;

  lcd.setCursor(0,0);
  lcd.print("Anh sang t/b: ");
  lcd.setCursor(0,1);
  lcd.print(avg);
}
