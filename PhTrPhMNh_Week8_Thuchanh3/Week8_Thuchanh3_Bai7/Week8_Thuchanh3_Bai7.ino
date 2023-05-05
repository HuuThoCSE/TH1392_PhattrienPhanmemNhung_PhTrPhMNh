#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
    lcd.begin(16, 2);
    lcd.print("Nguyen Huu Tho");
}

void loop() {
    lcd.noDisplay();
    delay(500);
    lcd.display();
    delay(500);
}