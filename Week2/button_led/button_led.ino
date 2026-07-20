void setup() {
  pinMode(13, INPUT_PULLUP);
  pinMode(11, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(13);

  if (buttonState == LOW) {   // LOW = pressed (INPUT_PULLUP logic is inverted).
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(11, LOW);
  }
}
