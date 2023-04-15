#include "mqttclient.h"
#include "secrets.h"
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

MqttClient::MqttClient(std::string name, std::string prefix, std::function<void(char* topic, byte* payload, unsigned int length)> cmdCallback)
:name(name)
,prefix(prefix)
{
  if( prefix.back() != '/'){
    prefix.append("/");
  }

  setupWifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(cmdCallback);
}

void MqttClient::setupWifi() {
  delay(10);
  //Serial.println();
  //Serial.print("Connecting to ");
  //Serial.println(ssid);

  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(name.c_str());
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());

  initOta();
}

void MqttClient::initOta(){
  ArduinoOTA.setHostname(name.c_str());
  ArduinoOTA.setPassword(OTAPASSWORD);
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
    });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void MqttClient::reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    if (client.connect(name.c_str(), nullptr, nullptr, std::string(prefix + "status").c_str(), 0, true, "offline")) {
      //Serial.println("connected");
      client.publish(std::string(prefix + "status").c_str(), "online");
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(client.state());
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MqttClient::operate(){
  if (!client.connected()){
    reconnect();
  }
  client.loop();
  ArduinoOTA.handle();

  //every sec
  unsigned long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    sendRssi();
  }
}

void MqttClient::publish(std::string subtopic, std::string payload)
{
  client.publish(std::string(prefix + subtopic).c_str(), payload.c_str());
}

void MqttClient::sendRssi(){
  char buf[10]; 
  std::sprintf(buf, "%d", WiFi.RSSI()); 
  client.publish(std::string(prefix + "RSSI").c_str(), buf);
}