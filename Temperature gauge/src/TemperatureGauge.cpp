#include <string.h>
#include <math.h>

#include "TemperatureGauge.h"
#include "Uart.h"

#define BETA 3950

TemperatureGauge::TemperatureGauge(Adc::Channel channel)
    : instruction(""), instructionSize(0)
{
    Adc::init(channel);
    Uart::init(9600);
}

void TemperatureGauge::processInstruction()
{
    char character = Uart::recieve();
    if(character)
    {
        instruction[instructionSize++] = character;
        instruction[instructionSize] = '\0';
        if(instruction[instructionSize - 1] == '\n')
            instructionSize = 0;
    }
}

void TemperatureGauge::send(const char* message)
{
    Uart::transmit(message);
}

bool TemperatureGauge::getInstructionEquals(const char* instruction)
{
    bool isEqual = !strcmp(this->instruction, instruction);
    if(isEqual)
        this->instruction[0] = '\0';
    return isEqual;
}

float TemperatureGauge::getTemperature()
{
    return 1 / (log(1 / (1023. / Adc::getAnalogValue() - 1)) / BETA + 1.0 / 298.15) - 273.15;
}