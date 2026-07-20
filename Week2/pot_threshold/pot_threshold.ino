int LED_PIN   = 11;
int POT_PIN   = A1;
int LIGHT_PIN = A5;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int threshold = analogRead(POT_PIN);
  int light     = analogRead(LIGHT_PIN);

  Serial.print(light);
  Serial.print(",");
  Serial.println(threshold);

  if (light < threshold) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(100);
}
