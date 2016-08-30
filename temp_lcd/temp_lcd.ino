#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  dht.begin();
  // Print a message to the LCD.
//  lcd.setCursor(5, 0);
//  lcd.print("temperature :");
}
void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.println(t);
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("Hu : ");
  lcd.print(h);
}
