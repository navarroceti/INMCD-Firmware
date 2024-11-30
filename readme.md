# INMCD - Firmware ESP32

Este proyecto es la etapa del firmware y esta desarrollado usando PlataformIO
y la tarjeta de desarrollo ESP32 DEVKit V1

## Diagrama de coneccion
- PWM 
- ADC
- AB ENCODER

## Arquitectura

### Generador de señales [Python]
- Generar funciones usando Latex

### Firmware [ESP32]
---
- Conectarse a red WIFI       - Posible conflicto con ADC
- Recibir ID de dispositivo
- Recibir señal de control
---
- Usar señal de control       - PWM WRITE
- Leer el sensor de corriente - ANALOG READ - Maximo voltaje 3.6v
- Leer el enconder            - [ROTARY AB ENCODER](https://github.com/MaffooClock/ESP32RotaryEncoder?tab=readme-ov-file) 
---
- Enviar lectura por internet - WRITE HTTP POST OR SOCKETS
---

### Interfaz WEB [Gradio]
- Almacenar Lectura en DB
- Desplegar lectura en tiempo Real

## Hardware

### Encoder


### Motor
Que tamaño de motor es?
Proporcion de reduccion de la caja

### Sensor Corriente
Como calibrar el sensor??
Proteger ESP32 - Maximo voltaje 3.6v
Resolucion del sensor

### Puente H
Maxima Frecuencia
Rango de trabajo

### Tarjeta de Desarrollo
2 nucleos
Velocidad de trabajo
Conexion WiFI

[SOM](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)

[SOC](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)



---------------------------------------
Generar señal con Python
---------------------------------------

-FIRMWARE------------------------------
Conectarse a red WIFI       - Posible conflicto con ADC
Recibir ID de dispositivo
Recibir señal de control

Usar señal de control       - PWM WRITE
Leer el sensor de corriente - ANALOG READ - Maximo voltaje 3.6v
Leer el enconder            - ROTARY AB ENCODER https://github.com/MaffooClock/ESP32RotaryEncoder?tab=readme-ov-file

Enviar lectura por internet - WRITE HTTP POST OR SOCKETS
---------------------------------------

---------------------------------------
Almacenar Lectura en DB
Desplegar lectura en tiempo Real
---------------------------------------
