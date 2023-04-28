#include <LiquidCrystal.h>

#define motor 9
const int echoPin = 7;
const int triggerPin = 8;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(motor, OUTPUT);
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

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Khoang cach: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.println(" cm");

  if(distance > 100)
    digitalWrite(motor, 1);
  else if(distance < 20)
    digitalWrite(motor, 0);

  delay(1000); 
}