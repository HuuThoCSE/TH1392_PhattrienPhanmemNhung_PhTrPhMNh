#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int echoPin = 7;
const int triggerPin = 8;

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);

  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0344 / 2;

  if(distance < 200){
    // Lui
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delay(500);
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Khoang cach: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.println(" cm");

  delay(500); 
}