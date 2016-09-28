#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define LEDPIN  D1
#define BUILTIN_LED D2
const char* ssid = "Cisco06394";
const char* password = "ontani209"; 
const char* mqtt_server = "m12.cloudmqtt.com";

#define DHTPIN D3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE,15);

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
char msg2[50];
char buff[50];

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(LEDPIN,OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server,14459);  //16406 , 17402 ,27402,37402
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } 
  else if((char)payload[0] == '2'){
    digitalWrite(5,LOW);
  }
  else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if(client.connect("iot","hwztqpui","FLj-CZ54RMFN")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("iot", "Start");
      // ... and resubscribe
      //client.subscribe("Node2");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    char temp[50];
    char hum[50];
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    itoa(t,temp,10);
    itoa(h,hum,10);
    snprintf (msg,75,temp);
    snprintf (msg2,75,hum);  
    Serial.print(t);
    Serial.print(" C   " );
    Serial.print(h);
    Serial.println(" % ");
    client.publish("Temperature", temp);
    client.publish("Humidity",hum);
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(LEDPIN,HIGH);
  }
}

