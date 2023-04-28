#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinLM35 A0
#define pinBtn 2

const unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int typeShow = 0;

void setup() {
  pinMode(pinLM35, INPUT);
  pinMode(pinBtn, INPUT_PULLUP);
  lcd.init();
  Serial.begin(9600);
}

long A, B = 0;
int stBTN, tttd;

float CtoF(float value) {
  return (value * 9.0 / 5.0) + 32.0;
}

void loop() {
  // Đọc giá trị từ cảm biến LM35
  int rawValue = analogRead(pinLM35);
  float voltage = rawValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;

  stBTN = digitalRead(pinBtn);
  // Nhan
  if (stBTN == HIGH && tttd == LOW) {
    A = millis();
  }

  // Khong nhan
  if (stBTN == LOW && tttd == HIGH) {
    B = millis();
    if (B - A > 120) {
      typeShow = !typeShow;
    }
  }
  tttd = stBTN;

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

  delay(100);
}
