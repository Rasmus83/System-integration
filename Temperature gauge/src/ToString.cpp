#include <stdlib.h>
#include <stdint.h>

void toString(char* string, size_t value)
{
    if (value == 0)
    {
        string[0] = '0';
        string[1] = '\0';
    }
    else
    {
        char temp[50] = "";
        size_t i = 0;
        while(value > 0)
        {
            temp[i++] = value % 10 + '0';
            value /= 10;
        }
        string[i] = '\0';
        for(size_t j = 0; j < i; j++)
            string[j] = temp[i - 1 - j];
    }
}

void toString(char* string, int value)
{
    if (value == 0)
    {
        string[0] = '0';
        string[1] = '\0';
    }
    else
    {
        char temp[50] = "";
        size_t i = 0;
        bool isNegative = false;
        if (value < 0)
        {
            isNegative = true;
            value = -value;
        }
        while (value > 0)
        {
            temp[i++] = value % 10 + '0';
            value /= 10;
        }
        if (isNegative)
        {
            string[i + 1] = '\0';
            string[0] = '-';
            for (size_t j = 0; j < i; j++)
                string[j + 1] = temp[i - 1 - j];
        }
        else
        {
            string[i] = '\0';
            for (size_t j = 0; j < i; j++)
                string[j] = temp[i - 1 - j];
        }
    }
}

void toString(char* string, float value, uint8_t decimals)
{
    if (value == 0)
    {
        string[0] = '0';
        string[1] = '\0';
    }
    else
    {
        char temp[50] = "";
        size_t i = 0;
        bool isNegative = false;
        if (value < 0)
        {
            isNegative = true;
            value = -value;
        }
        int valueInt = (int)value;
        float fractions = value - valueInt;
        while (valueInt > 0)
        {
            temp[i++] = valueInt % 10 + '0';
            valueInt /= 10;
        }
        if (isNegative)
        {
            string[0] = '-';
            for (size_t j = 0; j < i; j++)
                string[j + 1] = temp[i - 1 - j];
        }
        else
        {
            for (size_t j = 0; j < i; j++)
                string[j] = temp[i - 1 - j];
        }
        string[i++] = '.';
        for (uint8_t j = 0; j < decimals; j++)
        {
            fractions *= 10;
            int digit = (int)fractions;
            string[i++] = digit + '0';
            fractions -= digit;
        }
        string[i] = '\0';
    }
}