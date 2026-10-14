#pragma once

#include <Adafruit_AHTX0.h>

struct AhtData {
    sensors_event_t humidity;
    sensors_event_t temperature;
};

class AHT20Sensor {
private:
    Adafruit_AHTX0 aht;

public:
    void begin();
    AhtData read();
};