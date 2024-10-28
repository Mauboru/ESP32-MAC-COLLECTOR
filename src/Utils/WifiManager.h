#pragma once

#include <WiFiManager.h>
#include <Arduino.h>

class WifiManager {
public:
    void connect() {
        WiFiManager wm;
        if (!wm.autoConnect("TecnoMaub", "password")) {
            Serial.println("Failed to connect!!");
        } else {
            Serial.println("Successful connection!!");
        }
    }
};