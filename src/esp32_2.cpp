#include "WaterFlowSensor.h"
#include "PressureSensor.h"
#include "DopplerSensor.h"

// Define sensor pins
const int flowSensorPin = 14;   // YF-S201
const int pressureSensorPin = 34; // SEN0257 (analog)
const int dopplerSensorPin = 35;  // HB100 (analog or digital)

void setup() {
  Serial.begin(115200); // UART communication with master

  // Initialize sensors
  initWaterFlowSensor(flowSensorPin);
  initPressureSensor(pressureSensorPin);
  initDopplerSensor(dopplerSensorPin);

  Serial.println("All sensors initialized successfully for ESP32-2!");
}

void loop() {
  // Collect data
  float flowRate = readWaterFlowSensor(flowSensorPin);
  float pressure = readPressureSensor(pressureSensorPin);
  float dopplerSpeed = readDopplerSensor(dopplerSensorPin);

  // Transmit data to master via Serial
  Serial.print("Water Flow Rate: ");
  Serial.print(flowRate);
  Serial.println(" L/min");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" kPa");

  Serial.print("Doppler Speed: ");
  Serial.print(dopplerSpeed);
  Serial.println(" m/s");

  delay(500); // Adjust as needed
}
