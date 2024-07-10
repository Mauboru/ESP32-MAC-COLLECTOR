#include <Arduino.h>
#include <vector>

std::vector<String> macAddresses;

class MacAddress {
    public:
        void collect() {
            if (Serial.available() > 0) {
                String packetData = Serial.readStringUntil('\n');
                Serial.println("Received raw data: " + packetData);
                String macAddress = extractMacAddress(packetData);

                if (!macAddress.isEmpty() && !macAddressExists(macAddress)) {
                    macAddresses.push_back(macAddress);
                    Serial.println("MAC Address added: " + macAddress);
                } else {
                    Serial.println("Duplicate or invalid MAC Address: " + macAddress);
                }
            } else {
                Serial.println("No data available");
            }

            delay(1000);
        }

    private:
        String extractMacAddress(const String& packetData) {
            int start = packetData.indexOf("MAC=");
            if (start == -1) {
                return "";
            }
            start += 4;
            int end = packetData.indexOf(",", start);
            if (end == -1) {
                end = packetData.length();
            }
            return packetData.substring(start, end);
        }

        bool macAddressExists(const String& macAddress) {
            for (const String& addr : macAddresses) {
                if (addr == macAddress) {
                    return true;
                }
            }
            return false;
        }
};