#define pinBtn 2
#define pinLed 8

unsigned long buttonPressTime = 0;
bool isButtonPressed = false;
bool ledState = false;

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBtn, INPUT);
}

void loop() {
  int buttonState = digitalRead(pinBtn);

  if (buttonState == LOW && !isButtonPressed) {
    buttonPressTime = millis();
    isButtonPressed = true;
  }
_
  if (isButtonPressed && buttonState == HIGH) {
    unsigned long duration = millis() - buttonPressTime;
    if (duration >= 500) {
      ledState = !ledState;
      digitalWrite(pinLed, ledState);
      delay(5000);
      digitalWrite(pinLed, LOW);
    }
    isButtonPressed = false;
  }
}

