#include "sensors.h"

void envSensorTask(void *parameter)
{
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (true)
    {
        AhtData data = envSensor.read();
        Serial.print("hum: ");
        Serial.println(data.humidity.relative_humidity);
        xQueueOverwrite(envQueue, &data); 
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(500));
    }
}

void imuSensorTask(void *parameter) {
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (true) {
       ImuData data = imuSensor.read();
       Serial.print("accel: ");
       Serial.println(data.accel.acceleration.x); 
       xQueueOverwrite(imuQueue, &data);
       vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(100)); 
    }
}

void potTask(void *parameter) {
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (true) {
        int raw = analogRead(potPin);
        float perc = raw / 4095.0;
        Serial.print("pot: ");
        Serial.println(perc);
        xQueueOverwrite(potQueue, &perc);
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(50)); 
    }
}
