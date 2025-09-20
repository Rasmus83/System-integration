#include "TemperatureGuage.h"
#include "ToString.h"

int main()
{
    TemperatureGuage tg(AdcChannel::Adc_0);
    while(true)
    {
        tg.processInstruction();
        if(tg.getInstructionEquals("Send temperature\n"))
        {
            char temperature[10];
            toString(temperature, tg.getTemperature(), 3);
            tg.send(temperature);
        }
    }
}