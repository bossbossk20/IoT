#include <DHT.h>
#include <ESP8266WiFi.h>

// replace with your channel’s thingspeak API key,
String apiKey = "WMEREWQJ80Q4H83Z";
const char* ssid = "Apple TV";
const char* password = "APPLE_TV";

const char* server = "api.thingspeak.com";
#define DHTPIN D5 // what pin we’re connected to

DHT dht(DHTPIN, DHT22, 15);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();

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

}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println(t);

  if (client.connect(server, 80)) { // "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celcius Humidity: ");
    Serial.print(h);
    Serial.println("% send to Thingspeak");
  }
  client.stop();

  Serial.println("Waiting…");
  // thingspeak needs minimum 15 sec delay between updates
  delay(20000);
}
