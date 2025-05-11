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

int PulseSensorHandler::update() {
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
    
    return myBPM;
}