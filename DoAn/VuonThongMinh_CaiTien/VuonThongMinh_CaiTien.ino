// Import libraries
#include <LiquidCrystal.h>  // Declare LCD library / SPI connection (Built-in support)
#include "DHT.h"
#include <RTClib.h>             // RTC library
#include <BlynkSimpleStream.h>  // Blynk
#include <SoftwareSerial.h>

int runTuoi[4] = { 0, 0, 0, 0 };  // 0: Humidity; 1: Rain; 2: Water; 3: pH

// RTC
RTC_DS1307 rtc;  // Declare variable
char daysOfTheWeek[7][12] = { "ChN", "Hai", "Ba", "Tu", "Nam", "Sau", "Bay" };

// Initialize pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);  // Initialize communication pins
SoftwareSerial DebugSerial(17, 16);   // RX, TX

// Blynk
#define BLYNK_TEMPLATE_ID "TMPLSWy0uUgW"
#define BLYNK_DEVICE_NAME "HeThongVuonThongMinh"
#define BLYNK_AUTH_TOKEN "Tts2WJWwPD_a1c0OejzikcYrdszZwrKk"
char auth[] = "Tts2WJWwPRTCD_a1c0OejzikcYrdszZwrKk";

// Declare pins (Constants)
#define pinDHT A0
#define pinSOIL A1
#define pinWater A2
#define pinpHSensor A3

#define pinBtnLAMP 26
#define pinBtnMotor 25

#define pinBtnTime 24
#define pinBtnAuto 23
#define pinBtnReset 22
#define pinBtnScreen1 14
#define pinBtnScreen2 15

#define pinLightVuon2 12
#define pinLDR 13
#define pinRAIN 10
#define pinMotorBom 11
#define pinMotorTuoi 7
#define pinLightVuon1 6

#define DHTTYPE DHT11
DHT dht(pinDHT, DHTTYPE);

bool rainStatus = 0;
int statusLight, valueDoAmDat, giatriDAKK = 0, waterValue = 0, soilValue = 0, Soil = 0, screenShow = 1;
float valuepHWater;
unsigned long int avgValue;
byte nbMode = 2, statusEdit = 0, pageEdit = 0, nbModeLate = 0;
DateTime now;
float humValue, Humi, tempValue, Temp;  // humValue: Air humidity value, tempValue: Temperature humidity value

// Declare global variables
const int numReadings = 7;                                                        // Number of temperature readings
int readings[numReadings], matrixHumi[numReadings], matrixHumiDirt[numReadings];  // Array to store temperature values
int readIndex = 0;                                                                // Index of the array to write new values
float total = 0, totalHumi = 0, totalHumiDirt = 0;                                // Total of temperature values in the array
float average = 0, avgHumi = 0, avgHumiDirt = 0;                                  // Average value of temperature values in the array

unsigned long previousMillis = 0;  // Variable to store the last time temperature was read

const long interval = 60000;  // Time interval between readings (milliseconds)

byte nhietdo[] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte doam[] = {
  B01110,
  B11011,
  B10101,
  B11011,
  B01110,
  B00000,
  B00000,
  B00000
};

void setup() {
  pinMode(pinBtnLAMP, INPUT_PULLUP);
  pinMode(pinBtnMotor, INPUT_PULLUP);

  pinMode(pinBtnTime, INPUT_PULLUP);
  pinMode(pinBtnAuto, INPUT_PULLUP);
  pinMode(pinBtnReset, INPUT_PULLUP);
  pinMode(pinBtnScreen1, INPUT_PULLUP);
  pinMode(pinBtnScreen2, INPUT_PULLUP);

  pinMode(pinLightVuon2, OUTPUT);
  pinMode(pinLDR, INPUT);
  pinMode(pinRAIN, INPUT_PULLUP);
  pinMode(pinMotorBom, OUTPUT);
  pinMode(pinMotorTuoi, OUTPUT);
  pinMode(pinLightVuon1, OUTPUT);

  digitalWrite(pinMotorBom, LOW);
  digitalWrite(pinMotorTuoi, LOW);
  digitalWrite(pinLightVuon1, LOW);
  digitalWrite(pinLightVuon2, LOW);

  lcd.begin(16, 4);  // Initialize LCD screen with 16 characters and 4 lines
  lcd.createChar(1, nhietdo);
  lcd.createChar(2, doam);
  dht.begin();  // Initialize DHT11 sensor
  rtc.begin();  // Initialize RTC

  Serial.begin(9600);              // Initialize Serial communication
  DebugSerial.begin(9600);         // Initialize Debug Serial communication
  Blynk.begin(DebugSerial, auth);  // Initialize Blynk connection

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
    matrixHumi[i] = 0;
    matrixHumiDirt[i] = 0;
  }
}

void loop() {
  Blynk.run();               // Execute Blynk.run() function
  DateTime now = rtc.now();  // Get current time from RTC

  unsigned long currentMillis = millis();  // Store the current time in 'currentMillis'

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // Read and store temperature and humidity values
    tempValue = dht.readTemperature();
    humValue = dht.readHumidity();
    valueDoAmDat = analogRead(pinSOIL);
    valuepHWater = analogRead(pinpHSensor);
    waterValue = analogRead(pinWater);

    if (!isnan(tempValue) && !isnan(humValue)) {
      total = total - readings[readIndex] + tempValue;
      totalHumi = totalHumi - matrixHumi[readIndex] + humValue;
      totalHumiDirt = totalHumiDirt - matrixHumiDirt[readIndex] + valueDoAmDat;

      readings[readIndex] = tempValue;
      matrixHumi[readIndex] = humValue;
      matrixHumiDirt[readIndex] = valueDoAmDat;

      readIndex++;

      if (readIndex >= numReadings) {
        readIndex = 0;
      }

      average = total / numReadings;
      avgHumi = totalHumi / numReadings;
      avgHumiDirt = totalHumiDirt / numReadings;

      Temp = average;
      Humi = avgHumi;
      Soil = avgHumiDirt;
    }
  }
  // Add code to control the system, display data on the LCD screen, and send data to the Blynk app
  // Control the system based on input values
  controlSystem();

  // Display data on the LCD screen
  displayDataOnLCD(now);

  // Send data to the Blynk app
  sendDataToBlynk();

  // Check button states and perform corresponding actions
  checkButtonStates();

  // Check if auto mode is enabled and control the system accordingly
  if (autoMode) {
    controlSystemInAutoMode();
  }
}

void controlSystem() {
  // Control the water pump
  if (digitalRead(pinBtnMotor) == LOW) {
    digitalWrite(pinMotorBom, !digitalRead(pinMotorBom));
    delay(500);
  }

  // Control the irrigation system
  if (digitalRead(pinBtnLAMP) == LOW) {
    digitalWrite(pinMotorTuoi, !digitalRead(pinMotorTuoi));
    delay(500);
  }
}

void displayDataOnLCD(DateTime now) {
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(Temp);
  lcd.write(byte(1));
  lcd.print("C");

  lcd.setCursor(0, 2);
  lcd.print("Humi: ");
  lcd.print(Humi);
  lcd.write(byte(2));
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("Soil: ");
  lcd.print(Soil);
  lcd.print("%");
}

void sendDataToBlynk() {
  Blynk.virtualWrite(V1, Temp);
  Blynk.virtualWrite(V2, Humi);
  Blynk.virtualWrite(V3, Soil);
  Blynk.virtualWrite(V4, valuepHWater);
  Blynk.virtualWrite(V5, waterValue);
}

void checkButtonStates() {
  // Check the button states and perform the corresponding actions
  if (digitalRead(pinBtnTime) == LOW) {
    // Add code to set the time
    delay(500);
  }

  if (digitalRead(pinBtnAuto) == LOW) {
    // Toggle the auto mode
    autoMode = !autoMode;
    delay(500);
  }

  if (digitalRead(pinBtnReset) == LOW) {
    // Add code to reset the system
    delay(500);
  }

  if (digitalRead(pinBtnScreen1) == LOW) {
    // Add code to change to screen 1
    delay(500);
  }

  if (digitalRead(pinBtnScreen2) == LOW) {
    // Add code to change to screen 2
    delay(500);
  }
}

void controlSystemInAutoMode() {
  // Control the system based on the sensor values in auto mode
  if (Soil < soilMoistureThreshold) {
    digitalWrite(pinMotorTuoi, HIGH);
  } else {
    digitalWrite(pinMotorTuoi, LOW);
  }

  if (Temp < temperatureThreshold) {
    digitalWrite(pinLightVuon1, HIGH);
  } else {
    digitalWrite(pinLightVuon1, LOW);
  }
}
// Additional functions for changing screens and resetting the system
void changeScreen(byte screen) {
  switch (screen) {
    case 1:
      // Add code to display screen 1 data on the LCD
      lcd.clear();
      displayDataOnLCD(now);
      break;
    case 2:
      // Add code to display screen 2 data on the LCD
      lcd.clear();
      displayScreen2Data();
      break;
  }
}

void displayScreen2Data() {
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(valuepHWater, 2);

  lcd.setCursor(0, 1);
  lcd.print("Water Lvl: ");
  lcd.print(waterValue);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("Auto Mode: ");
  if (autoMode) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
}

void resetSystem() {
  // Reset the system to the initial state
  autoMode = false;
  digitalWrite(pinMotorBom, LOW);
  digitalWrite(pinMotorTuoi, LOW);
  digitalWrite(pinLightVuon1, LOW);
  changeScreen(1);
}

// Update the loop function with the new functions
void loop() {
  // Check if RTC is working and update the current time
  DateTime now = rtc.now();

  // Read sensor values
  readSensorData();

  // Control the system based on input values
  controlSystem();

  // Display data on the LCD screen
  displayDataOnLCD(now);

  // Send data to the Blynk app
  sendDataToBlynk();

  // Check button states and perform corresponding actions
  checkButtonStates();

  // Check if auto mode is enabled and control the system accordingly
  if (autoMode) {
    controlSystemInAutoMode();
  }

  // Change the screen based on the button state
  if (digitalRead(pinBtnScreen1) == LOW) {
    changeScreen(1);
    delay(500);
  }

  if (digitalRead(pinBtnScreen2) == LOW) {
    changeScreen(2);
    delay(500);
  }

  // Reset the system based on the button state
  if (digitalRead(pinBtnReset) == LOW) {
    resetSystem();
    delay(500);
  }
}