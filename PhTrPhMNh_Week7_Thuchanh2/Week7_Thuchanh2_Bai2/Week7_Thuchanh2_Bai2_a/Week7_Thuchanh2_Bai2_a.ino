#define pinRAIN 8

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

void setup() {
  pinMode(pinRAIN, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

void activateWiper() {
  // Mô phỏng hoạt động gạt nước bằng cách quay động cơ DC qua L298 Motor Driver
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  delay(1000); // Quay động cơ DC trong 1 giây

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  delay(1000); // Quay động cơ DC ngược lại trong 1 giây
}

void loop() {
  if (digitalRead(pinRAIN)){
    activateWiper(); // Kích hoạt gạt nước
  } else {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
  }
}