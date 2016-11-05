//void setup() {
//  pinMode(D2, INPUT);
//}
//
//void loop() {
//  Serial.print(digitalRead(D2));
//}

const int buttonPin = D2;    
int buttonState = 0;      

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
}

void loop() {

  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    Serial.println("on");
  } else {
    // turn LED off:
    Serial.println("off");
  }
}
