#ifndef PULSE_SENSOR_HANDLER_H
#define PULSE_SENSOR_HANDLER_H

#include <PulseSensorPlayground.h>

class PulseSensorHandler {
public:
    PulseSensorHandler();
    void begin();
    void update();

private:
    const int PulseWire = 6;
    int Threshold = 550;
    PulseSensorPlayground pulseSensor;
};

#endif // PULSE_SENSOR_HANDLER_H