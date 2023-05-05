#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinRAIN 8
#define pinLDR A0

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool status_on, statusRAIN = 0;
int levellight = 0;

void setup() {
  lcd.init();

  pinMode(pinRAIN, INPUT);
  pinMode(pinLDR, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);

  lcd.backlight();
}

void activateWiper() {
  // Mô phỏng hoạt động gạt nước bằng cách quay động cơ DC qua L298 Motor Driver
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  delay(1000); // Quay động cơ DC trong 1 giây

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  status_on = 1;
}

void closeWiper() {
  // Mô phỏng hoạt động gạt nước bằng cách quay động cơ DC qua L298 Motor Driver
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  delay(1000); // Quay động cơ DC trong 1 giây

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  status_on = 0;
}

void ShowLCD(){
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Anh sang: ");
  lcd.print(levellight);
  lcd.setCursor(0, 1);
  lcd.print("Giang phoi: ");
  if(status_on){
    lcd.print("Dang phoi.");
  } else {
    lcd.print("Dong.");
  }
}

void loop() {
  levellight = map(analogRead(pinLDR), 0, 1023, 0, 100);
  statusRAIN = digitalRead(pinRAIN);
  if(statusRAIN==1 && levellight > 35 && status_on==0){
    activateWiper();
  } else if (statusRAIN==0 || levellight < 35 && status_on == 1){
    closeWiper();
  } else {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
  }
  ShowLCD();
}