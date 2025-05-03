#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include "HeartRateSensor.h"
#include "MQTTHandler.h"

const char* ssid = "saf";
const char* password = "safer123";
const char* mqttServer = "broker.emqx.io";
const uint16_t mqttPort = 1883;

WiFiClient wifiClient;
MQTTHandler mqttHandler(wifiClient, mqttServer, mqttPort);
HeartRateSensor heartRateSensor;

void mqttTask(void* parameter) {
    for (;;) {
        mqttHandler.loop();
        vTaskDelay(100 / portTICK_PERIOD_MS); // Delay to prevent task hogging CPU
    }
}

void heartRateTask(void* parameter) {
    for (;;) {
        heartRateSensor.update();
        vTaskDelay(100 / portTICK_PERIOD_MS); // Delay to prevent task hogging CPU
    }
}

void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(" connected");

    // Initialize MQTT
    mqttHandler.begin();

    // Initialize Heart Rate Sensor
    heartRateSensor.begin();

    // Create tasks for MQTT and Heart Rate Sensor
    xTaskCreate(mqttTask, "MQTT Task", 4096, NULL, 1, NULL);
    xTaskCreate(heartRateTask, "Heart Rate Task", 4096, NULL, 1, NULL);
}

void loop() {
    // Main loop does nothing, tasks handle everything
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Prevent watchdog timer reset
    // You can also add other code here if needed
    // mqttHandler.publish("triana/test", "Hello from Triana!");
}