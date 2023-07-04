const int FIRST_PIN = 2;
const int LAST_PIN = 9;
const int DELAY_TIME = 300;

#define btnB 10

bool status = 0;

void setup() {
  for (int i = FIRST_PIN; i <= LAST_PIN; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(btnB, INPUT_PULLUP);
}

void loop() {
  if(status==0){
    // Sáng LED theo chiều kim đồng hồ
    for (int i = FIRST_PIN; i <= LAST_PIN; i++) {
      digitalWrite(i, HIGH); // Bật LED
      if(digitalRead(btnB) == LOW){
        status = !status;
      }
      delay(DELAY_TIME); // Chờ
      digitalWrite(i, LOW); // Tắt LED
    }
  } else {
    // Sáng LED theo chiều kim đồng hồ
    for (int i = LAST_PIN; i >= FIRST_PIN; i--) {
      digitalWrite(i, HIGH); // Bật LED
      if(digitalRead(btnB) == LOW){
        status = !status;
      }
      delay(DELAY_TIME); // Chờ
      digitalWrite(i, LOW); // Tắt LED
    }
  }
  
}