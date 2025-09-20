#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define BUFFER_SIZE 50
static char txDataBuffer[BUFFER_SIZE] = "";
volatile static size_t txBufferTail = 0;
volatile static size_t txBufferHead = 0;

static char rxDataBuffer[BUFFER_SIZE] = "";
volatile static size_t rxBufferTail = 0;
volatile static size_t rxBufferHead = 0;

void uartInit(unsigned int baudRate)
{
    cli();
    UBRR0 = F_CPU / 16 / baudRate - 1;
    UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    sei();
}

void uartTransmit(char character)
{
    txDataBuffer[txBufferHead++] = character;
    if(txBufferHead == BUFFER_SIZE)
        txBufferHead = 0;
    UCSR0B |= (1 << UDRIE0);
}

void uartTransmit(const char* string)
{
    while(*string)
    {
        txDataBuffer[txBufferHead++] = *string++;
        if(txBufferHead == BUFFER_SIZE)
            txBufferHead = 0;
    }
    UCSR0B |= (1 << UDRIE0);
}

char uartRecieve()
{
    if(rxBufferTail == rxBufferHead)
        return '\0';
    char data = rxDataBuffer[rxBufferTail++];
    if(rxBufferTail >= BUFFER_SIZE)
        rxBufferTail = 0;
    return data;
}

ISR(USART_UDRE_vect)
{
    if(txBufferTail != txBufferHead)
    {
        UDR0 = txDataBuffer[txBufferTail++];
        if(txBufferTail >= BUFFER_SIZE)
            txBufferTail = 0;
    }
    else
        UCSR0B &= ~(1 << UDRIE0);
}

ISR(USART_RX_vect)
{
    rxDataBuffer[rxBufferHead++] = UDR0;
    if(rxBufferHead >= BUFFER_SIZE)
        rxBufferHead = 0;
}