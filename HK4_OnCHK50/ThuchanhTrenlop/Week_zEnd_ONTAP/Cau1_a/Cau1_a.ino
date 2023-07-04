// void setup() {
//   for(int i=2; i<=9; i++){
//     pinMode(i, OUTPUT);
//   }  
// }

// void loop() {
//   for(int i=2; i<=9; i++){
//     digitalWrite(i, HIGH);
//     delay(100);
//   }

//   for(int i=9; i>=2; i--){
//     digitalWrite(i, LOW);
//   }
//   delay(100);
// }

const int FIRST_PIN = 2;
const int LAST_PIN = 9;
const int DELAY_TIME = 100;

void setup() {
  for (int i = FIRST_PIN; i <= LAST_PIN; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Sáng LED theo chiều kim đồng hồ
  for (int i = FIRST_PIN; i <= LAST_PIN; i++) {
    digitalWrite(i, HIGH); // Bật LED
    delay(DELAY_TIME); // Chờ
    digitalWrite(i, LOW); // Tắt LED
  }
}
