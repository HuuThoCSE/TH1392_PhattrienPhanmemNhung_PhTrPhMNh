#define pinLedB 11
#define pinBtn 7

unsigned long btnPressTime = 0;
unsigned long blinkEndTime = 0;
bool blinking = false;

void setup() {
  pinMode(pinLedB, OUTPUT);
  pinMode(pinBtn, INPUT_PULLUP);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(pinBtn) == LOW) { 
    if (btnPressTime == 0) { 
      btnPressTime = millis();
    }
    else if (millis() - btnPressTime > 2000) {
      blinking = true;
      blinkEndTime = millis() + 5000; 
      btnPressTime = 0; 
    }
  }
  else {
    btnPressTime = 0;
  }

  // Handle blinking
  if (blinking) {
    if (millis() <= blinkEndTime) { 
      digitalWrite(pinLedB, (millis() / 200) % 2); 
    }
    else { 
      blinking = false;
      digitalWrite(pinLedB, LOW); 
    }
  }
}
