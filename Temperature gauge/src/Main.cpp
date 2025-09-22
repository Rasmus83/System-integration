#include <string.h>

#include "TemperatureGauge.h"
#include "ToString.h"

int main()
{
    TemperatureGauge tg(Adc::Adc_0);
    while(true)
    {
        tg.processInstruction();
        if(tg.getInstructionEquals("TempRequest\n"))
        {
            char temperature[8];
            toString(temperature, tg.getTemperature(), 2);
            tg.send(strcat(temperature, "\n"));
        }
    }
}