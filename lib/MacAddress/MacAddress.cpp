#include "MacAddress.h"

std::map<String, unsigned long> macAddresses;

void MacAddress::collect() {
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb([](void* buf, wifi_promiscuous_pkt_type_t type) {
        const wifi_promiscuous_pkt_t* packet = reinterpret_cast<wifi_promiscuous_pkt_t*>(buf);
        extractAndProcessPacket(packet);
    });
}

String MacAddress::printMacTable() {
    String titleMac = "*MAC Address identificados 📵📶*";
    String qtdMac = "*Quantidade coletada:* ";
    String timeCatch = "*Coleta feita em:* ";
    String macTable = "";
    int qtd = 0;

    configTime(-10800, 0, "pool.ntp.org");

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Falha ao obter tempo.");
        return "Erro ao capturar o horário.";
    }

    for (const auto& macEntry : macAddresses) {
        macTable += " - " + macEntry.first + filtrarMacFixos(macEntry.first) + "\n";
        qtd++;
    }

    qtdMac += String(qtd);
    String timeNow = String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min) + ":" + String(timeinfo.tm_sec);
    String result = titleMac + "\n" + "```" + qtdMac + "```" + "\n" + timeCatch + timeNow + "\n\n" + macTable + "\n----------------------------------";

    return result;
}

void MacAddress::extractAndProcessPacket(const wifi_promiscuous_pkt_t* packet) {
    constexpr int mgmtHeaderSize = 36;
    const unsigned long currentTime = millis();

    if (packet->rx_ctrl.sig_len < mgmtHeaderSize) return;

    const uint8_t* payload = packet->payload;
    payload += 10;
    String senderMac = extractMacAddress(payload);

    if (!senderMac.isEmpty()) {
        macAddresses[senderMac] = currentTime;
    }
}

String MacAddress::extractMacAddress(const uint8_t* macAddr) {
    char macStr[18];
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
            macAddr[0], macAddr[1], macAddr[2],
            macAddr[3], macAddr[4], macAddr[5]);
    return String(macStr);
}

String MacAddress::filtrarMacFixos(String filter){
    String macs[][2] = 
    {
        {"38:9A:F6:96:EB:C9", "Josué Henrique"},
        {"5C:C9:D3:3A:6A:78", "COMPUTADOR COWORKING 1"},
        {"5C:CD:5B:20:84:4C", "COMPUTADOR COWORKING 2"},
        {"5C:CD:5B:EE:0E:B3", "COMPUTADOR COWORKING 3"},
        {"5C:CD:5B:EE:0E:A3", "COMPUTADOR COWORKING 4"},
        {"90:9A:4A:DE:42:21", "TP-LINK TECHNOLOGIES CO.,LTD."},
        {"28:EE:52:5A:59:0F", "TP-LINK TECHNOLOGIES CO.,LTD."},
    };             

    for(const auto& mac : macs){
        if(mac[0] == filter){
            return " <-- " + mac[1];
        }
    }
    return "";
}