byte ledPin[] = {2,3,4,5,6,7,8,9};
byte pinCount;
void setup() {
  pinCount = sizeof(ledPin);
  for (int i=0; i<pinCount; i++){
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  byte num_random = random(pinCount);
  digitalWrite(ledPin[num_random], 1);
  delay(100);
  digitalWrite(ledPin[num_random], 0);
}
