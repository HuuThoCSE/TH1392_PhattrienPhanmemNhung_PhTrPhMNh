#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define pinLedE 2

void setup () {
  pinMode(pinLedE, OUTPUT);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
//  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () {
    DateTime now = rtc.now();


    if(now.hour() >= 13 && now.minute() >= 30 && now.day() == 9){
      digitalWrite(pinLedE, 1);
    } else {
      digitalWrite(pinLedE, 0);
    }
}
