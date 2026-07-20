int LED_PIN = 11;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  for (int b = 0;   b <= 255; b++) fadeTo(b);
  for (int b = 255; b >= 0;   b--) fadeTo(b);
}

// Hold brightness level for 12 PWM cycles (~12 ms) before stepping.
// The MCU does nothing but toggle this pin the entire time.
void fadeTo(int brightness) {
  int onUs  = (1000L * brightness) / 255;  // L = long (32-bit): 1000*255=255000 overflows 16-bit int without it
  int offUs = 1000 - onUs;
  for (int i = 0; i < 12; i++) {
    if (onUs  > 0) { digitalWrite(LED_PIN, HIGH); delayMicroseconds(onUs); }
    if (offUs > 0) { digitalWrite(LED_PIN, LOW);  delayMicroseconds(offUs); }
  }
}
