#include "DHT.h"
#include <ESP8266WiFi.h>

const char* ssid = "Apple TV";
const char* password = "APPLE_TV";

#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE, 15);
void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.print("test dht");
  Serial.println();
  Serial.println();
  Serial.print("Connecting to");
  Serial.print(ssid);

  WiFi.begin(ssid, password);
  dht.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address");
  Serial.println(WiFi.localIP());
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    Serial.println("Fail");
  } else {
     Serial.print("Humidity: ");
     Serial.print(h);
     Serial.print(" %\t");
     Serial.print("Temperature: ");
     Serial.print(t);
     Serial.print(" *C ");
     Serial.println("");
  }
  delay(1000);
 
}
