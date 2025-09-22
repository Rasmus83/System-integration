#pragma once

namespace Uart
{
    void init(unsigned int baudRate);
    void transmit(char character);
    void transmit(const char* string);
    char recieve();
}