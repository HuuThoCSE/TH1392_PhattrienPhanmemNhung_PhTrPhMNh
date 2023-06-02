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

### **LCD SPI**


## **DHT11**
- **Lưu ý:** Nối vào chân digital
## **SOIL**
- 

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