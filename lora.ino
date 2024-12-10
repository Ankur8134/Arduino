#include <SPI.h>
#include <LoRa.h>

// Pin definitions
#define LDR_PIN A4    // LDR connected to analog pin A4
#define SS_PIN 10     // Slave select pin for LoRa module
#define RST_PIN 9     // Reset pin for LoRa module
#define DIO0_PIN 2    // DIO0 pin for LoRa module

int counter = 0;  // Counter for packet sending

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  while (!Serial) {
    // Wait for the Serial monitor to open
    Serial.println("LoRa Sender");
  }
  Serial.println();

  // Initialize LoRa
  Serial.println("Initializing LoRa...");
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);  // Set LoRa module pins
  
  // Initialize LoRa at 866 MHz frequency
  while (!LoRa.begin(866E6)) {
    Serial.print(".");
    delay(500);
  }
  
  // Set a custom sync word (optional for your network setup)
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // Read LDR value from the analog pin
  int LDR_VALUE = analogRead(LDR_PIN);
  
  // Print the LDR value for debugging
  Serial.print("Sending packet #");
  Serial.print(counter);
  Serial.print(" with LDR value: ");
  Serial.println(LDR_VALUE);

  // Send LDR value over LoRa
  LoRa.beginPacket();
  LoRa.print(LDR_VALUE);
  LoRa.endPacket();

  // Increment packet counter
  counter++;

  // Wait 10 seconds before sending the next packet
  delay(10000);
}