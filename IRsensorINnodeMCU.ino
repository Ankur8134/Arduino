int IRSensor = 1; 
int LED = 2; 
void setup(){
  Serial.begin(115200); 
  Serial.println("Serial Working");
  pinMode(IRSensor, INPUT);
  pinMode(LED, OUTPUT); 
}
void loop(){
  int sensorStatus = digitalRead(IRSensor); 
  if (sensorStatus == 1) 
  {
    digitalWrite(LED, LOW); 
    Serial.println("Motion Detected!"); 
  }
  else  {
   
    digitalWrite(LED, HIGH); 
    Serial.println("Motion Ended!"); 
  }
}