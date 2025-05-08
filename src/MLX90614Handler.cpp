#include "MLX90614Handler.h"
#include "FirebaseAsyncHandler.h" // Include the header for FirebaseAsyncHandler
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

// void MLX90614Handler::updateWithFirebase(FirebaseAsyncHandler &firebaseHandler) {
//     static int sampleCount = 0;
//     static float ambientSum = 0;
//     static float objectSum = 0;

//     if (firebaseHandler.getActivationStatus("mlxSensor")) { // Check activation status
//         float ambientTemp = mlx.readAmbientTempC();
//         float objectTemp = mlx.readObjectTempC();

//         ambientSum += ambientTemp;
//         objectSum += objectTemp;
//         sampleCount++;

//         if (sampleCount >= 5) { // Take 5 samples and upload the average
//             float averageAmbient = ambientSum / sampleCount;
//             float averageObject = objectSum / sampleCount;
//             firebaseHandler.uploadMLXData(averageAmbient, averageObject);

//             // Reset counters and deactivate sensor
//             sampleCount = 0;
//             ambientSum = 0;
//             objectSum = 0;
//             firebaseHandler.resetActivationStatus("mlxSensor");
//         }
//     }
// }

// void MLX90614Handler::updateWithFirebase(FirebaseAsyncHandler &firebaseHandler) {
//     static int sampleCount = 0;
//     static float ambientSum = 0.0f;
//     static float objectSum = 0.0f;

//     if (checkingActivation) return;  // Prevent overlapping async calls
//     checkingActivation = true;

//     firebaseHandler.getActivationStatus("mlxSensor", [&, this](bool isActive) {
//         checkingActivation = false;  // Reset flag regardless of result

//         if (!isActive) return;

//         float ambientTemp = mlx.readAmbientTempC();
//         float objectTemp = mlx.readObjectTempC();

//         ambientSum += ambientTemp;
//         objectSum += objectTemp;
//         sampleCount++;

//         if (sampleCount >= 5) {
//             float averageAmbient = ambientSum / sampleCount;
//             float averageObject = objectSum / sampleCount;

//             firebaseHandler.uploadMLXData(averageAmbient, averageObject);

//             // Reset for the next batch
//             sampleCount = 0;
//             ambientSum = 0.0f;
//             objectSum = 0.0f;

//             firebaseHandler.resetActivationStatus("mlxSensor");
//         }
//     });
// }
