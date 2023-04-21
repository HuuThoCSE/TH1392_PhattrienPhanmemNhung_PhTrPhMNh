#define ledRed 2
#define ledYellow 3
#define ledGreen 4

int mang[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1}, //9
};

void hienThiSo(int so) {
  for (int i = 13; i >= 7; i--)
    digitalWrite(i, mang[so][13 - i]);
}

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  for (int i = 1; i <= 13; i++)
    pinMode(i, OUTPUT);
}

void blink(int pin, int time){
  int numSeconds = time / 1000;
  digitalWrite(pin, 1);
  for(int i=numSeconds; i>=0; i--){
    hienThiSo(i);
    delay(1000);
  }
  digitalWrite(pin, 0);
}

void loop() {
  blink(ledRed, 9000);
  blink(ledYellow, 9000);
  blink(ledGreen, 9000);
}