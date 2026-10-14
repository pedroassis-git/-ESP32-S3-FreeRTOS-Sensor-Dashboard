#include "AHT20Wrapper.h"

void AHT20Sensor::begin() {
    if (!aht.begin(&Wire)) {
      Serial.println("AHT20 sensor not found");
      while (1);
    }
    Serial.println("AHT20 sensor found");
}

AhtData AHT20Sensor::read() {
    AhtData data;
    aht.getEvent(&data.humidity, &data.temperature);
    return data;

}