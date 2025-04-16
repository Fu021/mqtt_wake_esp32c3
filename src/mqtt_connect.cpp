#include "mqtt_connect.h"
#include "config.h"
#include "WiFiClientSecure.h"
#include "ArduinoJson.h"
#include "current_time.h"
#include "wake.h"

#define CHECK_ALIVE 0
#define ALIVE 1
#define WAKE 2

WiFiClientSecure wifi_client;
PubSubClient mqtt_client(wifi_client);
JsonDocument alive_reply;

void mqtt_connect()
{
    alive_reply["id"] = device_id;
    alive_reply["msg"] = ALIVE;
    alive_reply["time"] = 0;

    wifi_client.setCACert(root_ca);
    mqtt_client.setServer(mqtt_server.c_str(), port);
    mqtt_client.setCallback(callback);

    reconnect();
}

void callback(char* topic, byte* payload, unsigned int length)
{
    std::string message = "";
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, message);
  
    if (error)
        return;

    int8_t id = doc["id"];
    int8_t msg = doc["msg"];
    uint32_t time = doc["time"];

    if (id != device_id)
        return;
    if (current_time - time > 300)
        return;
    
    if (msg == CHECK_ALIVE)
    {
        alive_reply["time"] = current_time;
        serializeJson(alive_reply,message);
        mqtt_client.publish("wake",message.c_str());
    }
    if (msg == WAKE)
    {
        wake();
    }
        
}

void reconnect()
{
    while (!mqtt_client.connected()) 
    {
        if (mqtt_client.connect(mqtt_client_id.c_str(), mqtt_username.c_str(), mqtt_password.c_str())) 
        {
            mqtt_client.subscribe("wake");
        } 
        else 
        {
            delay(500);
        }
    }
}