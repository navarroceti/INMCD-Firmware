#ifndef SERVOMANAGER_H
#define SERVOMANAGER_H

#include <Adafruit_PWMServoDriver.h>

class ServoManager {
private:
    Adafruit_PWMServoDriver board;
    int servoPositions[16];
    int transitionSpeed;

    int angleToPulse(int angle);

public:
    ServoManager();
    void initialize();
    void setTransitionSpeed(int speed);
    void moveServoSmooth(int servo, int targetAngle);
    int getServoPosition(int servo);
};

#endif
