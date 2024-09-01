#include <Arduino.h>
#include <vector>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <esp_wifi.h>
#include "Utils/WhatsApp.h"
#include "Utils/IdentifierMac.h"

std::vector<String> macAddresses;
std::vector<String> macManufacturers;
WhatsApp whatsapp;
IdentifierMac identifierMac;

class MacAddress {
public:
    void collect() {
        esp_wifi_set_promiscuous(true);
        esp_wifi_set_promiscuous_rx_cb([](void* buf, wifi_promiscuous_pkt_type_t type) {
            const wifi_promiscuous_pkt_t* packet = reinterpret_cast<wifi_promiscuous_pkt_t*>(buf);
            extractAndProcessPacket(packet);
        });
    }

    static String printMacTable() {
        String macTable = "*Endereços MAC identificados: " + String(macAddresses.size()) +  "*\n\n";
        for (size_t i = 0; i < macAddresses.size(); ++i) {
            macTable += macAddresses[i] + " - " + macManufacturers[i] + "\n";
        }
        macTable += "\n--------------------------------------";
        return macTable;
    }

private:
    static void extractAndProcessPacket(const wifi_promiscuous_pkt_t* packet) {
        constexpr int mgmtHeaderSize = 36;

        if (packet->rx_ctrl.sig_len < mgmtHeaderSize) {
            return;
        }

        const uint8_t* payload = packet->payload;
        payload += 10;
        String senderMac = extractMacAddress(payload);

        if (!senderMac.isEmpty() && !macAddressExists(senderMac)) {
            macAddresses.push_back(senderMac);
            String manufacturer = identifierMac.fetchManufacturer(senderMac);
            macManufacturers.push_back(manufacturer);
            String macTable = printMacTable();
            Serial.println(macTable);
            delay(1000);
        }
    }

    static String extractMacAddress(const uint8_t* macAddr) {
        char macStr[18];
        sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
                macAddr[0], macAddr[1], macAddr[2],
                macAddr[3], macAddr[4], macAddr[5]);
        return String(macStr);
    }

    static bool macAddressExists(const String& macAddress) {
        for (const String& addr : macAddresses) {
            if (addr == macAddress) {
                return true;
            }
        }
        return false;
    }
};