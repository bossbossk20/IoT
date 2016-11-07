const int  buttonPin = D2;
const int ledPin = D1;
int buttonPushCounter = 0;
int buttonState = 0;       
int lastButtonState = 0; 

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      Serial.println("pressed");
    } else {
      Serial.println("haven't pressed yet");
    }
    delay(50);
  }
  lastButtonState = buttonState;
}

