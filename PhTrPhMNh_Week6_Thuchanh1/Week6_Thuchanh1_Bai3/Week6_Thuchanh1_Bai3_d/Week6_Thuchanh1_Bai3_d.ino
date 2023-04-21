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
  for(int i=0; i<pinCount; i++){
    if((i+1)%2==0)
      digitalWrite(ledPin[i], 1);
  }
}
