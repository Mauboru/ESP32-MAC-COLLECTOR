#include <UrlEncode.h> 
#include <HTTPClient.h>

class WhatsApp {
public:
    String phoneNumber = "+554184987049";
    String apiKey = "6400082";

    void sendWhatsAppMessage(String message) {
        String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&text=" + urlEncode(message) + "&apikey=" + apiKey;    
        HTTPClient http;
        http.begin(url);
        
        uint16_t httpResponseCode = http.GET();

        if (httpResponseCode == 200){                                     
            Serial.println("Mensagem enviada com sucesso!");  
            delay(1000);
        } else {
            Serial.println("Erro ao tentar enviar a mensagem!");
            Serial.print("Código HTTP: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    }
};