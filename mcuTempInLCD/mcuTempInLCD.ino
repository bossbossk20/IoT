#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 13
DHT dht(DHTPIN, DHT22, 15);
LiquidCrystal lcd(12, 14, 2, 0, 4, 5);
void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
 
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println(t);
  lcd.setCursor(2, 1);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.setCursor(2, 0);
  lcd.print("Hu : ");
  lcd.print(h);
}
