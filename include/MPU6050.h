#ifndef MPU6050_H
#define MPU6050_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

bool initMPU6050();
void readMPU6050(float &ax, float &ay, float &az, float &gx, float &gy, float &gz);

#endif // MPU6050_H
