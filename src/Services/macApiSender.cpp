#include "macApiSender.h"
#include <ArduinoJson.h>

void MacApiSender::sendMacToApi(String macAddresses[], int count) {
    String URL = "http://85.31.63.241:8082/inserirMacCapturado";

    HTTPClient http;
    http.begin(URL);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<512> doc;
    JsonArray macArray = doc.to<JsonArray>();

    for (int i = 0; i < count; i++) {
        JsonObject macObject = macArray.createNestedObject();
        macObject["MAC"] = macAddresses[i];
        macObject["id_esp_macAdress"] = 1; // aqui alterar pois esta fixo
    }

    String jsonPayload;
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