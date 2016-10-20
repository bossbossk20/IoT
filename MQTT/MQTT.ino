#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define LEDPIN  D1
#define BUILTIN_LED D2
const char* ssid = "Apple TV";
const char* password = "APPLE_TV"; 
const char* mqtt_server = "m12.cloudmqtt.com";
int count = 1;
#define DHTPIN D1
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE,15);
int c = 0;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
char msg2[50];
char buff[50];
float oldTemp = 0.0;
void setup() {
  pinMode(D0, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(D2,OUTPUT);
  Serial.begin(115200);
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
      client.publish("/Temperature",msg);
      client.publish("/Humidity",msg2);
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

    if (t > oldTemp) {
         digitalWrite(D0, HIGH);
         delay(2000);
         digitalWrite(D1, LOW);
      } else if (t < oldTemp){
          digitalWrite(D0, LOW);
          delay(2000);
          digitalWrite(D1, HIGH);
      } else if (t == oldTemp) {
          digitalWrite(D0, HIGH);
          digitalWrite(D2, HIGH);
        }
    oldTemp = t;
    itoa(t,temp,10);
    itoa(h,hum,10);
    snprintf (msg,75,temp);
    snprintf (msg2,75,hum);  
    Serial.print(t);
    Serial.print(" C   " );
    Serial.print(h);
    Serial.println(" % ");
    client.publish("/Temperature",msg);
    client.publish("/Humidity",msg2);
  }
  
  if (count % 2 == 0) {
      digitalWrite(D0, HIGH);
      digitalWrite(D2, HIGH);
   }
   else if (count % 2 != 0) {
     digitalWrite(D0, LOW);
      digitalWrite(D2, LOW);
   }
   count++;
}

