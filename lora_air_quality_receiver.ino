#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal.h>

const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#define ss 10
#define rst 9
#define dio0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");
    lcd.begin(16, 2);
  delay(200);
  lcd.clear();
  lcd.print("air_Quality");
  delay(2000);
  lcd.clear();
LoRa.setPins(ss, rst, dio0);
  
  
  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
   
  LoRa.setSyncWord(0xFF);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
   
    Serial.print("Received packet '");

    
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 

  lcd.clear();

  lcd.setCursor(0,0);
 

  lcd.setCursor(0,10);
   lcd.clear();

  lcd.print(LoRaData);
   lcd.display(); 
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
}