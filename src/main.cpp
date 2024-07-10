#include <Arduino.h>
#include "Utils/WiFiManager.h"
#include "Utils/MacAdress.h"

WifiManager wificonnect;
MacAdress macadress;

// void setup() {
//     Serial.begin(115200);
//     wificonnect.connect();
// }

// void loop() {
//     macadress.collect();
// }

char Dados;

void setup() {
    Serial.begin(115200);
    wificonnect.connect();
}

void loop() {
    Dados = Serial.read();

    if(Dados == 'a'){
        Serial.print("deu bom");
    }
    if(Dados == 'b'){
        Serial.print("deu ruim");
    }
}