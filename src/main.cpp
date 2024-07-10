#include <Arduino.h>
#include "Utils/WiFiManager.h"
#include "Utils/MacAddress.h"
#include <Update.h>
#include <WebServer.h>
#include <DNSServer.h>

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