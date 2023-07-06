#define BLYNK_PRINT DebugSerial
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#define BLYNK_TEMPLATE_ID "TMPL6gs3fVfBJ"
#define BLYNK_TEMPLATE_NAME "Wifi"
#define BLYNK_AUTH_TOKEN "IoA14iTuRaUMncDaH6W75kAcVJSai7le"
#include <BlynkSimpleStream.h>
char auth[] = "IoA14iTuRaUMncDaH6W75kAcVJSai7le";
int var;

void setup()
{
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  
  Blynk.begin(Serial, auth);
}
void loop()
{
  Blynk.run();
}
