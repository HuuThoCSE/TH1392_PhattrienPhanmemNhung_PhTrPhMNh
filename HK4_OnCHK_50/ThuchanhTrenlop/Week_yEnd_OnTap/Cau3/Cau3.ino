#include "RTClib.h"

#define ledE 2

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void setup() {
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  pinMode(ledE, OUTPUT);
  
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop() {
  DateTime now = rtc.now();
  
  if(now.day() == 5 &&  (now.hour() > 13 && now.minute() > 30) || (now.hour() > 14 && now.minute() > 0)){
    digitalWrite(ledE, HIGH);
  } else {
    digitalWrite(ledE, LOW);
  }
}
