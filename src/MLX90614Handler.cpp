#include "MLX90614Handler.h"
#include <Arduino.h>

MLX90614Handler::MLX90614Handler() : mlx() {}

void MLX90614Handler::begin() {
    Serial.println("Adafruit MLX90614 test");

    if (!mlx.begin()) {
        Serial.println("Error connecting to MLX sensor. Check wiring.");
        while (1);
    }

    Serial.print("Emissivity = ");
    Serial.println(mlx.readEmissivity());
    Serial.println("================================================");
}

void MLX90614Handler::update() {
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = ");
    Serial.print(mlx.readObjectTempC());
    Serial.println("*C");

    Serial.println();
    delay(500); // Delay to prevent spamming
}