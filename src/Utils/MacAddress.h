#include <Arduino.h>
#include <vector>
#include "WiFi.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

std::vector<String> macAddresses;
// const char* webhook_url = "https://script.google.com/macros/s/AKfycbw02LrScNgiReoJ_I1wli4CPoODVsw9FSREWOgSUwyv7uNCLLurywRLLn2GWIHckV1L/exec";

class MacAddress {
public:
    void collect() {
        esp_wifi_set_promiscuous(true);
        esp_wifi_set_promiscuous_rx_cb([](void* buf, wifi_promiscuous_pkt_type_t type) {
            const wifi_promiscuous_pkt_t* packet = reinterpret_cast<wifi_promiscuous_pkt_t*>(buf);
            extractAndProcessPacket(packet);
        });
    }

    static void printMacTable() {
        Serial.println("--------------------");
        Serial.println("MAC Address Table:");
        for (const auto& mac : macAddresses) {
            Serial.println(mac);
        }
        Serial.println("--------------------");
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
            printMacTable();
            // sendToGoogleSheets(senderMac);
        } else {
            // print caso seja duplicado ou invalido
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

    static void sendToGoogleSheets(const String& macAddress) {
        if(WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            http.begin(webhook_url);

            http.addHeader("Content-Type", "application/json");

            StaticJsonDocument<200> doc;
            doc["macAddress"] = macAddress;

            String requestBody;
            serializeJson(doc, requestBody);

            int httpResponseCode = http.POST(requestBody);

            if (httpResponseCode > 0) {
                String response = http.getString();
                Serial.println(httpResponseCode);
                Serial.println(response);
            } else {
                Serial.print("Error on sending POST: ");
                Serial.println(httpResponseCode);
            }

            http.end();
        } else {
            Serial.println("Error in WiFi connection");
        }
    }
};