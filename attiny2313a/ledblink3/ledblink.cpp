#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <util/delay.h>

// Main Function
int main(void)
{
	// Pin Mode Setting
	// 0 - input
	// 1 - output
	//DDRD = 0b00000000;
	DDRB = 0xFF;

	// In output mode
	// 0 - OFF
	// 1 - ON
	//PORTD = 0b00000000;

	int check = 1;
	int intval = 500;

	volatile int cnt = 0;

	while(1)	
	{
		// TEST LED
		if(check)
		{	
			check = 0;

			PORTB = 0b00000001;
			_delay_ms(intval); // time interval unit
			PORTB = 0b00000010;
			_delay_ms(intval); // time interval unit
			PORTB = 0b00000100;
			_delay_ms(intval); // time interval unit
			PORTB = 0b00001000;
			_delay_ms(intval); // time interval unit
			PORTB = 0b00010000;
			_delay_ms(intval); // time interval unit
			PORTB = 0b00100000;
			_delay_ms(intval); // time interval unit
			PORTB = 0b01000000;
			_delay_ms(intval); // time interval unit
			PORTB = 0b10000000;
			_delay_ms(intval); // time interval unit

		}

		cnt = 0;

		while(cnt < 256)
		{
			cnt++;
			PORTB = (unsigned char)cnt;
			_delay_ms(1000); // time interval unit
		}

	}
}
