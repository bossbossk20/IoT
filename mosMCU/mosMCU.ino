const int buttonPin = D2;    
int buttonState = 0;      

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
}

void loop() {

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // turn LED on:
    Serial.println("on");
  } else {
    // turn LED off:
    Serial.println("off");
  }
}
