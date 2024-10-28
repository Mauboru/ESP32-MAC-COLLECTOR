#include <UrlEncode.h> 
#include <HTTPClient.h>

class MacApiSender {
public:
    void sendMacToApi(String message) {
        String url = "";    
        HTTPClient http;
        http.begin(url);
        
        uint16_t httpResponseCode = http.GET();

        if (httpResponseCode == 200){                                     
            Serial.println("Dados enviados com sucesso!");  
            delay(1000);
        } else {
            Serial.println("Erro ao tentar enviar os dados!");
            Serial.print("Código HTTP: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    }
};