#pragma once

#include <stdint.h>

#include "Adc.h"

class TemperatureGauge
{
private:
    char instruction[20];
    uint8_t instructionSize;
public:
    TemperatureGauge(Adc::Channel channel);
    void processInstruction();
    void send(const char* message);
    bool getInstructionEquals(const char* instruction);
    float getTemperature();
};