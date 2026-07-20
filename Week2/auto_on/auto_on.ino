int LED_PIN   = 11;
int LIGHT_PIN = A5;
int THRESHOLD = 400; // adjust using Serial Monitor readings

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int light = analogRead(LIGHT_PIN);
  Serial.println(light);

  if (light < THRESHOLD)
  {
    digitalWrite(LED_PIN, HIGH); // dark: LED on
  }
  else
  {
    digitalWrite(LED_PIN, LOW); // bright: LED off
  }

  delay(100);
}
