#include <Arduino.h>
#include "wifi_connect.h"
#include "mqtt_connect.h"
#include "NTPClient.h"
#include "WiFiUdp.h"
#include "current_time.h"

#define LED_BUILDIN 8

WiFiUDP wifi_udp_client;
NTPClient time_client(wifi_udp_client);

uint32_t current_time = 0;

void setup() {
  	pinMode(LED_BUILDIN,OUTPUT);
  	digitalWrite(LED_BUILDIN,HIGH);

  	wifi_connect();
  	mqtt_connect();

	digitalWrite(LED_BUILDIN,LOW);
}

void loop() {
  	time_client.update();

	current_time = time_client.getEpochTime();

  	if (!mqtt_client.connected())
	{
		digitalWrite(LED_BUILDIN,HIGH);
		reconnect();
		digitalWrite(LED_BUILDIN,LOW);
	}

	mqtt_client.loop();
}
