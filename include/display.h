#pragma once
#include <Arduino.h>
#include "lcdScreenWrapper.h"
#include "AHT20Wrapper.h"
#include "IMUWrapper.h"

extern LcdDisplay lcdDisplay;
extern const uint8_t ledPin;
extern QueueHandle_t envQueue;
extern QueueHandle_t imuQueue;
extern QueueHandle_t potQueue;

void lcdDisplayTask(void *parameter);
void ledDisplayTask(void *parameter); 