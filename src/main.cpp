#include <Arduino.h>
#include <Communication.h>
#include <WifiManager.h>
#include <Adafruit_PWMServoDriver.h>

Communication com;
WifiManager wifi;

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

int angleToPulse(int ang){
	int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
	Serial.print("Angle: ");Serial.print(ang);
	Serial.print(" pulse: ");Serial.println(pulse);
	return pulse;
 }

#include <Wire.h>

void setup()
{
	Wire.begin(); // Usa los pines por defecto: SDA=21, SCL=22
	Serial.begin(115200);
	while (!Serial); // Espera que el puerto esté listo

	Serial.println("Buscando dispositivos I2C...");
	byte count = 0;
	for (byte i = 1; i < 127; ++i)
	{
		Wire.beginTransmission(i);
		if (Wire.endTransmission() == 0)
		{
			Serial.print("Encontrado dispositivo en 0x");
			Serial.println(i, HEX);
			count++;
		}
	}
	if (count == 0)
		Serial.println("¡Ningún dispositivo I2C encontrado!");
	else
	{
		if (board1.begin())
		{
			board1.setPWMFreq(50);
			for (size_t i = 0; i < 16; i++)
			{
				board1.setPWM(i, 0, angleToPulse(0));
			}
			board1.setPWM(0, 0, angleToPulse(0));
			board1.setPWM(1, 0, angleToPulse(45));
			board1.setPWM(2, 0, angleToPulse(90));
			board1.setPWM(3, 0, angleToPulse(135));
			board1.setPWM(4, 0, angleToPulse(180));

			board1.setPWM(5, 0, angleToPulse(0));
			board1.setPWM(6, 0, angleToPulse(45));
			board1.setPWM(7, 0, angleToPulse(90));
			board1.setPWM(8, 0, angleToPulse(135));
			board1.setPWM(9, 0, angleToPulse(180));

			board1.setPWM(10, 0, angleToPulse(0));
			board1.setPWM(11, 0, angleToPulse(45));
			board1.setPWM(12, 0, angleToPulse(90));
			board1.setPWM(13, 0, angleToPulse(135));
			board1.setPWM(14, 0, angleToPulse(180));
			


			Serial.println("Encontrado PCA9685 I2C Servo Driver en 0x40");
		}
		else
		{
			Serial.println("No se encontró el PCA9685 I2C Servo Driver en 0x40");
		}
	}
}
void loop()
{
	int speed = 800;

	board1.setPWM(15, 0, angleToPulse(180));
	delay(speed);
	board1.setPWM(15, 0, angleToPulse(135));
	delay(speed);

	board1.setPWM(14, 0, angleToPulse(180));
	delay(speed);
	board1.setPWM(14, 0, angleToPulse(90));
	delay(speed);
}
