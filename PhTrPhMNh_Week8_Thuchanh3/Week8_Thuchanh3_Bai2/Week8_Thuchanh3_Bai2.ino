const int ledRedPin=4;
const int ledYellowPin=3;
const int ledBluePin=2;

void setup() {
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
}

void loop() {
  digitalWrite(ledRedPin,     1);
  digitalWrite(ledYellowPin,  0);
  digitalWrite(ledBluePin,    0);
  delay(1000);

  digitalWrite(ledRedPin,     0);
  digitalWrite(ledYellowPin,  1);
  digitalWrite(ledBluePin,    0);
  delay(1000);

  digitalWrite(ledRedPin,     0);
  digitalWrite(ledYellowPin,  0);
  digitalWrite(ledBluePin,    1);
  delay(1000);
}
