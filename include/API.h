#pragma once
#include <WiFi.h>
#include <HTTPClient.h>

class API
{
private:

    const char *serverName = "https://myth.logiasimbolica.com/"; // Replace with your server URL
public:
    API();
    ~API();

    void sendGetRequest()
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            HTTPClient http;
            http.begin(serverName);
            int httpResponseCode = http.GET();

            if (httpResponseCode > 0)
            {
                String payload = http.getString();
                Serial.println(payload);
            }
            else
            {
                Serial.print("Error on HTTP request: ");
                Serial.println(httpResponseCode);
            }
            http.end();
        }
        else
        {
            Serial.println("WiFi Disconnected");
        }
    }

    void sendPostRequest(int a, int b)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            HTTPClient http;
            http.begin("https://myth.logiasimbolica.com/call/predict");
            http.addHeader("Content-Type", "application/json");

            String jsonData = "{\"data\": [" + String(a) + ", " + String(b) + "]}";
            int httpResponseCode = http.POST(jsonData);

            if (httpResponseCode > 0)
            {
                String response = http.getString();
                Serial.println(response);

                // Extract EVENT_ID from the response
                int startIndex = response.indexOf("\"") + 1;
                int endIndex = response.indexOf("\"", startIndex);
                String eventId = response.substring(startIndex, endIndex);

                // Make the second GET request
                http.end();
                http.begin("https://myth.logiasimbolica.com/call/predict/" + eventId);
                httpResponseCode = http.GET();

                if (httpResponseCode > 0)
                {
                    String eventResponse = http.getString();
                    Serial.println(eventResponse);
                }
                else
                {
                    Serial.print("Error on HTTP request: ");
                    Serial.println(httpResponseCode);
                }
            }
            else
            {
                Serial.print("Error on HTTP POST request: ");
                Serial.println(httpResponseCode);
            }
            http.end();
        }
        else
        {
            Serial.println("WiFi Disconnected");
        }
    }
};
