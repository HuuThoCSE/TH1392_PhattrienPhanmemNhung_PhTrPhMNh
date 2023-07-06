#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX / TX

#define soil A0

#define BLYNK_PRINT mySerial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleStream.h>


char auth[] = "ZvV50KuZ_Kp8xL1MT-gUtG5Ao3_Ng09k";

BlynkTimer timer;

void send_blynk()
{
  int value = map(analogRead(soil), 0, 1023, 0, 100);
  Blynk.virtualWrite(V4, value);
}

void setup() {
  pinMode(soil, INPUT);
  Serial.begin(9600);

  mySerial.begin(9600);

  Blynk.begin(Serial, auth);

  timer.setInterval(1000L, send_blynk);
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
