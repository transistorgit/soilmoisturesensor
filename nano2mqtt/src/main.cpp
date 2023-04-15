#include <Arduino.h>
#include "mqttclient.h"


MqttClient* mqttClient = nullptr;

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    std::string topicStr {topic};
    if(topicStr.compare("iot/garden/xxx")==0){
    }    
}

void setup() {
    // put your setup code here, to run once:
    mqttClient = new MqttClient("Nano_Humidity", "iot/garten/", mqttCallback);
}

void loop() {
  // put your main code here, to run repeatedly:
  mqttClient->operate();
}