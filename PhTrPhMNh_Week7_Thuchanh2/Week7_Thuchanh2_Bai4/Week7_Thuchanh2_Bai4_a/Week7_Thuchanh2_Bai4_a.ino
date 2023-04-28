#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinLM35 A0

#define pinBtn1 2
#define pinBtn2 3

LiquidCrystal_I2C lcd(0x27, 16, 2);

int typeShow = 0;

void setup() {
  pinMode(pinLM35, INPUT);
  pinMode(pinBtn1, INPUT_PULLUP);
  pinMode(pinBtn2, INPUT_PULLUP);
  lcd.init();
}

float CtoF(float value) {
  return (value * 9.0 / 5.0) + 32.0;
}

float FtoC(float value) {
  return (value - 32.0) * 5.0 / 9.0;
}

void loop() {
  // Đọc giá trị từ cảm biến LM35
  int rawValue = analogRead(pinLM35);
  float voltage = rawValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;

  // Kiểm tra nút nhấn
  bool btn1Pressed = digitalRead(pinBtn1);
  bool btn2Pressed = digitalRead(pinBtn2);
  
  if(btn1Pressed){
    typeShow == 0;
  } else if(btn2Pressed){
    typeShow == 1;
  }

  // Hiển thị nhiệt độ
  if (typeShow == 0) {
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(temperature);
    lcd.print(" C");
  } else if (typeShow == 1) {
    temperature = CtoF(temperature);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(temperature);
    lcd.print(" F");
  }
  delay(500);
}
