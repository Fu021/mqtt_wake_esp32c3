#ifndef MQTT_CONNECT_H_
#define MQTT_CONNECT_H_

#include <Arduino.h>
#include "PubSubClient.h"

extern PubSubClient mqtt_client;

void mqtt_connect();
void reconnect();
void callback(char* topic, byte* payload, unsigned int length);

#endif