#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "d3c5d31991c34f8dba47f37314780a6d";
const char* ssid = "Apple TV";
const char* password = "APPLE_TV";
WiFiClient client;
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Blynk.begin(auth, "yyyy", "zzzzzz");

}

void loop()
{
  Blynk.run();
}
