#pragma once

#include <Arduino.h>
#include <vector>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <time.h>
#include <map>

extern std::map<String, unsigned long> macAddresses;

class MacAddress {
public:
    void collect();
    static String printMacTable();
private:
    static void extractAndProcessPacket(const wifi_promiscuous_pkt_t* packet);
    static String extractMacAddress(const uint8_t* macAddr);
    static bool macAddressExists(const String& macAddress);
    static String filtrarMacFixos(String filter);
};