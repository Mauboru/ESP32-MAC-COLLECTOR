#include <HTTPClient.h>
#include <WebServer.h>
#include <DNSServer.h>

class IdentifierMac {
public:
    static String fetchManufacturer(const String& macAddress) {
        String manufacturer = "Unknown";
        String baseUrl = "https://api.macvendors.com/";
        String url = baseUrl + urlEncode(macAddress);

        HTTPClient http;
        http.begin(url);
        int httpResponseCode = http.GET();
        
        if (httpResponseCode == 200) {
            Serial.println("Informação coletada com sucesso!");
            String payload = http.getString();
            manufacturer = payload;
        } else {
            Serial.println("Erro ao tentar enviar a requisição! Código HTTP: ");
            Serial.println(httpResponseCode);
        }
        
        http.end();
        return manufacturer;
    }
};