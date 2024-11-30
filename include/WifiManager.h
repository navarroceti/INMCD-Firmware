#include <WiFi.h>

class WifiManager
{
private:
    const char *ssid = "Totalplay-BBAB";
    const char *password = "BBAB6E45BGkpHq9G";

public:
    WifiManager() {}
    ~WifiManager() {}
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
};