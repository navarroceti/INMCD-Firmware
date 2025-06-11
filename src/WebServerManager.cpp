#include "WebServerManager.h"
#include <Arduino.h>

WebServerManager::WebServerManager(ServoManager& manager) : server(80), servoManager(manager) {}

void WebServerManager::handleRoot() {
    String html = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
            <title>Control de Servos</title>
            <script>
                function updateServo(servo, angle) {
                    var xhr = new XMLHttpRequest();
                    xhr.open("GET", `/setServo?servo=${servo}&angle=${angle}`, true);
                    xhr.send();
                }

                function updateSpeed(speed) {
                    var xhr = new XMLHttpRequest();
                    xhr.open("GET", `/setSpeed?speed=${speed}`, true);
                    xhr.send();
                }
            </script>
        </head>
        <body>
            <h1>Control de Servos</h1>
            <div>
                <h3>Control de Servos con Sliders</h3>
                %SLIDERS%
            </div>
            <div>
                <h3>Velocidad de Transición</h3>
                <label for="speed">Velocidad (ms por paso):</label>
                <input type="number" id="speed" min="1" max="100" value="10" oninput="updateSpeed(this.value)">
            </div>
        </body>
        </html>
    )rawliteral";

    String sliders = "";
    for (int i = 0; i < 16; i++) {
        sliders += "<label for='servo" + String(i) + "'>Servo " + String(i) + ":</label>";
        sliders += "<input type='range' id='servo" + String(i) + "' min='0' max='180' value='90' ";
        sliders += "style='width: 300px;' ";
        sliders += "oninput='updateServo(" + String(i) + ", this.value)'><br><br>";
    }

    html.replace("%SLIDERS%", sliders);
    server.send(200, "text/html", html);
}

void WebServerManager::handleSetServo() {
    if (server.hasArg("servo") && server.hasArg("angle")) {
        int servo = server.arg("servo").toInt();
        int angle = server.arg("angle").toInt();
        servoManager.moveServoSmooth(servo, angle);
        server.send(200, "text/plain", "Servo actualizado");
    } else {
        server.send(400, "text/plain", "Faltan parámetros");
    }
}

void WebServerManager::handleSetSpeed() {
    if (server.hasArg("speed")) {
        int speed = server.arg("speed").toInt();
        servoManager.setTransitionSpeed(speed);
        server.send(200, "text/plain", "Velocidad actualizada");
    } else {
        server.send(400, "text/plain", "Falta el parámetro de velocidad");
    }
}

void WebServerManager::begin() {
    server.on("/", [this]() { handleRoot(); });
    server.on("/setServo", [this]() { handleSetServo(); });
    server.on("/setSpeed", [this]() { handleSetSpeed(); });
    server.begin();
}

void WebServerManager::handleClient() {
    server.handleClient();
}
