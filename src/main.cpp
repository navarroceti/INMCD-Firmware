#include <Motor.h>
#include <Communication.h>
#include <Arduino.h>
#include <Led.h>
#include <WiFi.h>
#include <SensorCorriente.h>
const char *ssid = "Totalplay-BBAB";
const char *password = "BBAB6E45BGkpHq9G";

Motor motor;
Communication com;
SensorCorriente sensor;
int speed = 255;

void ConectarWifi()
{
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void TestMotor()
{
  motor.ControlMotor(true, speed);
  Serial.println("Motor hacia adelante");
  // com.Log("Motor hacia adelante");
  sensor.Sensar();
  delay(2000);

  motor.ControlMotor(true, 0);
  Serial.println("Motor detenido");
  // com.Log("Motor detenido");
  sensor.Sensar();
  delay(2000);

  motor.ControlMotor(false, speed);
  Serial.println("Motor hacia atrás");
  // com.Log("Motor hacia atrás");
  sensor.Sensar();
  delay(2000);

  motor.ControlMotor(true, 0);
  Serial.println("Motor detenido");
  // com.Log("Motor detenido");
  sensor.Sensar();
  delay(2000);
}

void setup()
{
  Serial.begin(115200);
  motor.SetVelocidad(100);

  // ConectarWifi();
}

void loop()
{
  // sendPostRequest(10,2);

  TestMotor();
}


