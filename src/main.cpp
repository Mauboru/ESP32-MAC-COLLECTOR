#include <Arduino.h>
#include "Utils/WiFiManager.h"
#include "Utils/MacAddress.h"

WifiManager wificonnect;
MacAddress macadress;

void setup() {
    Serial.begin(115200);
    wificonnect.connect();
}

void loop() {
    macadress.collect();
}