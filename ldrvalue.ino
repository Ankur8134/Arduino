const int LDRPin = A0;
int LDRValue = 0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  LDRValue = analogRead(LDRPin);
  Serial.println(LDRValue);
  delay(500);
}


