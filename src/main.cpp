#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include "MLX90614Handler.h"
#include "PulseSensorHandler.h"
#include "FirebaseAsyncHandler.h"

MLX90614Handler mlxHandler;
PulseSensorHandler pulseSensorHandler;
FirebaseAsyncHandler firebaseAsyncHandler;

void mlxTask(void* parameter) {
    for (;;) {
        // mlxHandler.update();
        // mlxHandler.updateWithFirebase(firebaseAsyncHandler); // Pass FirebaseAsyncHandler reference
        vTaskDelay(500 / portTICK_PERIOD_MS); // Delay to match the original loop delay
    }
}

void pulseSensorTask(void* parameter) {
    for (;;) {
        pulseSensorHandler.update();
        // pulseSensorHandler.updateWithFirebase(firebaseAsyncHandler); // Pass FirebaseAsyncHandler reference
        vTaskDelay(20 / portTICK_PERIOD_MS); // Match the delay in the original loop
    }
}

// void firebaseTask(void* parameter) {
//     for (;;) {
//         firebaseAsyncHandler.update();
//         vTaskDelay(10 / portTICK_PERIOD_MS); // Adjust delay as needed
//     }
// }

void setup() {
    Serial.begin(115200);

    // Initialize MLX90614 sensor
    mlxHandler.begin();

    // Initialize Pulse Sensor
    pulseSensorHandler.begin();

    // Initialize Firebase Async Handler
    firebaseAsyncHandler.begin();

    // firebaseAsyncHandler.update(); // Call update to initialize Firebase connection

    // Create tasks for Heart Rate Sensor and MLX90614 sensor
    xTaskCreate(mlxTask, "MLX90614 Task", 4096, NULL, 1, NULL);
    xTaskCreate(pulseSensorTask, "Pulse Sensor Task", 4096, NULL, 1, NULL);
    // xTaskCreate(firebaseTask, "Firebase Task", 8192, NULL, 1, NULL);
}

void loop() {
    // Main loop does nothing, tasks handle everything
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Prevent watchdog timer reset
    firebaseAsyncHandler.update(); // Call update to process Firebase tasks
    delay(10);
}