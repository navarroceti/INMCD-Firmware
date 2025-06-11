#include <Arduino.h>
#include <Communication.h>
#include <WifiManager.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <WebServer.h>

Communication com;
WifiManager wifi;

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

WebServer server(80); // Servidor web en el puerto 80

int transitionSpeed = 10; // Velocidad de transición predeterminada (ms por paso)

int angleToPulse(int ang) {
    return map(ang, 0, 180, SERVOMIN, SERVOMAX);
}

// Función para mover el servo con transición suave
void moveServoSmooth(int servo, int targetAngle) {
    int currentPulse = board1.getPWM(servo);
    int currentAngle = map(currentPulse, SERVOMIN, SERVOMAX, 0, 180);

    if (currentAngle < targetAngle) {
        for (int angle = currentAngle; angle <= targetAngle; angle++) {
            board1.setPWM(servo, 0, angleToPulse(angle));
            delay(transitionSpeed);
        }
    } else {
        for (int angle = currentAngle; angle >= targetAngle; angle--) {
            board1.setPWM(servo, 0, angleToPulse(angle));
            delay(transitionSpeed);
        }
    }
}

#include <Wire.h>

// Manejar la página principal
void handleRoot() {
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

    // Generar sliders dinámicamente
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

// Manejar la configuración del servo
void handleSetServo() {
    if (server.hasArg("servo") && server.hasArg("angle")) {
        int servo = server.arg("servo").toInt();
        int angle = server.arg("angle").toInt();

        if (servo >= 0 && servo < 16 && angle >= 0 && angle <= 180) {
            moveServoSmooth(servo, angle);
            server.send(200, "text/plain", "Servo actualizado");
        } else {
            server.send(400, "text/plain", "Parámetros inválidos");
        }
    } else {
        server.send(400, "text/plain", "Faltan parámetros");
    }
}

// Manejar la configuración de la velocidad
void handleSetSpeed() {
    if (server.hasArg("speed")) {
        int speed = server.arg("speed").toInt();
        if (speed >= 1 && speed <= 100) {
            transitionSpeed = speed;
            server.send(200, "text/plain", "Velocidad actualizada");
        } else {
            server.send(400, "text/plain", "Velocidad inválida");
        }
    } else {
        server.send(400, "text/plain", "Falta el parámetro de velocidad");
    }
}

void setup() {
    Wire.begin(); // Usa los pines por defecto: SDA=21, SCL=22
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Buscando dispositivos I2C...");
    if (board1.begin()) {
        board1.setPWMFreq(50);

        // Inicializar todos los servos en la posición de 90 grados
        for (size_t i = 0; i < 16; i++) {
            board1.setPWM(i, 0, angleToPulse(90));
        }

        Serial.println("Encontrado PCA9685 I2C Servo Driver en 0x40");
    } else {
        Serial.println("No se encontró el PCA9685 I2C Servo Driver en 0x40");
    }

    // Configurar WiFi
    WiFi.begin("Cabeza", "seguridad"); // Reemplaza con tu SSID y contraseña
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }
    Serial.println("Conectado a WiFi");
    Serial.println(WiFi.localIP());

    // Configurar servidor web
    server.on("/", handleRoot);
    server.on("/setServo", handleSetServo);
    server.on("/setSpeed", handleSetSpeed);
    server.begin();
    Serial.println("Servidor web iniciado");
}

void loop() {
    server.handleClient(); // Manejar solicitudes del servidor web
}


