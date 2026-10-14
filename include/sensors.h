#pragma once
#include <Arduino.h>
#include "AHT20Wrapper.h"
#include "IMUWrapper.h"

extern AHT20Sensor envSensor;
extern ImuSensor imuSensor; 
extern QueueHandle_t envQueue;
extern QueueHandle_t imuQueue;
extern QueueHandle_t potQueue;
extern const uint8_t potPin;

void envSensorTask(void *parameter);
void imuSensorTask(void *parameter);
void potTask(void *parameter);