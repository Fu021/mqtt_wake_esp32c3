#include "wifi_connect.h"
#include "WiFi.h"
#include "config.h"

void wifi_connect()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(),password.c_str());

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}