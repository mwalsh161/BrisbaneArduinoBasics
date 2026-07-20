// Pot on A0: period — 5 ms (200 Hz, smooth) to 300 ms (3 Hz, visible blink)
// Pot on A1: duty cycle — 0% to 100%, independent of frequency
const int LED_PIN = 11;
const int FREQ_POT = A0;
const int DUTY_POT = A1;

// delayMicroseconds() is unreliable above ~16 ms; split into ms + leftover us.
void delayUs(long us) {
  if (us >= 1000) delay(us / 1000);
  delayMicroseconds(us % 1000);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  long period_us = map(analogRead(FREQ_POT), 0, 1023, 5000L, 300000L);
  int  duty_pct  = map(analogRead(DUTY_POT), 0, 1023, 0, 100);
  long on_us     = period_us * duty_pct / 100;

  digitalWrite(LED_PIN, HIGH);
  delayUs(on_us);
  digitalWrite(LED_PIN, LOW);
  delayUs(period_us - on_us);
}
