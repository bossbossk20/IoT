#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float oldTemp = 0.0;
void setup() {
  // put your setup code here, to run once:
  int oldTemp = 0;
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600); 
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature(); float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!"); return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
   float hic = dht.computeHeatIndex(t, h, false);
  Serial.println(hic);
  if(hic<oldTemp) {
    Serial.println(hic);
    Serial.println("DOWN");
    digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
     
  }else if (hic > oldTemp) {
    Serial.println(hic);
    Serial.println("UP");
    digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  }
  else if (hic == oldTemp) {
    Serial.println(hic);
    Serial.println("EQ");
  }
  oldTemp = hic;
  
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  }
 
