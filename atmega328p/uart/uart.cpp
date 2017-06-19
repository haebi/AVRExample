/* Based on Atmel 328P Reference Source Code
 * */

#define F_CPU 16000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD -1

#define bit_set(x, y) x |= (1 << y);
#define	bit_clear(x, y) x &= ~(1 << y);

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <string.h>
#include <stdio.h>

void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0) ) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
		;
	/* Get and return received data from buffer */
	return UDR0;
}

void sendMessage(char* data)
{
	int i = 0;

	while(data[i] != 0x00)
	{
		USART_Transmit(data[i]);
		i++;
	}
}

int main( void )
{
	DDRB |= (1<<DDB1);

	USART_Init(MYUBRR);

	int count = 0;
	int led = -1;

	while(1)
	{
		bit_set(PORTB, PORTB1); // ON

		_delay_ms(500);

		bit_clear(PORTB, PORTB1); // OFF

		count++;

		_delay_ms(500);

		char str1[32];

		sprintf(str1, "[%d] Hello World ~!!\n", count);

		sendMessage(str1);
		USART_Transmit('\r');

		if (led > 1)
		{
			PORTB = 0b00000000; // OFF
		}
		else
		{
			PORTB = 0b00000001; // ON
		}

		led *= led;
	}
}

