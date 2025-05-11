#ifndef PULSE_SENSOR_HANDLER_H
#define PULSE_SENSOR_HANDLER_H

#include <PulseSensorPlayground.h>

class PulseSensorHandler {
public:
    PulseSensorHandler();
    void begin();
    int update();
    // void updateWithFirebase(FirebaseAsyncHandler &firebaseHandler); // Pass FirebaseAsyncHandler reference

private:
    const int PulseWire = 6;
    int Threshold = 550;
    PulseSensorPlayground pulseSensor;
    bool isSampling = false;
};

#endif // PULSE_SENSOR_HANDLER_H