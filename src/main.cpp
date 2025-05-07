#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include "MLX90614Handler.h"
#include "PulseSensorHandler.h"

MLX90614Handler mlxHandler;
PulseSensorHandler pulseSensorHandler;

void mlxTask(void* parameter) {
    for (;;) {
        mlxHandler.update();
        vTaskDelay(500 / portTICK_PERIOD_MS); // Delay to match the original loop delay
    }
}

void pulseSensorTask(void* parameter) {
    for (;;) {
        pulseSensorHandler.update();
        vTaskDelay(20 / portTICK_PERIOD_MS); // Match the delay in the original loop
    }
}

void setup() {
    Serial.begin(115200);

    // Use WiFiManager for WiFi connection
    // WiFiManager wifiManager;
    // wifiManager.autoConnect("ESP32_AP"); // Creates an access point if no WiFi credentials are saved

    // Serial.println("Connected to WiFi");

    // Initialize MLX90614 sensor
    mlxHandler.begin();

    // Initialize Pulse Sensor
    pulseSensorHandler.begin();

    // Create tasks for Heart Rate Sensor and MLX90614 sensor
    xTaskCreate(mlxTask, "MLX90614 Task", 4096, NULL, 1, NULL);
    xTaskCreate(pulseSensorTask, "Pulse Sensor Task", 4096, NULL, 1, NULL);
}

void loop() {
    // Main loop does nothing, tasks handle everything
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Prevent watchdog timer reset
}
