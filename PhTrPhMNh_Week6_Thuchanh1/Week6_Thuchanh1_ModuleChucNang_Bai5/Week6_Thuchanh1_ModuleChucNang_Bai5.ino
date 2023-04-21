#include <LiquidCrystal.h>
#include <RTClib.h>

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = { "ChN", "Hai", "Ba", "Tu", "Nam", "Sau", "Bay" };

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define pinLed 8

void setup() {

  pinMode(pinLed, OUTPUT);

  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.begin(16, 2);
}

void loop() {
  DateTime now = rtc.now();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(" ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  lcd.setCursor(0,1);
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);

  if(now.minute() == 15)
    digitalWrite(pinLed, 1);
  else if(now.minute() > 20)
    digitalWrite(pinLed, 0);
  delay(1000);
}
