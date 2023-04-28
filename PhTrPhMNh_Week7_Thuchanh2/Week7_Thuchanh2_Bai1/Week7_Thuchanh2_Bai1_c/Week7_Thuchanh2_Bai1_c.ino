#include <LiquidCrystal.h>

#define motor 9
#define buzzer 10
const int echoPin = 7;
const int triggerPin = 8;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long startTime = 0;

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);

  // Tắt khi khởi động
  digitalWrite(motor, LOW); 
  digitalWrite(buzzer, LOW); 
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0344 / 2;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Khoang cach: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.println(" cm");

  if (distance > 100 && startTime == 0) {
    startTime = millis(); // Lưu thời gian bắt đầu bơm nước
    digitalWrite(motor, HIGH); // Bật máy bơm nước
    digitalWrite(buzzer, HIGH); // Bật còi báo động
    delay(5000); // Còi báo động sẽ kêu trong 5 giây
    digitalWrite(buzzer, LOW); // Tắt còi báo động
  }

  if (distance <= 20) {
    startTime = 0; // Đặt lại thời gian bắt đầu
    digitalWrite(motor, LOW); // Tắt máy bơm nước khi mực nước cách cảm biến 20 cm
  }

  if (startTime != 0 && millis() - startTime >= 15 * 60 * 1000) { // Kiểm tra xem đã quá 15 phút chưa
    startTime = 0; // Đặt lại thời gian bắt đầu
    digitalWrite(motor, LOW); // Tắt máy bơm nước sau 15 phút
    digitalWrite(buzzer, HIGH); // Bật còi báo động
    delay(5000); // Còi báo động sẽ kêu trong 5 giây
    digitalWrite(buzzer, LOW); // Tắt còi báo động
  }

  delay(1000); 
}