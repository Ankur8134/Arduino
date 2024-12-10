#include<SPI.h>
#include<LoRa.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

#define ss 10
#define rst 9
#define dio0 2

int counter=0;

void setup(){
 Serial.begin(9600);
    Wire.begin();
    
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed");
    } else {
        Serial.println("MPU6050 connection successful");
    }
LoRa.setPins(ss,rst,dio0);
while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}


void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
int16_t ax, ay, az;
    int16_t gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    Serial.print("Accelerometer: ");
    Serial.print("X: "); Serial.print(ax);
    Serial.print(" Y: "); Serial.print(ay);
    Serial.print(" Z: "); Serial.println(az);
  
    Serial.print("Gyroscope: ");
    Serial.print("X: "); Serial.print(gx);
    Serial.print(" Y: "); Serial.print(gy);
    Serial.print(" Z: "); Serial.println(gz);
  
    // Format the message correctly
    String message = String(ax) + "," + String(ay) + "," + String(az) + "," +
                     String(gx) + "," + String(gy) + "," + String(gz);
    
  
  LoRa.beginPacket();
  LoRa.print(message);
   
  LoRa.endPacket();

  counter++;

  delay(1000);
}