#include "MacAddress.h"

std::vector<String> macAddresses;

void MacAddress::collect() {
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb([](void* buf, wifi_promiscuous_pkt_type_t type) {
        const wifi_promiscuous_pkt_t* packet = reinterpret_cast<wifi_promiscuous_pkt_t*>(buf);
        extractAndProcessPacket(packet);
    });
}

String MacAddress::printMacTable() {
    String macTable = "*MAC Address identificados:*\n";
    for (const auto& mac : macAddresses) {
        macTable += mac + "\n";
    }
    macTable += "--------------------";
    return macTable;
}

void MacAddress::extractAndProcessPacket(const wifi_promiscuous_pkt_t* packet) {
    constexpr int mgmtHeaderSize = 36;

    if (packet->rx_ctrl.sig_len < mgmtHeaderSize) return;

    const uint8_t* payload = packet->payload;
    payload += 10;
    String senderMac = extractMacAddress(payload);

    if (!senderMac.isEmpty() && !macAddressExists(senderMac)) {
        macAddresses.push_back(senderMac);
    }
}

String MacAddress::extractMacAddress(const uint8_t* macAddr) {
    char macStr[18];
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
            macAddr[0], macAddr[1], macAddr[2],
            macAddr[3], macAddr[4], macAddr[5]);
    return String(macStr);
}

bool MacAddress::macAddressExists(const String& macAddress) {
    for (const String& addr : macAddresses) {
        if (addr == macAddress) return true;
    }
    return false;
}