int LED_PIN = 11;
int POT_PIN = A1;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  int pot = analogRead(POT_PIN);
  int blinkDelay = map(pot, 0, 1023, 50, 1000);
  Serial.print(pot);
  Serial.print(",");
  Serial.println(blinkDelay);

  digitalWrite(LED_PIN, HIGH);
  delay(blinkDelay);
  digitalWrite(LED_PIN, LOW);
  delay(blinkDelay);
}
