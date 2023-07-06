// Blynk ver 0.6.0
#define BLYNK_TEMPLATE_ID "TMPL6BOtPA5km"
#define BLYNK_TEMPLATE_NAME "Wifi"
#define BLYNK_AUTH_TOKEN "ZvV50KuZ_Kp8xL1MT-gUtG5Ao3_Ng09k"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

#define BLYNK_PRINT mySerial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleStream.h>

char auth[] = "ZvV50KuZ_Kp8xL1MT-gUtG5Ao3_Ng09k";

BlynkTimer timer;

#define rainSersor 2

#define led 3

#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void send_blynk()
{
  Blynk.virtualWrite(V0, digitalRead(rainSersor));
  Blynk.virtualWrite(V2, dht.readTemperature());
  Blynk.virtualWrite(V3, dht.readHumidity());
}

void setup() {
  pinMode(rainSersor, INPUT);
  pinMode(led, OUTPUT);

  // Debug console
  Serial.begin(9600);
  mySerial.begin(9600);

  Blynk.begin(Serial, auth);

  timer.setInterval(1000L, send_blynk);
  dht.begin();
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  digitalWrite(led, pinValue);
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
