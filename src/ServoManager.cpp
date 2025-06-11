#include "ServoManager.h"
#include <Arduino.h>

#define SERVOMIN 125
#define SERVOMAX 575

ServoManager::ServoManager() : board(Adafruit_PWMServoDriver()), transitionSpeed(10) {
    for (int i = 0; i < 16; i++) {
        servoPositions[i] = 90; // Posición inicial
    }
}

int ServoManager::angleToPulse(int angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void ServoManager::initialize() {
    if (board.begin()) {
        board.setPWMFreq(50);
        for (int i = 0; i < 16; i++) {
            board.setPWM(i, 0, angleToPulse(90));
        }
    }
}

void ServoManager::setTransitionSpeed(int speed) {
    transitionSpeed = constrain(speed, 1, 100);
}

void ServoManager::moveServoSmooth(int servo, int targetAngle) {
    targetAngle = constrain(targetAngle, 0, 180);
    int currentAngle = servoPositions[servo];

    if (currentAngle < targetAngle) {
        for (int angle = currentAngle; angle <= targetAngle; angle++) {
            board.setPWM(servo, 0, angleToPulse(angle)); // Asegurarse de usar el índice correcto
            delay(transitionSpeed);
        }
    } else {
        for (int angle = currentAngle; angle >= targetAngle; angle--) {
            board.setPWM(servo, 0, angleToPulse(angle)); // Asegurarse de usar el índice correcto
            delay(transitionSpeed);
        }
    }

    servoPositions[servo] = targetAngle; // Actualizar la posición del servo correcto
}

int ServoManager::getServoPosition(int servo) {
    return servoPositions[servo];
}
