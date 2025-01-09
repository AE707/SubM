#include <Wire.h>
#include "MPU6050.h"
#include "BMM150.h"
#include "AJ_SR04M.h"

// Ultrasonic Sensor Pins
const int trigPin = 4;
const int echoPin = 5;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize Sensors
  if (!initMPU6050()) {
    Serial.println("MPU6050 initialization failed!");
    while (1);
  }

  if (!initBMM150()) {
    Serial.println("BMM150 initialization failed!");
    while (1);
  }

  initUltrasonic(trigPin, echoPin);

  Serial.println("All sensors initialized successfully!");
}

void loop() {
  // Collect data and send to master ESP32
  float ax, ay, az, gx, gy, gz;
  float magX, magY, magZ;
  float distance;

  readMPU6050(ax, ay, az, gx, gy, gz);
  readBMM150(magX, magY, magZ);
  distance = readUltrasonic(trigPin, echoPin);

  // Transmit data to master via Serial, I2C, or ESP-NOW
  Serial.print("MPU6050: ");
  Serial.print("AccX: "); Serial.print(ax);
  Serial.print(" AccY: "); Serial.print(ay);
  Serial.print(" AccZ: "); Serial.print(az);
  Serial.print(" GyroX: "); Serial.print(gx);
  Serial.print(" GyroY: "); Serial.print(gy);
  Serial.print(" GyroZ: "); Serial.println(gz);

  Serial.print("BMM150: ");
  Serial.print("MagX: "); Serial.print(magX);
  Serial.print(" MagY: "); Serial.print(magY);
  Serial.print(" MagZ: "); Serial.println(magZ);

  Serial.print("Ultrasonic Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}
