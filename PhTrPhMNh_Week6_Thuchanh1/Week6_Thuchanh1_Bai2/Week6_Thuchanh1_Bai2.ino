#define pinRed 8
#define pinYellow 9
#define pinGreen 10

void setup() {
  pinMode(pinRed,     OUTPUT);
  pinMode(pinYellow,  OUTPUT);
  pinMode(pinGreen,   OUTPUT);
}

void blink(int pin, int time){
  digitalWrite(pin, 1);
  delay(time);
  digitalWrite(pin, 0);
}

void loop() {
  blink(pinGreen, 30000);
  blink(pinRed, 20000);
  blink(pinYellow, 5000);
}
