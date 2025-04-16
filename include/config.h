#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

extern std::string mqtt_server;
extern uint16_t port;
extern const char* root_ca;
extern std::string mqtt_client_id;
extern int8_t device_id;
extern std::string mqtt_username;
extern std::string mqtt_password;

extern std::string ssid;
extern std::string password;

extern std::string wake_device_MAC;

#endif