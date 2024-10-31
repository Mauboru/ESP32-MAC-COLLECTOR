#include "WhatsApp.h"

void WhatsApp::sendWhatsAppMessage(String message) {
    String url = "https://api.callmebot.com/whatsapp.php?phone=" + 
                 phoneNumber + "&text=" + urlEncode(message) + 
                 "&apikey=" + apiKey;

    HTTPClient http;
    http.begin(url);
    uint16_t httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
        Serial.println("Mensagem enviada com sucesso!");
    } else {
        Serial.println("Erro ao tentar enviar a mensagem!");
        Serial.print("Código HTTP: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}