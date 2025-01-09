#include "MotorControl.h"
#include "WaterPumpControl.h"

// Define motor driver pins for Motor 1 (left motor)
const int motor1In1 = 25;
const int motor1In2 = 26;
const int motor1PWM = 27;

// Define motor driver pins for Motor 2 (right motor)
const int motor2In1 = 32;
const int motor2In2 = 33;
const int motor2PWM = 22;

// Define water pump pins
const int pump1Pin = 21;  // Pump 1 for inflow
const int pump2Pin = 19;  // Pump 2 for outflow

// Water flow rate in liters per second (based on pump specs)
const float pumpFlowRate = 0.05; // Example: 0.05 L/s

// Variables for water level tracking
float waterLevel = 0.0; // Initial water level in liters

void setup() {
  Serial.begin(115200); // UART communication with master

  // Initialize motors
  initMotor(motor1In1, motor1In2, motor1PWM);
  initMotor(motor2In1, motor2In2, motor2PWM);

  // Initialize water pumps
  initWaterPump(pump1Pin);
  initWaterPump(pump2Pin);

  Serial.println("ESP32-3 setup complete!");
}

void controlMotors(int leftPower, int rightPower) {
  // Adjust motor speeds for turning
  controlMotor(motor1In1, motor1In2, motor1PWM, leftPower);  // Left motor
  controlMotor(motor2In1, motor2In2, motor2PWM, rightPower); // Right motor
}

void controlWaterPumps(bool pump1On, bool pump2On, int durationMs) {
  // Control water pumps and calculate water level changes
  if (pump1On) {
    turnOnWaterPump(pump1Pin);
    waterLevel += (pumpFlowRate * (durationMs / 1000.0)); // Inflow
  }

  if (pump2On) {
    turnOnWaterPump(pump2Pin);
    waterLevel -= (pumpFlowRate * (durationMs / 1000.0)); // Outflow
  }

  delay(durationMs); // Pump runtime

  // Turn off pumps
  if (pump1On) turnOffWaterPump(pump1Pin);
  if (pump2On) turnOffWaterPump(pump2Pin);

  // Clamp water level to avoid negative values
  if (waterLevel < 0) waterLevel = 0;

  Serial.print("Updated Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" L");
}

void loop() {
  // Example motor control logic
  Serial.println("Turning right...");
  controlMotors(80, 50); // Left motor faster for right turn
  delay(2000);

  Serial.println("Turning left...");
  controlMotors(50, 80); // Right motor faster for left turn
  delay(2000);

  // Example water pump control
  Serial.println("Adding water...");
  controlWaterPumps(true, false, 3000); // Pump 1 inflow for 3 seconds

  Serial.println("Removing water...");
  controlWaterPumps(false, true, 2000); // Pump 2 outflow for 2 seconds

  delay(5000); // Wait before next loop iteration
}
