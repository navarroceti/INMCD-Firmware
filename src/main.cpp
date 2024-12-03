#include <Motor.h>
#include <Communication.h>
#include <Arduino.h>
#include <Led.h>
#include <Encoder.h>
#include <SensorCorriente.h>
#include <WifiManager.h>
#include <API.h>

Motor motor;
Communication com;
SensorCorriente sensor;
WifiManager wifi;
API api;
int y = 0;
static int t = 0;

unsigned long previousMillis = 0; // Almacena el tiempo anterior
const long interval = 3000;         // Intervalo de tiempo en milisegundos

void setup()
{
  Serial.begin(115200);
  motor.SetVelocidad(0);
  // wifi.ConectarWifi();
  encoder_setup();
  delay(2000);
}

int estado = 0;
int estado_anterior = 0;
void test_motor()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    
    // transicionar entre estados
    if(estado == 0)
    {
      estado = 1;
    }
    else if (estado == 1)
    {
      estado = 2;
    }
    else if (estado == 2)
    {
      estado = 0;
    }
  }

  if (estado != estado_anterior)
  {
    estado_anterior = estado;
  }else{
    return;
  }

  switch (estado)
  {
  case 0:
    Serial.println("Motor hacia adelante");
    motor.SetDireccion(FORWARD);
    motor.SetVelocidad(100);
    motor.Actualizar();
    break;
  case 1:
    Serial.println("Motor hacia atrás");
    motor.SetDireccion(BACKWARD);
    motor.SetVelocidad(100);
    motor.Actualizar();
    break;
  case 2:
    Serial.println("Motor detenido");
    motor.SetDireccion(STOP);
    motor.SetVelocidad(0);
    motor.Actualizar();
    break;
  default:
    break;
  }
}

void loop()
{
  test_motor();
  encoder_loop();
  sensor.Sensar();
  delay(100);
}
