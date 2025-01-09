#include <Arduino.h>
#include <Wire.h>
#include <HardwareSerial.h>

// Include headers for each subsystem
#include "esp32_1.h"
#include "esp32_2.h"
#include "esp32_3.h"
#include "master.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting AUV Master-Slave System...");

  // Initialize communication and subsystems
  setupMaster();
  setupESP32_1();
  setupESP32_2();
  setupESP32_3();

  Serial.println("System initialized successfully!");
}

void loop() {
  // Example: Request data from ESP32-1
  String sensorData1 = getESP32_1Data();
  Serial.println("ESP32-1 Sensor Data: " + sensorData1);

  // Example: Request data from ESP32-2
  String sensorData2 = getESP32_2Data();
  Serial.println("ESP32-2 Sensor Data: " + sensorData2);

  // Example: Control motors and pumps via ESP32-3
  controlESP32_3Motors(80, 50);  // Left motor 80%, right motor 50%
  controlESP32_3Pumps(true, false, 3000); // Turn on Pump 1 for 3 seconds

  // Add custom logic for data processing and behavior control
  processSensorData(sensorData1, sensorData2);

  delay(5000); // Adjust as needed
}
