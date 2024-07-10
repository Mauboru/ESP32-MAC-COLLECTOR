#include <WiFiManager.h>
#include <Arduino.h>

class WifiManager {
public:
    void connect() {
        WiFiManager wm;
        bool res;
        res = wm.autoConnect("TecnoMaub", "password");

        if (!res) {
            Serial.println("Failed to connect!!");
        } else {
            Serial.println("Sucessful to connect!!");
        }
    }
};