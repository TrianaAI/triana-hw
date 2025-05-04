#include "MQTTHandler.h"
#include <Arduino.h>

static bool enableHeartRateScan = false; // Flag to enable heart rate scanning

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    if (String(topic) == "triana/device/1/heartrate") {
        if (message == "1") {
            enableHeartRateScan = true;
        } else {
            enableHeartRateScan = false;
        }
    }
}

MQTTHandler::MQTTHandler(Client& networkClient, const char* server, uint16_t port)
    : mqttClient(networkClient), mqttServer(server), mqttPort(port) {}

void MQTTHandler::begin() {
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(mqttCallback); // Set the callback function
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
    if (mqttClient.connected()) {
        return; // Avoid reconnecting if already connected
    }

    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");

        // Generate a unique client ID using the ESP32's chip ID
        String clientId = "ESP32Client-";
        clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

        if (mqttClient.connect(clientId.c_str())) {
            Serial.println("connected");
            mqttClient.subscribe("triana/device/1/heartrate"); // Subscribe to the topic
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

bool MQTTHandler::isHeartRateScanEnabled() {
    return enableHeartRateScan;
}