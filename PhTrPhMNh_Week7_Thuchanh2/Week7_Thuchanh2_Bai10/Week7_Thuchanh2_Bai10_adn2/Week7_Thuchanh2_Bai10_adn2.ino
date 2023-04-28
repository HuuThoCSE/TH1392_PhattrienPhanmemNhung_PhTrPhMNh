#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);  // Tốc độ baudrate của HC-05 và HC-06
}

void loop() {
  // Đọc dữ liệu từ Serial Monitor và gửi qua Bluetooth
  if (Serial.available()) {
    char data = Serial.read();
    BTSerial.write(data);
  }

  // Đọc dữ liệu từ Bluetooth và hiển thị lên Serial Monitor
  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.write(data);
  }
}