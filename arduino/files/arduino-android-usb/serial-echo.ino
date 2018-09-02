void setup() {
  Serial.begin(57600);
}

void loop() {
  while (Serial.available() > 0)
    Serial.print((char)Serial.read());
}
