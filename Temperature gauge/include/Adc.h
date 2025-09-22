#pragma once

namespace Adc
{
    enum Channel
    {
        Adc_0 = 0,
        Adc_1 = 1 << 0,
        Adc_2 = 1 << 1,
        Adc_3 = (1 << 0) | (1 << 1),
        Adc_4 = 1 << 2,
        Adc_5 = (1 << 0) | (1 << 2)
    };
    
    void init(Channel channel);
    unsigned short getAnalogValue();
};