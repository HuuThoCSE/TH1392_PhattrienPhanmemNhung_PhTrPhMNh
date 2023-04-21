#include "DHT.h"

#define pinLed 2

#define DHTPIN A1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float ArrTemp[7];

void setup() {
  dht.begin();
  pinMode(pinLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i=0; i < 7; i++){
    ArrTemp[i+1] = ArrTemp[i]; 
  }

  ArrTemp[0] = dht.readTemperature();
  
  float sum = 0;
  for(int i=0; i < 7; i++){
    sum += ArrTemp[i]; 
  }

  float avg = 0;
  avg = sum / 7;

  if(avg < 32 )
    digitalWrite(pinLed, 1);
  else
    digitalWrite(pinLed, 0);
  Serial.println(avg);
  delay(500);
}

//// Code cai tien
// #include "DHT.h"

// #define pinLed 2
// #define DHTPIN A1
// #define DHTTYPE DHT11
// #define SAMPLES 7

// DHT dht(DHTPIN, DHTTYPE);
// float ArrTemp[SAMPLES];

// void setup() {
//   dht.begin();
//   pinMode(pinLed, OUTPUT);
//   Serial.begin(9600);
// }

// void updateArray(float newArr[], float newVal) {
//   for (int i = SAMPLES - 1; i > 0; i--) {
//     newArr[i] = newArr[i - 1];
//   }
//   newArr[0] = newVal;
// }

// float calculateAverage(float arr[], int size) {
//   float sum = 0;
//   for (int i = 0; i < size; i++) {
//     sum += arr[i];
//   }
//   return sum / size;
// }

// void loop() {
//   float currentTemperature = dht.readTemperature();
//   updateArray(ArrTemp, currentTemperature);

//   float avg = calculateAverage(ArrTemp, SAMPLES);
//   digitalWrite(pinLed, (avg < 32) ? HIGH : LOW);

//   Serial.println(avg);
//   delay(500);
// }

