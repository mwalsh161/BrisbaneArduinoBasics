// Pot on A0: period (5 ms = 200 Hz, smooth) to 300 ms (3 Hz, clearly blinking)
// Pot on A1: duty cycle (0% = always off, 100% = always on)
const int LED_PIN = 11;
const int FREQ_POT = A0;
const int DUTY_POT = A1;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int period_ms = map(analogRead(FREQ_POT), 0, 1023, 5, 300);
  int on_ms = map(analogRead(DUTY_POT), 0, 1023, 0, period_ms);

  digitalWrite(LED_PIN, HIGH);
  delay(on_ms);
  digitalWrite(LED_PIN, LOW);
  delay(period_ms - on_ms);
}
