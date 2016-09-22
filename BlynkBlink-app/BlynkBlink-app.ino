//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
float te = 0.0;
#define DHTPIN            13    
#define DHTTYPE           DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);

char auth[] = "9c7715fefb1b49b6aee3bf5d10e11608";

SimpleTimer timer;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, "Cisco06394", "ontani209");

  dht.begin();
  
  // Setup a function to be called every second
  timer.setInterval(5000L, sendUptime);
}

void sendUptime()
{
  Blynk.virtualWrite(V5, millis() / 1000);
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    Blynk.virtualWrite(V1, event.temperature);
  }
  Serial.print(event.temperature);
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    Blynk.virtualWrite(V2, event.relative_humidity);
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}
