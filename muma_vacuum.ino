#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <stdio.h>

#include "config.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

//PubSubClient client(MQTT_HOST, MQTT_PORT);

void setup(void)
{
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PW);
  
  Serial.print("Wifi connecting.");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  Serial.flush();
}
 
void loop(void)
{ 
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    // (clientID, username, password, willTopic, willQoS, willRetain, willMessage)
    if (mqttClient.connect("vacuum1", MQTT_USER, MQTT_PASS, "mumalab/room/vacuum/status", 1, true, "0")) {
      Serial.println("MQTT connection successfull.");
      mqttClient.publish("mumalab/room/vacuum/status","1");
      
    } else {
      Serial.println("MQTT connection failed.");
    }
    
    delay(500);
  }
  delay(1000);
  mqttClient.loop();
  
} 
