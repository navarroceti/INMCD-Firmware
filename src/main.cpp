#include <Arduino.h>
#include <Wire.h>
#include <ServoManager.h>
#include <WebServerManager.h>

ServoManager servoManager;
WebServerManager webServerManager(servoManager);

void setup() {
    Wire.begin();
    Serial.begin(115200);
    while (!Serial);

    servoManager.initialize();

    WiFi.begin("Cabeza", "seguridad");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }
    Serial.println("Conectado a WiFi");
    Serial.println(WiFi.localIP());

    webServerManager.begin();
}

void loop() {
    webServerManager.handleClient();
}


