int LED_PIN = 11;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

// ~50 Hz: at the edge of visible flicker for most people.
// Slow-mo demo: try delay(16) first so the phone catches clear flicker, then halve down to delay(2).
// The LED is pulsing the whole time; it just looks steady when the pulses are too fast to see.
void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(10);  // 10 ms on  } 50 Hz total
  digitalWrite(LED_PIN, LOW);
  delay(10);  // 10 ms off }
}
