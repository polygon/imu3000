#include <avr/io.h>
#include <avr/interrupt.h>

#include "main.h"
#include "usart.h"

#define UART_RXBUFSIZE 25

volatile static uint8_t rxbuf0[UART_RXBUFSIZE];
volatile static uint8_t *volatile rxhead0, *volatile rxtail0;

volatile uint8_t xon = 0;

ISR (USART_RX_vect)
{
    int diff;
    uint8_t c;
    c=UDR0;
    diff = rxhead0 - rxtail0;
    if (diff < 0) diff += UART_RXBUFSIZE;
    if (diff < UART_RXBUFSIZE -1)
    {
        *rxhead0 = c;
        ++rxhead0;
        if (rxhead0 == (rxbuf0 + UART_RXBUFSIZE)) rxhead0 = rxbuf0;

	}

}


void USART0_Init (void)
{
	// 38400 baud
	UBRR0H = 0;
	UBRR0L = 51;
	UCSR0A |= (1 << U2X0);	// enable double speed operation

	// flush receive buffer
	while ( UCSR0A & (1 << RXC0) ) UDR0;

	// set 8N1
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0B &= ~(1 << UCSZ02);



	UCSR0B |= (1 << RXEN0);
	UCSR0B |= (1 << TXEN0);

	UCSR0B |= (1 << RXCIE0);

	rxhead0 = rxtail0 = rxbuf0;
}



void USART0_putc (char c)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}


uint8_t USART0_Getc_nb(uint8_t *c)
{
    if (rxhead0==rxtail0) return 0;
    *c = *rxtail0;
    if (++rxtail0 == (rxbuf0 + UART_RXBUFSIZE)) rxtail0 = rxbuf0;

    return 1;
}

void USART0_puts (char *s)
{
    while (*s)
    {
        USART0_putc (*s);
        s++;
    }
}
