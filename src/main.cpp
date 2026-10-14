#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sensors.h"
#include "AHT20Wrapper.h"
#include "IMUWrapper.h"
#include "display.h"

// hardware
AHT20Sensor envSensor;
ImuSensor imuSensor;
LcdDisplay lcdDisplay;

// pins
extern const uint8_t ledPin = 17;
extern const uint8_t potPin = A5;
extern const uint8_t dcPin = 11;
extern const uint8_t csPin = 9;
extern const uint8_t rstPin = 10; 

// queue
QueueHandle_t envQueue; 
QueueHandle_t imuQueue;
QueueHandle_t potQueue;

void setup() {
  // init hardware
  Serial.begin(115200);
  while (!Serial) delay(10);
  envSensor.begin();                            // aht20 sensor
  imuSensor.begin();                            // imu sensor
  analogReadResolution(12);                     // adc for pot
  analogSetPinAttenuation(potPin, ADC_11db);
  lcdDisplay.begin();                           // lcd display
  ledcAttach(ledPin, 1000, 8);                  // external led

  // init queues
  envQueue = xQueueCreate(1, sizeof(AhtData));
  imuQueue = xQueueCreate(1, sizeof(ImuData));
  potQueue = xQueueCreate(1, sizeof(float));

  // create tasks
  xTaskCreate(envSensorTask, "envTask", 2048, nullptr, 1, nullptr);
  xTaskCreate(imuSensorTask, "imuTask", 2048, nullptr, 1, nullptr);
  xTaskCreate(potTask, "potTask", 2048, nullptr, 2, nullptr);
  xTaskCreate(lcdDisplayTask, "lcdDisplayTask", 2048, nullptr, 2, nullptr);
  xTaskCreate(ledDisplayTask, "ledDisplayTaks", 2048, nullptr, 2, nullptr);
}

void loop() {
  while(1) delay(500);
}
