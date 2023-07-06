# **I. NỘI DUNG**
- Thiết bị thật
- Grove
    - LCD
- Kết nối blynk

# **Sensor**
**Lưu ý:**
- pin NC (Not Connected): Chân không sử dụng.

## **Buzzer**
```c++
// byte buzzer = A5;

void loop(){
  digitalWrite(A5, 1);
}
```

## **LCD**
### **LCD I2C**
#### **Đấu nối**
![image](https://github.com/huuthocs/TH1392_PhattrienPhanmemNhung_PhTrPhMNh/assets/89997693/370b7a61-20c2-4535-b3f5-d55d613740d5)

#### **Thư viện**
[LiquidCrystal I2C](https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c)
### **LCD SPI**
#### **Đấu nối**
![image](https://github.com/huuthocs/TH1392_PhattrienPhanmemNhung_PhTrPhMNh/assets/89997693/cfc2349f-4d33-4b53-8cac-e5d2c012841d)

#### **Thư viện**
[LiquidCrystal (Có sẵn không cần cài)](https://github.com/arduino-libraries/LiquidCrystal)

## **DHT**
- **Lưu ý:** Nối vào chân digital

### DHT11

### DHT22
- Proteus + Library arduino (DHT Sensor): Dùng type DHT11 (10h18pm - 4/7/2023)

## **SOIL**
- Kèm theo
    - 1210-271K - INDUCTOR
    - A700V107M002ATE02 - CAPACITOR
#### **Đấu nối**
![image](https://github.com/huuthocs/TH1392_PhattrienPhanmemNhung_PhTrPhMNh/assets/89997693/36e7625f-c072-4430-98ed-e860628ae65a)

## **L298**
```c++
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 6
#define ENB 7

void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
```

## **RTC**
- Cài thư viện RTC: [RTClib](https://github.com/adafruit/RTClib)
```c++
#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

DateTime now;
void setup () {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  // rtc.adjust(DateTime(2023, 5, 19, 3, 15, 0));
}

void loop () {
  now = rtc.now();
  Serial.print(now.minute())
}
```

## **ULTRASONIC SENSOR**
```c++
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

byte trig = 8;
byte echo = 9;
// byte buzzer = A5;

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 6
#define ENB 7

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  // pinMode(buzzer, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  long thgian;
  int kcach;

  //phát xung đi
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  //Tính thời gian
  thgian = pulseIn(echo, HIGH);

  //tính khoảng cách đơn vị cm
  kcach = int(thgian/2/29.412);

  Serial.println("Khoang cach: "+ String(kcach) +" cm");
  Serial.println();

  lcd.setCursor(0, 0);
  lcd.print("Khoang cach: "+ String(kcach) +" cm");
  lcd.println();
  
  if (kcach > 30 || kcach == 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    delay(1000);
  }

  // // nếu khoàng cách nhỏ hơn 100 thì buzzer sẽ bật.
  //  if(kcach < 100){       
  //     digitalWrite(buzzer,HIGH);
  //   }
  //   else 
  //     digitalWrite(buzzer,LOW);
    
  //   delay(1000);
}

```

# **Truyền tính hiệu giữa 2 thiết bị**
## **SPI**
```c++
ConA:
#include "DHT.h"
#include <SoftwareSerial.h>

SoftwareSerial Serial2(10, 11); // RX, TX

#define DHTPIN 8

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.println(t); // Gửi dữ liệu

  if (Serial.available() > 0) { // Kiểm tra xem có dữ liệu đến hay không
    String data = Serial.readString(); // Đọc dữ liệu

    Serial2.println(data); // In dữ liệu nhận được
  }

  delay(1000);
}

ConB:
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2

#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {
  if (Serial.available() > 0) { // Kiểm tra xem có dữ liệu đến hay không
    String data = Serial.readString(); // Đọc dữ liệu
    Serial.println("Dan nhan duoc");
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println(data); // In dữ liệu nhận được
  }
}

```

# **Grove - Seeeaduino**
**SPI:** MISO, SCK, MOSI and SS are also connected to digital pins 12, 13, and 11 and 10

## **Grive - Kết nối**
- Tải driver: [https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads)
- Cài thư viện trong arduino (property): https://raw.githubusercontent.com/Seeed-Studio/Seeed_Platform/master/package_legacy_seeeduino_boards_index.json
- Vào giao diện quản lý boar tìm “Seeduino AVR”
- Chọn Seeeduino Lotus

## **Grove - ChainableLED**
- Cài thư viện: [ChainableLED](https://github.com/pjpmarques/ChainableLED)
```c++
#include <ChainableLED.h>

#define NUM_LEDS 1

ChainableLED leds(7, 8, NUM_LEDS);

float hue = 0.0;
boolean up = true;
if(temp > 40){
  for (byte i=0; i<NUM_LEDS; i++)
  leds.setColorHSB(i, hue, 1.0, 0.5);
  delay(50);
  if (up)
    hue+= 0.025;
  else
    hue-= 0.025;
  if (hue>=1.0 && up)
    up = false;
  else if (hue<=0.0 && !up)
    up = true;
} else if(temp > 30){
  leds.setColorRGB(0, 0, 0, 255); // Blue
} else if(temp > 20){
  leds.setColorRGB(0, 0, 255, 0); // Green
} else if(temp > 10){
  leds.setColorRGB(0, 255, 0, 0); // Red
}

```

## **Grove - LCD I2C**
- Cài thư viện Library: [Grove - LCD rgb backlight](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight)
```c++
// Khởi tạo đối tượng LiquidCrystal_I2C
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup(){  
  lcd.begin(16, 2);
}

void loop(){  
  lcd.clear();
  lcd.cursor();
}
```
## **Grove - DHT11**
- Kết nối chân data với pinDigital
- Cài thư viện (Library): [Grove temperature and humidity sensor](https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor)
# **Ethernet Shield W5100**
**Địa chỉ IP động**
```c++
#include <SPI.h>
#include <Ethernet.h>

// Nhập địa chỉ MAC của bạn
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
EthernetClient client;

void setup() {
  // Khởi động Serial:
  Serial.begin(9600);

  // Cố gắng để kết nối DHCP
  Serial.println("Cố gắng kết nối DHCP");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Không thể cấu hình Ethernet bằng DHCP");
    // Nếu kết nối DHCP thất bại, hãy cố gắng thiết lập địa chỉ IP tĩnh:
    Ethernet.begin(mac, IPAddress(192,168,1,177));
  }
  // In ra địa chỉ IP sau khi kết nối:
  Serial.print("Địa chỉ IP của máy là: ");
  Serial.println(Ethernet.localIP());
}
```

```c++
void setup(){
    if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
    }

    // print your local IP address:
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
}
```

# **Grove + W5100 và Kết nối Blynk**
```c++
BLYNK_WRITE(V10) // Thay đổi V.. thành V như trên Blynk Website đã cài đặt
{
  int pinValue = param.asInt();
  // Code thao tác tới pinValue
}
```

**Cơ bản**
```c++
#include <SPI.h>
#include <Ethernet.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your Ethernet MAC address:
byte arduino_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup()
{
  // Debug console
  Serial.begin(9600);

  // You can also specify server:
  //Blynk.begin(auth, "blynk-cloud.com", 80);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8080);
  Blynk.begin(auth, arduino_mac);
}

void loop()
{
  Blynk.run();
}
```
**Gửi dữ liệu**
```c++
#define BLYNK_PRINT Serial // Enables Serial Monitor  
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <BlynkSimpleEthernet.h> 

BlynkTimer timer;

// Tạo một hàm gửi dữ liệu
void sendBlynk(){
  // Hàm lấy giá trị từ sensor

  // Hàm gửi lên blynk
  Blynk.virtualWrite(V0, t); // t là biến lưu giá trị nhiệt độ
}

void setup(){  
  // Here your Arduino connects to the Blynk Cloud.  
  Blynk.begin(BLYNK_AUTH_TOKEN);
  
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);  
}
```

```c++
#define pinRed 8
#define pinYellow 9
#define pinGreen 10

void setup() {
  pinMode(pinRed,     OUTPUT);
  pinMode(pinYellow,  OUTPUT);
  pinMode(pinGreen,   OUTPUT);
}

void blink(int pin, int time){
  digitalWrite(pin, 1);
  delay(time);
  digitalWrite(pin, 0);
}

void loop() {
  blink(pinGreen, 30000);
  blink(pinRed, 20000);
  blink(pinYellow, 5000);
}
```

```c++
byte ledPin[] = {2,3,4,5,6,7,8,9};
byte pinCount;
void setup() {
  pinCount = sizeof(ledPin);
  for (int i=0; i<pinCount; i++){
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  for (int i=0; i<pinCount; i++)
    digitalWrite(ledPin[i], 1);
  delay(3000);

  for (int i=0; i<pinCount; i++)
    digitalWrite(ledPin[i], 0);
  delay(3000);
}
```

```c++
byte ledPin[] = {2,3,4,5,6,7,8,9};
byte pinCount;
void setup() {
  pinCount = sizeof(ledPin);
  for (int i=0; i<pinCount; i++){
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  for (int i=0; i<pinCount; i++){
    digitalWrite(ledPin[i], 1);
    delay(100);
  }
    
  for (int i=0; i<pinCount; i++){
    digitalWrite(ledPin[i], 0);
    delay(100);
  }
}
```

```c++
byte ledPin[] = {2,3,4,5,6,7,8,9};
byte pinCount;
void setup() {
  pinCount = sizeof(ledPin);
  for (int i=0; i<pinCount; i++){
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  byte num_random = random(pinCount);
  digitalWrite(ledPin[num_random], 1);
  delay(100);
  digitalWrite(ledPin[num_random], 0);
}
```

```c++
byte ledPin[] = {2,3,4,5,6,7,8,9};
byte pinCount;
void setup() {
  pinCount = sizeof(ledPin);
  for (int i=0; i<pinCount; i++){
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  for(int i=0; i<pinCount; i++){
    if((i+1)%2==0)
      digitalWrite(ledPin[i], 1);
  }
}
```

```c++
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

```c++
#define pinBtn 2
#define pinLed 8

unsigned long buttonPressTime = 0;
bool isButtonPressed = false;
bool ledState = false;

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBtn, INPUT);
}

void loop() {
  int buttonState = digitalRead(pinBtn);

  if (buttonState == LOW && !isButtonPressed) {
    buttonPressTime = millis();
    isButtonPressed = true;
  }
_
  if (isButtonPressed && buttonState == HIGH) {
    unsigned long duration = millis() - buttonPressTime;
    if (duration >= 500) {
      ledState = !ledState;
      digitalWrite(pinLed, ledState);
      delay(5000);
      digitalWrite(pinLed, LOW);
    }
    isButtonPressed = false;
  }
}

```

```c++
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
  for (int i = 1; i <= 13; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  hienThiSo(3);
}

```

```c++
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
  for (int i = 1; i <= 13; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  for(int i=0; i<=9; i++){
    hienThiSo(i);
    delay(500);
  }
}
```

```c++
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
```

```c++
#include <LiquidCrystal.h>

#define motor 9
#define buzzer 10
const int echoPin = 7;
const int triggerPin = 8;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long startTime = 0;

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);

  // Tắt khi khởi động
  digitalWrite(motor, LOW); 
  digitalWrite(buzzer, LOW); 
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0344 / 2;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Khoang cach: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.println(" cm");

  if (distance > 100 && startTime == 0) {
    startTime = millis(); // Lưu thời gian bắt đầu bơm nước
    digitalWrite(motor, HIGH); // Bật máy bơm nước
    digitalWrite(buzzer, HIGH); // Bật còi báo động
    delay(5000); // Còi báo động sẽ kêu trong 5 giây
    digitalWrite(buzzer, LOW); // Tắt còi báo động
  }

  if (distance <= 20) {
    startTime = 0; // Đặt lại thời gian bắt đầu
    digitalWrite(motor, LOW); // Tắt máy bơm nước khi mực nước cách cảm biến 20 cm
  }

  if (startTime != 0 && millis() - startTime >= 15 * 60 * 1000) { // Kiểm tra xem đã quá 15 phút chưa
    startTime = 0; // Đặt lại thời gian bắt đầu
    digitalWrite(motor, LOW); // Tắt máy bơm nước sau 15 phút
    digitalWrite(buzzer, HIGH); // Bật còi báo động
    delay(5000); // Còi báo động sẽ kêu trong 5 giây
    digitalWrite(buzzer, LOW); // Tắt còi báo động
  }

  delay(1000); 
}
```

## Blynk + Proteus
```c++
// Phải dùng thư viện:
#include <BlynkSimpleEthernet.h>
```


# ÔN TẬP BÀI KIỂM TRA
## LED

### Đề: Đấu nối 8 led theo hình tròn lập trình **sáng tắt như rắn săn mồi tuần tự** theo chiều kim đồng hồ ?
```c++
void setup() {
  for(int i=2; i<=9; i++){
    pinMode(i, OUTPUT);
  }  
}

void loop() {
  for(int i=2; i<=9; i++){
    digitalWrite(i, HIGH);
    delay(100);
  }

  for(int i=9; i>=2; i--){
    digitalWrite(i, LOW);
  }
  delay(100);
}
```

### Đề: Đấu nối 8 led theo hình tròn lập trình **sáng tắt tuần tự** theo chiều kim đồng hồ ?
```c++
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
```

### Đề: Đấu nối nút nhấn B, Khi nhấn vào nút nhấn B sẽ đảo chiều sáng tắt các led ( ngược chiều kim đồng hồ) 
```c++
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
```


### Đề: Nếu nhiệt độ >30 thì LED C sáng tắt tuần tự trong 2s không sử dụng delay (1đ) ?
```c++
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

float h, t = 0;

unsigned long time_cur = 0;
unsigned long time_last = 0;
unsigned long time_ledC = 2000;


#define ledC 3

void setup() {
  lcd.init();
  dht.begin();

  pinMode(ledC, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("21022008");
  lcd.setCursor(0, 1);
  lcd.print("Nguyen Huu Tho");
  // delay(15000);
  delay(100);
  lcd.clear();
}

void loop() {
  time_cur = millis();
  if(t > 30){
    if(time_cur - time_last > time_ledC){
      digitalWrite(ledC, !digitalRead(ledC));
      time_last = time_cur;
    } else {
      digitalWrite(ledC, LOW);
    }
  }
}

```

### Đề: Hiển thị nhiệt độ trung bình 6 lần đo
```c++
void loop() {
  float sum = 0;

  for(int i=0; i < 6; i++){ // Exp: Chú ý dòng for
    sum += dht.readTemperature();;
    delay(500);
  }

  float avg = sum / 6;

  lcd.setCursor(0, 0);
  lcd.print("Nhiet do tb 6lan: "); 
  lcd.setCursor(0, 1);
  lcd.print(avg); lcd.print("C");

  delay(1000);
}

```


