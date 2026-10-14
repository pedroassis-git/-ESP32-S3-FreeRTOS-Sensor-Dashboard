#pragma once
#include <DFRobot_GDL.h>
#include "IMUWrapper.h"
#include "AHT20Wrapper.h"

extern const uint8_t dcPin;
extern const uint8_t csPin;
extern const uint8_t rstPin; 

class LcdDisplay {
    public:
        void begin();
        LcdDisplay();
        void setupScreen();
        void updateScreen();
        void setData(AhtData ahtData, ImuData imuData);
    private:
        DFRobot_ST7735_128x160_HW_SPI screen;
        ImuData imuData;
        AhtData ahtData;
};