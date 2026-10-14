#include "display.h"

void lcdDisplayTask(void *parameter) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    lcdDisplay.setupScreen();

    while (true)
    {
        ImuData imuData;
        AhtData ahtData;
        xQueueReceive(imuQueue, &imuData, portMAX_DELAY);
        xQueuePeek(envQueue, &ahtData, 0);

        Serial.print("from display: ");
        Serial.println(imuData.accel.acceleration.x);
        lcdDisplay.setData(ahtData, imuData);
        lcdDisplay.updateScreen();
    }
}

void ledDisplayTask(void *parameter) {
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (true)
    {
        float perc;
        xQueueReceive(potQueue, &perc, portMAX_DELAY);
        uint8_t duty = perc * 255; 

        ledcWrite(ledPin, duty);
        Serial.print("for ledc: ");
        Serial.println(duty);
    } 
}