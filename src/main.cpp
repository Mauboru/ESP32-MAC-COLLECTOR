#include <Arduino.h>
#include <Update.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <time.h>
#include "../lib/MacAddress/MacAddress.h"
#include "Utils/WifiManager.h"
#include "../lib/WhatsApp/WhatsApp.h"
#include "Services/macApiSender.h"

WifiManager wifiConnect;
MacAddress macAddress;
WhatsApp whatsapp;
MacApiSender macApiSender;

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 3600000; //3600000 1 hora

void setup() {
    Serial.begin(9600);
    wifiConnect.connect();
}

void loop() {
    macAddresses.clear();
    delay(10000);
    macAddress.collect();

    if (WiFi.status() != WL_CONNECTED) wifiConnect.connect();

    if (millis() - lastSendTime >= sendInterval) {      
        whatsapp.sendWhatsAppMessage(macAddress.printMacTable());
        lastSendTime = millis();
    }

    //Serial.println(macAddress.printMacTable());

    delay(10000);
}