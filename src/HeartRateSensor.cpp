#include "HeartRateSensor.h"
#include "heartRate.h"
#include <Arduino.h>

HeartRateSensor::HeartRateSensor() {}

void HeartRateSensor::begin() {
    Serial.println("Initializing Heart Rate Sensor...");
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
        Serial.println("MAX30105 was not found. Please check wiring/power.");
        while (1);
    }
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x0A);
    particleSensor.setPulseAmplitudeGreen(0);
    Serial.println("Place your index finger on the sensor with steady pressure.");
}

void HeartRateSensor::update() {
    long irValue = particleSensor.getIR();

    if (irValue > 50000) {
        if (checkForBeat(irValue)) {
            long delta = millis() - lastBeat;
            lastBeat = millis();

            beatsPerMinute = 60 / (delta / 1000.0);

            if (beatsPerMinute < 255 && beatsPerMinute > 20) {
                rates[rateSpot++] = (byte)beatsPerMinute;
                rateSpot %= RATE_SIZE;

                beatAvg = 0;
                for (byte x = 0; x < RATE_SIZE; x++) {
                    beatAvg += rates[x];
                }
                beatAvg /= RATE_SIZE;
            }
            noFingerStart = 0;
        }

        Serial.print("IR=");
        Serial.print(irValue);
        Serial.print(", BPM=");
        Serial.print(beatsPerMinute);
        Serial.print(", Avg BPM=");
        Serial.print(beatAvg);
    } else {
        Serial.print("IR=");
        Serial.print(irValue);
        Serial.print(" No finger?");
        if (noFingerStart == 0) {
            noFingerStart = millis();
        } else if (millis() - noFingerStart > 2000) {
            resetValues();
        }
    }

    Serial.println();
}

void HeartRateSensor::resetValues() {
    beatsPerMinute = 0;
    beatAvg = 0;
}

int HeartRateSensor::getAverageBPM() {
    return beatAvg; // Return the average BPM
}