#include <Arduino.h>
#include <Update.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "Utils/MacAddress.h"
#include "Utils/WifiManager.h"
#include "Utils/WhatsApp.h"

WifiManager wifiConnect;
MacAddress macAddress;
WhatsApp whatsapp;

void setup() {
    Serial.begin(9600);
    wifiConnect.connect();
    macAddress.collect();
}

void loop() {
    delay(60000);
    whatsapp.sendWhatsAppMessage(macAddress.printMacTable());
}