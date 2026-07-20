int LED_PIN    = 11;
int LIGHT_PIN  = A5;
int BUTTON_PIN = 13;
int LO         = 200;  // your dark reading from light_sensor_read
int HI         = 800;  // your bright reading from light_sensor_read

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  int currentButton = digitalRead(BUTTON_PIN);
  int light         = analogRead(LIGHT_PIN);

  if (currentButton == LOW) {
    analogWrite(LED_PIN, 255);
  } else {
    int brightness = map(light, HI, LO, 0, 255);
    brightness     = constrain(brightness, 0, 255);
    analogWrite(LED_PIN, brightness);
  }

  delay(50);
}
