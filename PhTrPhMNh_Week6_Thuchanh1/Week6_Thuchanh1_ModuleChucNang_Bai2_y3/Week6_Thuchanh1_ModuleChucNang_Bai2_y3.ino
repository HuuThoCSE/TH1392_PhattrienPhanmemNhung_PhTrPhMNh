#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int ledPin = 8;
unsigned long previousMillis = 0;
const long intervalOn = 200;  
const long intervalOff = 3000;  
bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  if (ledState == HIGH) {
    if (currentMillis - previousMillis >= intervalOn) {
      ledState = LOW;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
  } else {
    if (currentMillis - previousMillis >= intervalOff) {
      ledState = HIGH;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
  }
}