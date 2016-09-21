#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "d3c5d31991c34f8dba47f37314780a6d";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "yyyy", "zzzzzz");

}

void loop()
{
  Blynk.run();
}
