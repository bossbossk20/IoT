#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN D5
DHT dht(DHTPIN, DHT22, 15);
void setup() {
  Serial.begin(115200);
  dht.begin();
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println(t);
}
