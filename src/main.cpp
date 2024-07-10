#include <Arduino.h>
#include "Utils/WiFiManager.h"
#include "Utils/MacAddress.h"

WifiManager wifiConnect;
MacAddress macAddress;

void setup() {
    Serial.begin(115200);
    wifiConnect.connect();
    macAddress.collect();
}

void loop() {
    //
}