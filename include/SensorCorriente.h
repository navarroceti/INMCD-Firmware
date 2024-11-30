#include <Arduino.h>
class SensorCorriente
{
private:
    // sensibilidad en Voltios/Amperio para sensor de 5A
    float Sensibilidad = 0.185;
    const int AnalogPin = 39;

public:
    SensorCorriente() {
        pinMode(AnalogPin, INPUT);
    }
    ~SensorCorriente() {}
    void Sensar()
    {
        float voltajeSensor = analogRead(AnalogPin) * (5.0 / 1023.0); // lectura del sensor
        float I = (voltajeSensor - 2.5) / Sensibilidad;        // Ecuación  para obtener la corriente
        Serial.print("Corriente: ");
        Serial.println(I, 3);
        delay(200);
    }
};