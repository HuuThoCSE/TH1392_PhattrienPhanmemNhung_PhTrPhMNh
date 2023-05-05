#include <Wire.h>
#include "rgb_lcd.h"
#include "DHT.h"
#include <ChainableLED.h>

rgb_lcd lcd;

#define NUM_LEDS 1

ChainableLED leds(7, 8, NUM_LEDS);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float hue = 0.0;
boolean up = true;

void setup() {
  lcd.begin(16, 2);
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("21022008");
  lcd.setCursor(0, 1);
  lcd.print("Nguyen Huu Tho");
  // delay(5000);
}

void loop() {
  float humidity = dht.readHumidity();
  // float temp = dht.readTemperature();
  // float temp = 13;
  // float temp = 23;
  // float temp = 23;
  float temp = 53;
  lcd.clear();
  if (isnan(humidity) || isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed to read");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Nhiet do: ");
    lcd.print(temp, 1);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Do am: ");
    lcd.print(humidity, 1);
    lcd.print("%");
  }

  if(temp > 40){
    for (byte i=0; i<NUM_LEDS; i++)
    leds.setColorHSB(i, hue, 1.0, 0.5);
    delay(50);
    if (up)
      hue+= 0.025;
    else
      hue-= 0.025;
    if (hue>=1.0 && up)
      up = false;
    else if (hue<=0.0 && !up)
      up = true;
  } else if(temp > 30){
    leds.setColorRGB(0, 0, 0, 255); // Blue
  } else if(temp > 20){
    leds.setColorRGB(0, 0, 255, 0); // Green
  } else if(temp > 10){
    leds.setColorRGB(0, 255, 0, 0); // Red
  }
}