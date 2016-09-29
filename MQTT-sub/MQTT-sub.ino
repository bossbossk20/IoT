#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 14, 2, 0, 4, 5);
const char* ssid = "Cisco06394";
const char* password = "ontani209";

#define mqtt_server "m12.cloudmqtt.com"
#define mqtt_port 14459
#define mqtt_user "hwztqpui"
#define mqtt_password "FLj-CZ54RMFN"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  Serial.begin(115200);
  lcd.begin(16, 2);
//  lcd.setCursor(2, 0);
//  lcd.print("koy");
  delay(10);

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

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("iotsub", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("/Temperature");
      client.subscribe("/Humidity");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      return;
    }
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  String to = "";
  int i = 0;
  while (i < length) msg += (char)payload[i++];
  Serial.println(msg);
  to = topic;
  Serial.print(to);
  if (to == "/Temperature") {
    lcd.setCursor(2,1);
    lcd.print("Temp : ");
    lcd.print(msg);
  } else if (to == "/Humidity") {
    lcd.setCursor(2,0);
    lcd.print("Humi : ");
    lcd.print(msg);
  }
}
