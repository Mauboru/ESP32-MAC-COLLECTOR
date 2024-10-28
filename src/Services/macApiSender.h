#pragma once

#include <UrlEncode.h> 
#include <HTTPClient.h>

class MacApiSender {
public:
    static void sendMacToApi(String macAddress);
};