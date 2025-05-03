#include "MQTTHandler.h"
#include <Arduino.h>

MQTTHandler::MQTTHandler(Client& networkClient, const char* server, uint16_t port)
    : mqttClient(networkClient), mqttServer(server), mqttPort(port) {}

void MQTTHandler::begin() {
    mqttClient.setServer(mqttServer, mqttPort);
}

void MQTTHandler::loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();
}

void MQTTHandler::publish(const char* topic, const char* payload) {
    mqttClient.publish(topic, payload);
}

void MQTTHandler::subscribe(const char* topic) {
    mqttClient.subscribe(topic);
}

void MQTTHandler::reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect("ESP32Client")) {
            Serial.println("connected");
            // Resubscribe to topics if needed
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}