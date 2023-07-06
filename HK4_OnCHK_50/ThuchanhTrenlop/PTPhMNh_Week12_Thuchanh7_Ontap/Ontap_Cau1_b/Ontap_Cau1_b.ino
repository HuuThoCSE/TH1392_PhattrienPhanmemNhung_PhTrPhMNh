#define pinLedB 13
#define pinBtn 8

unsigned long thoiDiemNhan = 0;
unsigned long thoiDiemTha = 0;
unsigned long thoiDiemBatDau = 0;

void setup() {
  pinMode(pinLedB, OUTPUT);
  pinMode(pinBtn, INPUT);

  digitalWrite(pinLedB, LOW);
}

void loop() {
  unsigned long thoiGianHienTai = millis();

  if(digitalRead(pinBtn) == HIGH){
    thoiDiemNhan = thoiGianHienTai;
  } else {
    if(thoiDiemNhan != 0 && thoiDiemTha == 0){
      thoiDiemTha = thoiGianHienTai;
    }
  }

  if(thoiDiemTha - thoiDiemNhan > 2000){
    thoiDiemBatDau = thoiDiemTha;
    thoiDiemNhan = 0;
    thoiDiemTha = 0;
  }

  if(thoiDiemBatDau != 0 && thoiGianHienTai - thoiDiemBatDau < 2000){
    digitalWrite(pinLedB, HIGH);
  } else {
    digitalWrite(pinLedB, LOW);
  }
}