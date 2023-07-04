#include "RTClib.h"
#define pinLedD 6

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);

  pinMode(pinLedD, OUTPUT);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");

  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  
}

void loop() {
  DateTime now = rtc.now();
  if(now.hour() >= 12){
    digitalWrite(pinLedD, 1);
  } else {
    digitalWrite(pinLedD, 0);
  }
}
