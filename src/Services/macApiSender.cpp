#include "macApiSender.h"
#include <ArduinoJson.h>

void MacApiSender::sendMacToApi(String macAddress) {
    String URL = "http://85.31.63.241:8082/inserirMacCapturado";

    HTTPClient http;
    http.begin(URL);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload;
    StaticJsonDocument<200> doc;
    doc["MAC"] = macAddress;
    doc["id_esp_macAdress"] = 1;
    serializeJson(doc, jsonPayload);

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode == 201) {
        String payload = http.getString();
        Serial.println("Resposta da API:");
        Serial.println(payload);
    } else {
        Serial.print("Erro ao tentar enviar os dados! Código: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}