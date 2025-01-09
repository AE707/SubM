#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

void initMotor(int in1, int in2, int pwmPin);
void controlMotor(int in1, int in2, int pwmPin, int speed);

#endif // MOTORCONTROL_H
