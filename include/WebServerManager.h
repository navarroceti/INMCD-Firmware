#ifndef WEBSERVERMANAGER_H
#define WEBSERVERMANAGER_H

#include <WebServer.h>
#include "ServoManager.h"

class WebServerManager {
private:
    WebServer server;
    ServoManager& servoManager;

    void handleRoot();
    void handleSetServo();
    void handleSetSpeed();

public:
    WebServerManager(ServoManager& manager);
    void begin();
    void handleClient();
};

#endif
