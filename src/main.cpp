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
Encoder encoder;
WifiManager wifi;
API api;

void setup()
{
  Serial.begin(115200);
  motor.SetVelocidad(100);
  wifi.ConectarWifi();
}

void loop()
{
  api.sendPostRequest(10,2);
  motor.Test();
}
