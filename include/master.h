#ifndef MASTER_H
#define MASTER_H

void setupMaster();
String getESP32_1Data();
String getESP32_2Data();
void controlESP32_3Motors(int leftPower, int rightPower);
void controlESP32_3Pumps(bool pump1On, bool pump2On, int durationMs);

#endif // MASTER_H
