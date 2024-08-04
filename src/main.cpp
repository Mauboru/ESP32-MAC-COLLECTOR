#include <Arduino.h>
#include <Update.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "Utils/MacAddress.h"
#include "Utils/WifiManager.h"

WifiManager wifiConnect;
MacAddress macAddress;

void setup() {
    Serial.begin(9600);
    wifiConnect.connect();
    macAddress.collect();
}

void loop() {
    delay(60000); // 1 minuto
    whatsapp.sendWhatsAppMessage(macAddress.printMacTable());
}