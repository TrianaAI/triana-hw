#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include "MLX90614Handler.h"
#include "PulseSensorHandler.h"

MLX90614Handler mlxHandler;
PulseSensorHandler pulseSensorHandler;

void setup() {
    Serial.begin(115200);

    // Initialize MLX90614 sensor
    mlxHandler.begin();

    // Initialize Pulse Sensor
    pulseSensorHandler.begin();
}

void loop() {
    if (Serial.available()) {
        // Read the incoming data as a string until a newline character
        String input = Serial.readStringUntil('\n');
        input.trim(); // Remove any extra whitespace or newline characters

        // Serial.print("Received command: ");
        // Serial.println(input);

        // Process the input
        if (input == "start pulse") {
            pulseSensorHandler.update();
        } else if (input == "start mlx") {
            mlxHandler.update();
        } else {
            Serial.println("Unknown command.");
        }
    }
}