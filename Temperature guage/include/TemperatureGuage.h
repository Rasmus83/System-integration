#include <stdint.h>

#include "Adc.h"

class TemperatureGuage
{
private:
    char instruction[20];
    uint8_t instructionSize;
public:
    TemperatureGuage(AdcChannel channel);
    void processInstruction();
    void send(const char* message);
    bool getInstructionEquals(const char* instruction);
    float getTemperature();
};