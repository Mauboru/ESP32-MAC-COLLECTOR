#include <WiFiManager.h>
#include <Arduino.h>

class WifiManager {
public:
    void connect() {
        Serial.begin(115200);
        WiFiManager wm;
        bool res;
        res = wm.autoConnect("AutoConnectAP", "password");

        if (!res) {
            Serial.println("Failed to connect");
        } else {
            Serial.println("connected...yeey :)");
        }
    }
};