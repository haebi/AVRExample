#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Main Function
int main(void)
{

	// Ref. ATMega328P datasheet p.77 [14.1 Port Pin Configurations]

	DDRB	= 0b00000001; // Pin 14 of MCU as output (DDRB0 as 1)
	PORTB	= 0b00000000; // output of PIN 14 as OFF (PORTB0 as 0)

	DDRC	= 0b00000000; // Pin 23 of MCU as input (DDRC0 as 0)
	PORTC	= 0b00000001; // Enable internal pullup of pin 23 (PORTC0 as 1)

	while(1)
	{
		//if(PORTC0 == 0)
		if(bit_is_clear(PINC, 0))
		{
			int i = 5;

			while(i-- > 0)
			{
				setbit(PORTB, PORTB0); // ON
				_delay_ms(500);
				clrbit(PORTB, PORTB0); // OFF
				_delay_ms(500);
			}
		}

		PORTB	= 0x00; // all OFF
	}
}
