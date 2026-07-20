bool ledOn = false;

void setup()
{
  Serial.begin(9600);
  pinMode(13, INPUT_PULLUP);
  pinMode(11, OUTPUT);
}

void loop()
{
  if (digitalRead(13) == LOW)
  {
    // delay(20);                        // debounce: sleep through press bounce
    ledOn = !ledOn;
    digitalWrite(11, ledOn ? HIGH : LOW);
    Serial.println(ledOn ? 1 : 0);
    while (digitalRead(13) == LOW) // Wait for release
    {
    }
    // delay(20);                        // debounce: sleep through release bounce
  }
}
