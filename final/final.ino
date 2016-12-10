#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
float hh = 0.0;
float te = 0.0;
float td = 0.0;
float temp = 0.0 , hum = 0.0;
String koy = "0";
#define DHTPIN            D7    
#define DHTTYPE           DHT22
LiquidCrystal lcd(12, 14, 2, 0, 4, 5);
DHT_Unified dht(DHTPIN, DHTTYPE);

char auth[] = "05f046a5cf5848a69ffdf003c87c7059";

SimpleTimer timer;

void setup()
{
  Serial.begin(115200);
  pinMode(15, OUTPUT);
  Blynk.begin(auth, "Apple TV", "APPLE_TV");
  
  dht.begin();
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("koy");
  
  // Setup a function to be called every second
  timer.setInterval(5000L, sendUptime);
}

void sendUptime()
{
  Blynk.virtualWrite(V5, millis() / 1000);
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    Blynk.virtualWrite(V1, event.temperature);
    Serial.print("temp : ");
    Serial.print(event.temperature);
    if(event.temperature >= 30 && event.temperature <= 35) { 
      digitalWrite(15, HIGH);
    } else if (event.temperature > 35 ) {
        digitalWrite(15, HIGH);
        delay(1000);
        digitalWrite(15, LOW);
        delay(1000);
        digitalWrite(15, HIGH);
        delay(1000);
        digitalWrite(15, LOW);
        delay(1000);
    } else if (event.temperature < 30 ) {
      digitalWrite(15, LOW);
    }
    lcd.setCursor(0,1);
    lcd.print("T:");
    lcd.print(event.temperature);
    temp = event.temperature;
  }
  Serial.print(event.temperature);
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    Blynk.virtualWrite(V2, event.relative_humidity);
    lcd.setCursor(0,0);
    lcd.print("H:");
    lcd.print(event.relative_humidity);
    hum = event.relative_humidity
      Serial.println("");
      Serial.println(event.relative_humidity + event.relative_humidity);
//    String hh = event.relative_humidity;
  }
    td = (temp - ((100-hum)/5));
    lcd.setCursor(8,0);
    lcd.print("td:");
    lcd.print(td);
//  Serial.print(hh.toFloat());
}
void loop()
{
  Blynk.run();
  timer.run();
}
