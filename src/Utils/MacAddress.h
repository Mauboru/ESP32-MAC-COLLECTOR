#include <Arduino.h>
#include <vector>

std::vector<String> macAddresses;

class MacAddress {
    public:
        void collect() {
            //criar codiogo do snifferWifiMac
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