#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

unsigned char data, receive;

ISR(USART_RX_vect)
{
	receive = 1;
	data = UDR;
}

ISR(USART_UDRE_vect)
{
	if(receive == 1)
	{
		UDR = '_';
		while((UCSRA&0x20) == 0);

		receive = 0;
	}

	UCSRB = 0x98;
}

int main(void)
{
	//DDRB = 0xFF; // 1 : output
	//PORTB = 0x00;
	
	UCSRA = 0x00;
	UCSRB = 0x98;
	UCSRC = 0x06;
	UBRRH = 0x01;
	UBRRL = 0xA0; // 2400 bps
	
	sei();

	while(1)
	{
		//UCSRB = 0xB8;
		UDR = '_';
		while((UCSRA&0x20) == 0);
		UDR = 'o';
		while((UCSRA&0x20) == 0);
		UDR = 'k';
		while((UCSRA&0x20) == 0);

		_delay_ms(500);
	}

	return 0;
}
