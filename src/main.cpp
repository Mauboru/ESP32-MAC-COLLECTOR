#include <Arduino.h>
#include "Utils/WiFiManager.h"

WifiManager wificonnect;

void setup() {
    wificonnect.connect();
}

void loop() {
    // 
}