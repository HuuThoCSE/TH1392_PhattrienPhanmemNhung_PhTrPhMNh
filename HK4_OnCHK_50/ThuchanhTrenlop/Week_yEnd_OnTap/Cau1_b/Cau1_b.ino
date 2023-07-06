#define ledA 2
#define ledB 13
#define btnB 6

unsigned long time_cur = 0;
unsigned long time_last_led = 0;
unsigned long time_last_btn = 0;
unsigned long time_ledA = 5000;
unsigned long time_btnB = 2000;


void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(btnB, OUTPUT_PULLUP);
}

void loop() {
  time_cur = millis();
  
  if()
  if(time_cur - time_last_led <= time_ledA){
    digitalWrite(ledA, !digitalRead(ledA));
    time_cur = time_last;
  } else {
    digitalWrite(ledA, LOW);
  }
}
