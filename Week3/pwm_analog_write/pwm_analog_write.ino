int LED_PIN = 11;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

// Same fade as pwm_soft_fade — but the hardware timer handles the pulsing.
// The MCU just sets the duty cycle and moves on.
void loop() {
  for (int b = 0;   b <= 255; b++) { analogWrite(LED_PIN, b); delay(12); }
  for (int b = 255; b >= 0;   b--) { analogWrite(LED_PIN, b); delay(12); }
}
