#include <SPI.h>
#include <LoRa.h>

#define AIR_QUALITY_PIN A0  
#define SS_PIN 10          
#define RST_PIN 9          
#define DIO0_PIN 2         
int counter = 0;  

void setup() {
 
  Serial.begin(115200);
  while (!Serial) {
    Serial.println("LoRa Air Quality Sender");
  }
  Serial.println();

 
  Serial.println("Initializing LoRa...");
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);  
  while (!LoRa.begin(866E6)) {  
    Serial.print(".");
    delay(500);
  }
  
  
  LoRa.setSyncWord(0xF1);  
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  
  int airQualityValue = analogRead(AIR_QUALITY_PIN);

  
  Serial.print("Sending packet #");
  Serial.print(counter);
  Serial.print(" with Air Quality value: ");
  Serial.println(airQualityValue);

 
  LoRa.beginPacket();
  LoRa.print(airQualityValue);  
  LoRa.endPacket();

  
  counter++;
  delay(10000);
}
