#pragma once

#include <UrlEncode.h>
#include <HTTPClient.h>

class WhatsApp {
public:
    String phoneNumber = "+554184987049";
    String apiKey = "6400082";

    void sendWhatsAppMessage(String message);
};