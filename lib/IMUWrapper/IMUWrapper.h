#pragma once

#include <Adafruit_LSM6DS3TRC.h>

struct ImuData {
    sensors_event_t accel;
    sensors_event_t gyro;
};

class ImuSensor {
    private:
        Adafruit_LSM6DS3TRC lsm6ds3trc;
    public:
        void begin();
        ImuData read();
};