int LED_PIN   = 11;
int LIGHT_PIN = A5;
int LO        = 200;  // your dark reading from light_sensor_read
int HI        = 800;  // your bright reading from light_sensor_read

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int light      = analogRead(LIGHT_PIN);
  Serial.println(light);
  int brightness = map(light, HI, LO, 0, 255);
  brightness     = constrain(brightness, 0, 255);

  analogWrite(LED_PIN, brightness);
  delay(50);
}
