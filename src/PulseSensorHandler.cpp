#include "PulseSensorHandler.h"
#include <Arduino.h>

PulseSensorHandler::PulseSensorHandler() : pulseSensor() {}

void PulseSensorHandler::begin() {
    Serial.begin(115200);

    pulseSensor.analogInput(PulseWire);
    pulseSensor.setThreshold(Threshold);

    if (pulseSensor.begin()) {
        Serial.println("We created a pulseSensor Object !");
    }
}

// void PulseSensorHandler::update() {
//     static int sampleCount = 0;
//     static int bpmSum = 0;

//     if (pulseSensor.sawStartOfBeat()) {
//         int myBPM = pulseSensor.getBeatsPerMinute();
//         bpmSum += myBPM;
//         sampleCount++;

//         if (sampleCount >= 3) { // Take 3 samples and calculate the average
//             int averageBPM = bpmSum / sampleCount;
//             // Serial.println("♥  A HeartBeat Happened ! ");
//             // Serial.print("Average BPM: ");
//             Serial.println(averageBPM);

//             // Reset counters for the next batch
//             sampleCount = 0;
//             bpmSum = 0;
//         }
//     }
//     delay(20);
// }

void PulseSensorHandler::update() {
    int myBPM = 0;
    do
    {
        if (pulseSensor.sawStartOfBeat()) {
            myBPM = pulseSensor.getBeatsPerMinute();
            // Serial.print("♥  A HeartBeat Happened ! ");
            // Serial.print("BPM: ");
            Serial.println(myBPM);
        }
        delay(20); // Adjust delay as needed
    } while (myBPM == 0);
    
}

// void PulseSensorHandler::updateWithFirebase(FirebaseAsyncHandler &firebaseHandler) {
//     static int sampleCount = 0;
//     static int bpmSum = 0;

//     if (firebaseHandler.getActivationStatus("pulseSensor")) { // Check activation status
//         if (pulseSensor.sawStartOfBeat()) {
//             int bpm = pulseSensor.getBeatsPerMinute();
//             bpmSum += bpm;
//             sampleCount++;

//             if (sampleCount >= 3) { // Take 3 samples and upload the average
//                 int averageBPM = bpmSum / sampleCount;
//                 firebaseHandler.uploadPulseSensorData(averageBPM);

//                 // Reset counters and deactivate sensor
//                 sampleCount = 0;
//                 bpmSum = 0;
//                 firebaseHandler.resetActivationStatus("pulseSensor");
//             }
//         }
//     }
// }

// void PulseSensorHandler::updateWithFirebase(FirebaseAsyncHandler &firebaseHandler) {
//     static int sampleCount = 0;
//     static int bpmSum = 0;

//     if (checkingActivation) return;  // Prevent overlapping async calls
//     checkingActivation = true;

//     firebaseHandler.getActivationStatus("pulseSensor", [&, this](bool isActive) {
//         checkingActivation = false;

//         if (!isActive) return;

//         if (pulseSensor.sawStartOfBeat()) {
//             int bpm = pulseSensor.getBeatsPerMinute();
//             bpmSum += bpm;
//             sampleCount++;

//             if (sampleCount >= 3) {
//                 int averageBPM = bpmSum / sampleCount;
//                 firebaseHandler.uploadPulseSensorData(averageBPM);

//                 // Reset for the next batch
//                 sampleCount = 0;
//                 bpmSum = 0;

//                 firebaseHandler.resetActivationStatus("pulseSensor");
//             }
//         }
//     });
// }
