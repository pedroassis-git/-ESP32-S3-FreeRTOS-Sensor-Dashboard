# FreeRTOS Sensor and Display Demo

An embedded firmware project for the **Adafruit ESP32-S3 Feather**, built with **PlatformIO**, the **Arduino framework**, and **FreeRTOS**. The goal is predictable sensor sampling and responsive outputs while running multiple sensor, display, and LED tasks concurrently.

## Hardware and interfaces

- **AHT20 (I2C):** reads temperature and relative humidity.
- **LSM6DS3TR-C IMU (I2C):** reads three-axis acceleration and angular velocity.
- **Potentiometer (ADC, A5):** reads a 12-bit analog value and normalizes it to a percentage.
- **ST7735 128×160 LCD (SPI):** displays temperature, humidity, acceleration, and gyroscope readings. Control pins: DC 11, CS 9, and reset 10.
- **External LED (LEDC, GPIO 17):** uses 1 kHz, 8-bit PWM to adjust brightness from the potentiometer reading.

## FreeRTOS design

Five tasks separate data acquisition from output updates:

| Task | Timing | Priority |
| --- | --- | --- |
| AHT20 sampling | Every 500 ms | 1 |
| IMU sampling | Every 100 ms | 1 |
| Potentiometer sampling | Every 50 ms | 2 |
| LCD update | Waits for new IMU data; also reads the latest AHT20 data | 2 |
| LED update | Waits for new potentiometer data | 2 |

Sampling tasks use `vTaskDelayUntil()` to maintain regular periods. Three single-item FreeRTOS queues pass the latest readings between tasks, using `xQueueOverwrite()` so older samples do not accumulate. Output tasks block while waiting for data, leaving CPU time available for other tasks.

This structure aims for deterministic behavior through periodic sampling, task priorities, and queue-based communication. The configured periods are scheduling targets rather than a verified hard real-time guarantee.

## Build and run

The PlatformIO configuration targets `adafruit_feather_esp32s3` and declares the Adafruit AHTX0, Adafruit LSM6DS, and DFRobot GDL libraries.

```sh
pio run
pio run --target upload
pio device monitor
```

Serial diagnostics run at **115200 baud**. Connect the serial monitor after reset: startup waits for a serial connection before initializing hardware and creating tasks.
