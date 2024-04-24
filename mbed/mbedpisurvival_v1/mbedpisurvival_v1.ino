void setup() {
  Serial.begin(9600);
}

void loop() {
  // red
  Serial.println("PIXEL,3,4,255-0-0");
  Serial.println("PIXEL,0,0,255-0-0");
  delay(100);

  // white
  Serial.println("PIXEL,3,4,255-255-255");
  delay(100);

  // black
  Serial.println("PIXEL,3,4,0-0-0");
  Serial.println("PIXEL,0,0,0-0-0");
  delay(100);
}
