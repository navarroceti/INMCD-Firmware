#include <Arduino.h>
// Pines control puente H
#define ENA_PIN 27
#define IN1_PIN 12
#define IN2_PIN 14

enum DIRECCION_MOTOR
{
    FORWARD,
    BACKWARD,
    STOP
};

class Motor
{
private:
    int velocidad = 255;
    DIRECCION_MOTOR direccion = FORWARD;

public:
    Motor()
    {
        this->velocidad = 0;
        pinMode(IN1_PIN, OUTPUT);
        pinMode(IN2_PIN, OUTPUT);
        pinMode(ENA_PIN, OUTPUT);
    }
    ~Motor() {}
    void SetVelocidad(int velocidad)
    {
        this->velocidad = velocidad;
    }

    void SetDireccion(DIRECCION_MOTOR direccion)
    {
        this->direccion = direccion;
    }

    void Actualizar()
    {
        switch (direccion)
        {
        case FORWARD:
            digitalWrite(IN1_PIN, HIGH);
            digitalWrite(IN2_PIN, LOW);
            break;
        case BACKWARD:
            digitalWrite(IN1_PIN, LOW);
            digitalWrite(IN2_PIN, HIGH);
            break;
        case STOP:
            digitalWrite(IN1_PIN, LOW);
            digitalWrite(IN2_PIN, LOW);
            break;
        }
        analogWrite(ENA_PIN, velocidad);
    }
};