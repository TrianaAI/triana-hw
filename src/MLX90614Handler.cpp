#include "MLX90614Handler.h"

MLX90614Handler::MLX90614Handler() : mlx() {}

void MLX90614Handler::begin() {
    if (!mlx.begin()) {
        Serial.println("Error connecting to MLX sensor. Check wiring.");
        while (1);
    }
    Serial.println("MLX90614 initialized");
}

void MLX90614Handler::update(FirebaseAsyncHandler &firebaseHandler) {
    // Update the MLX90614 sensor data
    float ambientTemp = mlx.readAmbientTempC();
    float objectTemp = mlx.readObjectTempC();

    Serial.print("Ambient Temperature: ");
    Serial.print(ambientTemp);
    Serial.print("°C, Object Temperature: ");
    Serial.print(objectTemp);
    Serial.println("°C");

    // Upload the data to Firebase
    firebaseHandler.uploadMLXData(ambientTemp, objectTemp);
}

void MLX90614Handler::updateWithFirebase(FirebaseAsyncHandler &firebaseHandler) {
    static unsigned long lastCheckTime = 0;
    const unsigned long checkInterval = 1000; // Check every 1 second

    // Only check activation periodically
    if (millis() - lastCheckTime >= checkInterval) {
        lastCheckTime = millis();
        
        firebaseHandler.monitorActivation("mlxSensor", [&, this](bool isActive) {
            if (isActive && !isSampling) {
                // Start new sampling session
                isSampling = true;
                sampleCount = 0;
                ambientSum = 0;
                objectSum = 0;
                Serial.println("Activation detected - starting sampling");
            }
        });
    }

    if (isSampling) {
        // Take samples with 200ms interval
        static unsigned long lastSampleTime = 0;
        if (millis() - lastSampleTime >= 200) {
            lastSampleTime = millis();
            
            float ambientTemp = mlx.readAmbientTempC();
            float objectTemp = mlx.readObjectTempC();
            
            ambientSum += ambientTemp;
            objectSum += objectTemp;
            sampleCount++;

            Serial.print("Sample ");
            Serial.print(sampleCount);
            Serial.print(" - Ambient: ");
            Serial.print(ambientTemp);
            Serial.print("°C, Object: ");
            Serial.print(objectTemp);
            Serial.println("°C");

            if (sampleCount >= 5) {
                // Calculate averages
                float avgAmbient = ambientSum / 5;
                float avgObject = objectSum / 5;
                
                // Upload to Firebase
                firebaseHandler.uploadMLXData(avgAmbient, avgObject);
                
                // Reset activation status
                firebaseHandler.resetActivationStatus("mlxSensor");
                
                // Reset sampling state
                isSampling = false;
                Serial.println("Sampling complete. Data uploaded.");
            }
        }
    }
}