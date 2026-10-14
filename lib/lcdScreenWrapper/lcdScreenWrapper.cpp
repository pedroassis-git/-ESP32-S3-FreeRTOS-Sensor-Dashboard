#include "lcdScreenWrapper.h"

void LcdDisplay::begin() {
    screen.begin();
}

LcdDisplay::LcdDisplay() : screen(dcPin, csPin, rstPin) {}

void LcdDisplay::setData(AhtData ahtData, ImuData imuData) {
    this->ahtData = ahtData;
    this->imuData = imuData;
}

void LcdDisplay::setupScreen() {
    screen.fillScreen(COLOR_RGB565_BLACK);
    screen.setTextWrap(false);
    screen.setTextSize(1);

    // AHT20 header
    screen.fillRect(0, 0, 128, 12, COLOR_RGB565_PURPLE);
    screen.setTextColor(COLOR_RGB565_WHITE);
    screen.setCursor(2, 2);
    screen.print("AHT20");

    // Static labels
    screen.setTextColor(COLOR_RGB565_CYAN);

    screen.setCursor(2, 16);
    screen.print("T:");

    screen.setCursor(64, 16);
    screen.print("H:");

    // IMU header
    screen.fillRect(0, 30, 128, 12, COLOR_RGB565_PURPLE);
    screen.setTextColor(COLOR_RGB565_WHITE);
    screen.setCursor(2, 32);
    screen.print("IMU");

    // Column headers
    screen.setCursor(2, 48);
    screen.print("ACC");

    screen.setCursor(66, 48);
    screen.print("GYRO");

    // Axis labels
    screen.setCursor(2, 62);
    screen.print("X:");

    screen.setCursor(66, 62);
    screen.print("X:");

    screen.setCursor(2, 76);
    screen.print("Y:");

    screen.setCursor(66, 76);
    screen.print("Y:");

    screen.setCursor(2, 90);
    screen.print("Z:");

    screen.setCursor(66, 90);
    screen.print("Z:");
}

void LcdDisplay::updateScreen() {
    // AHT20 values
    screen.fillRect(14, 15, 48, 10, COLOR_RGB565_BLACK);
    screen.setTextColor(COLOR_RGB565_CYAN);
    screen.setCursor(14, 16);
    screen.print(ahtData.temperature.temperature, 1);
    screen.print("C");

    screen.fillRect(76, 15, 50, 10, COLOR_RGB565_BLACK);
    screen.setCursor(76, 16);
    screen.print(ahtData.humidity.relative_humidity, 1);
    screen.print("%");

    // IMU ACC values
    screen.setTextColor(COLOR_RGB565_WHITE);

    screen.fillRect(14, 61, 48, 10, COLOR_RGB565_BLACK);
    screen.setCursor(14, 62);
    screen.print(imuData.accel.acceleration.x, 1);

    screen.fillRect(14, 75, 48, 10, COLOR_RGB565_BLACK);
    screen.setCursor(14, 76);
    screen.print(imuData.accel.acceleration.y, 1);

    screen.fillRect(14, 89, 48, 10, COLOR_RGB565_BLACK);
    screen.setCursor(14, 90);
    screen.print(imuData.accel.acceleration.z, 1);

    // IMU GYRO values
    screen.fillRect(78, 61, 48, 10, COLOR_RGB565_BLACK);
    screen.setCursor(78, 62);
    screen.print(imuData.gyro.gyro.x, 1);

    screen.fillRect(78, 75, 48, 10, COLOR_RGB565_BLACK);
    screen.setCursor(78, 76);
    screen.print(imuData.gyro.gyro.y, 1);

    screen.fillRect(78, 89, 48, 10, COLOR_RGB565_BLACK);
    screen.setCursor(78, 90);
    screen.print(imuData.gyro.gyro.z, 1);
}