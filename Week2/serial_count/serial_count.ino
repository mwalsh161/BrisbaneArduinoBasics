int count = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print(count);
  Serial.print(",");
  Serial.println(49 - count);
  count = (count + 1) % 50;
  delay(50);
}
