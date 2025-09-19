#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <util/delay.h>
#include <avr/io.h>

#include "Adc.h"
#include "Uart.h"
#include "ToString.h"

const float beta = 3950;

int main()
{
    adcInit(AdcChannel::Adc_0);
    uartInit(9600);
    while(true)
    {
        unsigned short adcValue = adcGetValue();
        float temp = 1 / (log(1 / (1023. / adcValue - 1)) / beta + 1.0 / 298.15) - 273.15;
        char tempString[20] = "";
        toString(tempString, temp, 3);
        uartTransmit(strcat(tempString, "\r\n"));
    }
}