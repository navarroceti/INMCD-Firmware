#include <Arduino.h>
class SensorCorriente
{
private:
    // sensibilidad en Voltios/Amperio para sensor de 5A
    float Sensibilidad = 0.185;
    const int AnalogPin = 35;

public:
    SensorCorriente() {
        pinMode(AnalogPin, INPUT);
    }
    ~SensorCorriente() {}
    void Sensar()
    {
        // # Sensar 1 sola muestra
        // int analogValue = analogRead(AnalogPin);
        // float voltajeSensor = analogValue * (5.0 / 1023.0); // lectura del sensor
        // float I = (voltajeSensor - 2.5) / Sensibilidad;        // Ecuación  para obtener la corriente
        // Serial.print(">corriente: " + String(I, 3) + "\n");
        // Serial.print(">analog-read " + String(analogValue) + "\n");
        // delay(200);

        float I = get_corriente(200); // obtenemos la corriente promedio de 200 muestras
        Serial.print(">corriente: ");
        Serial.println(I, 3);
    }

    float get_corriente(int n_muestras)
    {
        float voltajeSensor;
        float corriente = 0;
        for (int i = 0; i < n_muestras; i++)
        {
            voltajeSensor = analogRead(A0) * (5.0 / 1023.0);              ////lectura del sensor
            corriente = corriente + (voltajeSensor - 2.5) / Sensibilidad; // Ecuación  para obtener la corriente
        }
        corriente = corriente / n_muestras;
        return (corriente);
    }
};