#include <ChainableLED.h>

#define NUM_LEDS 2
#define PIN_CLK 7
#define PIN_DATA 8 

ChainableLED leds(PIN_CLK, PIN_DATA, NUM_LEDS);

void setup()
{
  //nothing
}

float hue = 0.0;
boolean up = true;

void loop()
{
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
}

