#include "ESP8266WiFi.h"
const char* MY_SSID = "Apple TV";
const char* MY_PWD =  "APPLE_TV";

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to " + *MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  delay(1000);
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("WIFI connected\n ");
  Serial.println("");
}

void loop() {
  
  
}

