#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9c7715fefb1b49b6aee3bf5d10e11608";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, "Apple TV", "APPLE_TV");

}

void loop()
{
  Blynk.run();
}
