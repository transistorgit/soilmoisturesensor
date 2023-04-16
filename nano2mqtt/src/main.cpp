#include <Arduino.h>
#include "mqttclient.h"

#define LED_PIN 2 //ESP-01 -> Pin 1 / ESP-01S -> Pin 2
MqttClient* mqttClient = nullptr;

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  std::string topicStr {topic};
  if(topicStr.compare("iot/garden/xxx")==0){
  }    
}

void setup() {
  mqttClient = new MqttClient("Soil_Moisture", "iot/garten/", mqttCallback);
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  mqttClient->operate();
  
  //read messages like "S1:44:XX"  sensorid separator percent value 
  if(Serial.available()<5){
    return;
  }

  while(Serial.available() && Serial.read() != 'S'){
  }

  auto id = Serial.parseInt();
  if(id < 0 || id > 7){
    while(Serial.available()){
      Serial.read();//purge input buffer
    }
    return;
  }

  if(Serial.read() != ':'){
    while(Serial.available()){
      Serial.read();//purge input buffer
    }
    return;
  }

  auto value = Serial.parseInt();
  if(value < 0 || value > 100){
    while(Serial.available()){
      Serial.read();//purge input buffer
    }
    return;
  }

  digitalWrite(LED_PIN, LOW);
  mqttClient->publish((std::string("SoilMoisture/") + std::to_string(id)).c_str(), std::to_string(value).c_str());
  digitalWrite(LED_PIN, HIGH);
}
