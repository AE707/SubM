#include <Wire.h>
#include <HardwareSerial.h>

// Define serial connections for slaves
HardwareSerial Serial1(1); // ESP32-1
HardwareSerial Serial2(2); // ESP32-2
HardwareSerial Serial3(3); // ESP32-3

void setup() {
  Serial.begin(115200);  // Serial Monitor
  Serial1.begin(9600, SERIAL_8N1, 16, 17); // RX, TX for ESP32-1
  Serial2.begin(9600, SERIAL_8N1, 4, 5);  // RX, TX for ESP32-2
  Serial3.begin(9600, SERIAL_8N1, 18, 19); // RX, TX for ESP32-3

  Serial.println("Master ESP32 initialized!");
}

void sendCommand(HardwareSerial &serial, const String &command) {
  serial.println(command);
  Serial.print("Sent command: ");
  Serial.println(command);
}

String receiveData(HardwareSerial &serial) {
  String data = "";
  if (serial.available()) {
    data = serial.readStringUntil('\n');
    Serial.print("Received data: ");
    Serial.println(data);
  }
  return data;
}

void loop() {
  // Example: Request data from ESP32-1
  sendCommand(Serial1, "REQUEST_SENSOR_DATA");
  delay(100); // Wait for response
  String esp32_1_data = receiveData(Serial1);

  // Example: Request data from ESP32-2
  sendCommand(Serial2, "REQUEST_SENSOR_DATA");
  delay(100); // Wait for response
  String esp32_2_data = receiveData(Serial2);

  // Example: Send control commands to ESP32-3
  sendCommand(Serial3, "SET_MOTOR_POWER:80,50"); // Left: 80%, Right: 50%
  sendCommand(Serial3, "SET_WATER_PUMP:1,3000"); // Turn on Pump 1 for 3 seconds

  // Example: Process data (customize this logic)
  Serial.println("Processing data...");
  Serial.print("ESP32-1 Data: ");
  Serial.println(esp32_1_data);
  Serial.print("ESP32-2 Data: ");
  Serial.println(esp32_2_data);

  delay(5000); // Adjust as needed
}
