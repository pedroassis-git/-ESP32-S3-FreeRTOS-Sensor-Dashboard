#include "IMUWrapper.h"

void ImuSensor::begin() {
    if (!lsm6ds3trc.begin_I2C()) {
        Serial.println("Failed find IMU sensor");
        while (1) delay(10); 
    }
    Serial.println("Found IMU sensor");
}

ImuData ImuSensor::read() {
    ImuData data;
    sensors_event_t temp;
    lsm6ds3trc.getEvent(&data.accel, &data.gyro, &temp); 
    return data;
}