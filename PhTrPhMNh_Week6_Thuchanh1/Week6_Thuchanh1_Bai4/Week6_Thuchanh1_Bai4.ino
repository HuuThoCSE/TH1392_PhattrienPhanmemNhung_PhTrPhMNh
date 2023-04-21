#define pinBtn 2
#define pinLed 8
const unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(pinBtn, INPUT);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  static bool lastBtnState = HIGH;
  bool btnState = digitalRead(pinBtn);

  if (btnState != lastBtnState) 
    lastDebounceTime = millis();
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (btnState == LOW) {
      digitalWrite(pinLed, !digitalRead(pinLed));
    }
  }

  lastBtnState = btnState;
}
