#include <Arduino.h>
#include "Utils/WiFiManager.h"
#include "Utils/MacAddress.h"

WifiManager wificonnect;
MacAddress macaddress;

void setup() {
    Serial.begin(115200);
    wificonnect.connect();
    macaddress.collect();
}

void loop() {
    //
}