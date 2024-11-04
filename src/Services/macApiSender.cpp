#include "macApiSender.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <ctime> 

void MacApiSender::sendMacToApi(String macAddresses[], int count) {
    String URL = "http://85.31.63.241:8082/inserirMacsCapturados";
    HTTPClient http;

    http.begin(URL);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<2048> doc;
    JsonArray macArray = doc.createNestedArray("macs"); 

    for (int i = 0; i < count; i++) {
        JsonObject macObject = macArray.createNestedObject();
        macObject["MAC"] = macAddresses[i];
        
        time_t now = time(nullptr);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
        macObject["data_hora_captura"] = timestamp;
        macObject["id_esp_macAdress"] = 1; 
    }

    String jsonPayload;
    serializeJson(doc, jsonPayload);

    Serial.println("JSON enviado:");
    Serial.println(jsonPayload);

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode == 201 || httpResponseCode == 200) {
        String payload = http.getString();
        Serial.println("Resposta da API:");
        Serial.println(payload);
    } else {
        Serial.print("Erro ao tentar enviar os dados! Código: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
