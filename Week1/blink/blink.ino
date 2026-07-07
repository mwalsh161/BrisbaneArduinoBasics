void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // Turn LED on.
  delay(1000);                      // Wait 1 second (1000 ms).
  digitalWrite(LED_BUILTIN, LOW);   // Turn LED off.
  delay(1000);
}
