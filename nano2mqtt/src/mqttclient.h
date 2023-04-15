#pragma once

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <functional>
#include <string>

class MqttClient{
    const char* mqtt_server = "192.168.168.112";
    std::string name;
    std::string prefix;

    WiFiClient espClient;
    PubSubClient client {espClient};

    unsigned int lastMsg = 0;
    std::string status {"offline"};

    void setupWifi();
    void initOta();
    void reconnect();
    
public:
    MqttClient(std::string name, std::string prefix, std::function<void(char* topic, byte* payload, unsigned int length)> cmdCallback);
    void operate();
    void publish(std::string subtopic, std::string payload);
    void sendRssi();
};

