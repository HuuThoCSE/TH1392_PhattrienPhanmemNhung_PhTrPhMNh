#define pinBtn 2
#define pinLed 8
const unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(pinBtn, INPUT);
  pinMode(pinLed, OUTPUT);
  Serial.begin(9600);
}

// void loop() {
//   static bool lastBtnState = HIGH;
//   bool btnState = digitalRead(pinBtn);

//   if (btnState != lastBtnState) 
//     lastDebounceTime = millis();
  
//   if ((millis() - lastDebounceTime) > debounceDelay) {
//     if (btnState == LOW) {
//       digitalWrite(pinLed, !digitalRead(pinLed));
//     }
//   }

//   lastBtnState = btnState;
// }
  long A, B = 0;
  int stBTN, tttd;
void loop(){
  stBTN = digitalRead(2);
  // Nhan
  if (stBTN == HIGH && tttd == LOW) {
    A = millis();
  }

  // Khong nhan
  if(stBTN == LOW && tttd==HIGH){
    B = millis();
    Serial.print("TG nhan: ");
    Serial.println(B-A);

    if(B-A > 120)
      digitalWrite(pinLed, !digitalRead(pinLed));
  }
  tttd = stBTN;
}
