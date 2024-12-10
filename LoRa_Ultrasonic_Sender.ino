#include <SPI.h>
#include <LoRa.h>

#define TRIG_PIN 3    
#define ECHO_PIN 4    
#define SS_PIN 10     
#define RST_PIN 9    
#define DIO0_PIN 2    
int counter = 0;  

void setup() {
  
  Serial.begin(115200);
  while (!Serial);  
  Serial.println("LoRa Ultrasonic Sender");
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);
  while (!LoRa.begin(866E6)) {
    Serial.print(".");
    delay(500);
  }

  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.0343 / 2;
  Serial.print("Sending packet #");
  Serial.print(counter);
  Serial.print(" with Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  LoRa.beginPacket();
  LoRa.print(distance); 
  LoRa.endPacket();
  counter++;
  delay(10000);
}
