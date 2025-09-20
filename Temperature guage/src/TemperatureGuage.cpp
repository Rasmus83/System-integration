#include <string.h>
#include <math.h>

#include "TemperatureGuage.h"
#include "Uart.h"

#define BETA 3950

TemperatureGuage::TemperatureGuage(AdcChannel channel)
    : instruction(""), instructionSize(0)
{
    adcInit(channel);
    uartInit(9600);
}

void TemperatureGuage::processInstruction()
{
    char character = uartRecieve();
    if(character)
    {
        instruction[instructionSize++] = character;
        instruction[instructionSize] = '\0';
        if(instruction[instructionSize - 1] == '\n')
            instructionSize = 0;
    }
}

void TemperatureGuage::send(const char* message)
{
    uartTransmit(message);
}

bool TemperatureGuage::getInstructionEquals(const char* instruction)
{
    bool isEqual = !strcmp(this->instruction, instruction);
    if(isEqual)
        this->instruction[0] = '\0';
    return isEqual;
}

float TemperatureGuage::getTemperature()
{
    return 1 / (log(1 / (1023. / adcGetValue() - 1)) / BETA + 1.0 / 298.15) - 273.15;
}