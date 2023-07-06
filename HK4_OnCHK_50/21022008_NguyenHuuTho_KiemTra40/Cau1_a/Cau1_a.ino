#define pinLedA 2

unsigned long time_ledA = 0;
bool ledState = LOW;

void setup() {
  pinMode(pinLedA, OUTPUT);
  digitalWrite(pinLedA, ledState);
}

void loop() {
  // Led A sáng tắt tuần tự trong 4s không sử dụng delay
  unsigned long cur_time = millis();
  if(cur_time - time_ledA >= 4000){
      ledState = !ledState;
      digitalWrite(pinLedA, ledState);
      time_ledA = cur_time;
   }
}
