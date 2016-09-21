#include <ESP8266WiFi.h>

const char* ssid = "Cisco06394";
const char* password = "ontani209";

const char* server = "mysterious-inlet-51517.herokuapp.com";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

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

  if (client.connect(server, 80)) { // "184.106.153.149" or api.thingspeak.com
    String postStr;
    postStr += "?field1=";
    postStr += "23";
    postStr += "&field2=";
    postStr += "33";
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: mysterious-inlet-51517.herokuapp.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println(postStr);
  }
  client.stop();

  Serial.println("Waiting…");
  // thingspeak needs minimum 15 sec delay between updates
  delay(20000);
}
