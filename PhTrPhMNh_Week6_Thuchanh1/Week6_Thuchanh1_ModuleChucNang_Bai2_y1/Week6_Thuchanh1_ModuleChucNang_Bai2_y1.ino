#include "DHT.h"

#define pinLed 2

#define DHTPIN A1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float ArrTemp[7];

void setup() {
  dht.begin();
  pinMode(pinLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(t);
  if(t < 30)
    digitalWrite(pinLed, 1);
  else
    digitalWrite(pinLed, 0);
  delay(500);
}
