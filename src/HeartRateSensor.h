#ifndef HEART_RATE_SENSOR_H
#define HEART_RATE_SENSOR_H

#include "MAX30105.h"

class HeartRateSensor {
public:
    HeartRateSensor();
    void begin();
    void update();

private:
    MAX30105 particleSensor;
    const byte RATE_SIZE = 4;
    byte rates[4];
    byte rateSpot = 0;
    long lastBeat = 0;
    float beatsPerMinute = 0;
    int beatAvg = 0;
    unsigned long noFingerStart = 0;

    void resetValues();
};

#endif // HEART_RATE_SENSOR_H