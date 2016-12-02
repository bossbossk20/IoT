#include "ESP8266WiFi.h"
const int  buttonPin = D2;
const int ledPin = D1;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;
const int redPin = D5;
const int greenPin = D6;
const int bluePin = D7;
const char WEBSITE[] = "api-iot.herokuapp.com";
const char* MY_SSID = "Cisco06394";
const char* MY_PWD =  "ontani209";

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(115200);
  Serial.print("Connecting to " + *MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("WIFI connected\n ");
  Serial.println("");
}

void RGBcolor(int red, int green, int blue) {
  digitalWrite(redPin, !red);
  digitalWrite(bluePin, !green);
  digitalWrite(greenPin, !blue);
}

void loop() {
  WiFiClient client;
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      Serial.println("pressed");
      RGBcolor(1, 0, 0);
      delay(1000);
      RGBcolor(0, 1, 0);
      delay(1000);
      RGBcolor(0, 0, 1);
      delay(1000);
      if (client.connect(WEBSITE, 80)) {
        client.print("GET /api?location=1");
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(WEBSITE);
        client.println("User-Agent: ESP8266/1.0");
        client.println("Connection: close");
        client.println();
      }

    } else {
      Serial.println("haven't pressed yet");
    }
    delay(50);
  }
  lastButtonState = buttonState;
}

