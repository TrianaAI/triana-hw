#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include "HeartRateSensor.h"
#include "MQTTHandler.h"

const char* mqttServer = "broker.emqx.io";
const uint16_t mqttPort = 1883;

WiFiClient wifiClient;
MQTTHandler mqttHandler(wifiClient, mqttServer, mqttPort);
HeartRateSensor heartRateSensor;

void mqttTask(void* parameter) {
    static unsigned long lastPublishTime = 0;
    static int bpmSum = 0;
    static int bpmCount = 0;

    for (;;) {
        mqttHandler.loop();

        // Collect BPM values over 5 seconds
        int bpm = heartRateSensor.getAverageBPM();
        if (bpm > 0) { // Only consider valid BPM values
            bpmSum += bpm;
            bpmCount++;
        }

        // Publish the average BPM every 5 seconds
        if (millis() - lastPublishTime >= 5000) {
            if (bpmCount > 0) {
                int averageBPM = bpmSum / bpmCount;
                char payload[16];
                snprintf(payload, sizeof(payload), "%d", averageBPM);
                mqttHandler.publish("triana/heartrate/bpm", payload);

                // Reset the sum and count for the next interval
                bpmSum = 0;
                bpmCount = 0;
            }
            lastPublishTime = millis();
        }

        vTaskDelay(100 / portTICK_PERIOD_MS); // Delay to prevent task hogging CPU
    }
}

void heartRateTask(void* parameter) {
    for (;;) {
        if (mqttHandler.isHeartRateScanEnabled()) { // Only scan if enabled via MQTT
            heartRateSensor.update();
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Delay to prevent task hogging CPU
    }
}

void setup() {
    Serial.begin(115200);

    // Use WiFiManager for WiFi connection
    WiFiManager wifiManager;
    wifiManager.autoConnect("ESP32_AP"); // Creates an access point if no WiFi credentials are saved

    Serial.println("Connected to WiFi");

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