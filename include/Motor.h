#include <Arduino.h>

class Motor
{
private:
    int velocidad = 255;
    // Definir los pines para el control del motor
    const int enAPin = 27;
    const int in1Pin = 12;
    const int in2Pin = 14;

public:
    Motor()
    {
        this->velocidad = 0;
        pinMode(this->in1Pin, OUTPUT);
        pinMode(this->in2Pin, OUTPUT);
        pinMode(this->enAPin, OUTPUT);
    }
    ~Motor() {}
    void SetVelocidad(int velocidad)
    {
        this->velocidad = velocidad;
    }
    
    void ControlMotor(bool forward, int speed)
    {
        digitalWrite(in1Pin, forward ? HIGH : LOW);
        digitalWrite(in2Pin, forward ? LOW : HIGH);
        analogWrite(enAPin, speed);
    }
    
    void Test()
    {
        this->ControlMotor(true, velocidad);
        Serial.println("Motor hacia adelante");
        delay(2000);

        this->ControlMotor(true, 0);
        Serial.println("Motor detenido");
        delay(2000);

        this->ControlMotor(false, velocidad);
        Serial.println("Motor hacia atrás");
        delay(2000);

        this->ControlMotor(true, 0);
        Serial.println("Motor detenido");
        delay(2000);
    }
};