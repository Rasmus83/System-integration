#include <avr/io.h>
#include <avr/interrupt.h>

volatile static unsigned short adcValue = 0;

namespace Adc
{
    enum Channel
    {
        Adc_0 = 0,
        Adc_1 = 1 << MUX0,
        Adc_2 = 1 << MUX1,
        Adc_3 = (1 << MUX0) | (1 << MUX1),
        Adc_4 = 1 << MUX2,
        Adc_5 = (1 << MUX0) | (1 << MUX2)
    };
    
    ISR(ADC_vect)
    {
        adcValue = ADC;
    }
    
    void init(Channel channel)
    {
        sei();
        ADMUX = (1 << REFS0) | (int)channel;
        ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE)  | (1 << ADIE) | (1 << ADPS2) | 
        (1 << ADPS1) | (1 << ADPS0);
        ADCSRB = 0;
    }
    
    unsigned short getAnalogValue()
    {
        return adcValue;
    }
};