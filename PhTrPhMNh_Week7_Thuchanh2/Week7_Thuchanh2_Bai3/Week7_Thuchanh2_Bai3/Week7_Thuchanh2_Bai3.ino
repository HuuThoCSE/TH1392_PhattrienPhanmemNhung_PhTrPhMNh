#define pinLed 8
#define pinLM35 A0

void setup() {
  pinMode(pinLM35, INPUT);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  // Đọc giá trị từ cảm biến LM35
  int rawValue = analogRead(pinLM35);
  float voltage = rawValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;

  if(temperature < 30)
    digitalWrite(pinLed, 1);
  else
    digitalWrite(pinLed, 0);

  delay(1000);
}
