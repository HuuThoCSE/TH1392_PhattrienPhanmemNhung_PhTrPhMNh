#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinSOIL A0

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool status_on, statusRAIN = 0;
int humi_soil = 0;

void setup() {
  lcd.init();

  pinMode(pinSOIL, INPUT);

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

void OnMotor() {
  // Mô phỏng hoạt động gạt nước bằng cách quay động cơ DC qua L298 Motor Driver
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  status_on = 1;
}

void OffMotor() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  status_on = 0;
}

void ShowLCD(){
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Do am: ");
  lcd.print(humi_soil);
  lcd.setCursor(0, 1);
  lcd.print("Motor: ");
  if(status_on){
    lcd.print("On.");
  } else {
    lcd.print("Off.");
  }
}

void loop() {
  humi_soil = map(analogRead(pinSOIL), 0, 1023, 0, 100);
  if(humi_soil < 70){N
    OnMotor();
  } else {
    if(status_on != 0){
      OffMotor();
    }
  }
  ShowLCD();
}