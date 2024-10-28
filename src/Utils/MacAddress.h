#pragma once

#include <Arduino.h>
#include <vector>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <esp_wifi.h>

extern std::vector<String> macAddresses;

class MacAddress {
public:
    void collect();
    static String printMacTable();
private:
    static void extractAndProcessPacket(const wifi_promiscuous_pkt_t* packet);
    static String extractMacAddress(const uint8_t* macAddr);
    static bool macAddressExists(const String& macAddress);
};
