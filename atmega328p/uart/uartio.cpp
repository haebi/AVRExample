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

unsigned char data, receive;

char snd_data[128];
char cmd_data[128];
unsigned char cmd_idx;

void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	//UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	//UCSR0B = (1<<RXEN0)|(1<<TXEN0|1<<RXCIE0|1<<TXCIE0|1<<UDRIE0); // 1<<UDRIE0 slow problem... why?
	//UCSR0B = (1<<RXEN0)|(1<<TXEN0|1<<RXCIE0|1<<TXCIE0); // unimplemented TX may cause problem.
	UCSR0B = (1<<RXEN0)|(1<<TXEN0|1<<RXCIE0);

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

void blink_led(unsigned char *led)
{
	if (*led)
	{
		bit_set(PORTB, PORTB1); // ON
	}
	else
	{
		bit_clear(PORTB, PORTB1); // OFF
	}

	++*led;
	*led = *led > 1 ? 0 : 1;
}

int main( void )
{
	// set pin output
	DDRB |= (1<<DDB1);

	// initialize UART
	USART_Init(MYUBRR);

	// control led on/off
	unsigned char led = 1;

	// Enable global interrupt
	sei();

	// initialize variables
	cmd_idx = 0;
	memset(cmd_data, 0x00, sizeof(cmd_data));
	memset(snd_data, 0x00, sizeof(cmd_data));

	sprintf(snd_data, "\nStart...");
	sendMessage(snd_data);

	while(1)
	{
		// UART receive->send Blocked
		// ------------------------------
		//char rxc = USART_Receive();
		//USART_Transmit(rxc);
		// ------------------------------

		blink_led(&led);

		_delay_ms(500);
	}
}

// Interrupt UART Receive (avoid blocking)
ISR (USART_RX_vect)
{
	// receive from uart RX
	data = UDR0;

	// send to uart TX
	UDR0 = data;
	while ( !( UCSR0A & (1<<UDRE0) ) ); // wait for send complete

	// memo command
	cmd_data[cmd_idx] = data;
	cmd_idx++;

	// return key process
	if(data == '\r')
	{
		// process command
		if(strncmp(cmd_data, "uname", cmd_idx-1) == 0)
		{
			sprintf(snd_data, "\nATMega328 shell 0.1 Tue June 20 22:07:00 KST 2017");
			sendMessage(snd_data);
		}

		// process new line
		memset(snd_data, 0x00, sizeof(snd_data));
		sprintf(snd_data, "\r\n# ");
		sendMessage(snd_data);

		// clear command
		memset(cmd_data, 0x00, sizeof(cmd_data));
		cmd_idx = 0;
	}
}

