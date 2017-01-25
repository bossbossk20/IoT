#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 14, 2, 0, 4, 5);
void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
//  lcd.print("test : ");
}
void loop() {
  lcd.setCursor(2, 0);
  lcd.print("koykoy");
}
