#define pinLedA 2

void setup() {
  pinMode(pinLedA, OUTPUT);
}

void loop() {
  digitalWrite(pinLedA, 1);
  delay(5000);
  digitalWrite(pinLedA, 0);
  delay(5000);
}
