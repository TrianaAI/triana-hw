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

void PulseSensorHandler::update() {
    if (pulseSensor.sawStartOfBeat()) {
        int myBPM = pulseSensor.getBeatsPerMinute();
        Serial.println("♥  A HeartBeat Happened ! ");
        Serial.print("BPM: ");
        Serial.println(myBPM);
    }
    delay(20);
}