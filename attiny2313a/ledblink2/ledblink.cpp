#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <util/delay.h>

// Main Function
int main(void)
{
	// Pin Mode Setting
	// 0 - output
	// 1 - input
	//DDRD = 0b00000000;
	clrbit(DDRD,DDD6);

	// In input mode
	// 0 - OFF
	// 1 - ON
	//PORTD = 0b00000000;

	while(1)
	{
		setbit(PORTD, PORTD6); // set PD6 ON (PORTD = 0b__1_____)
		_delay_ms(1000); // time interval unit

		clrbit(PORTD, PORTD6); // set PD6 OFF (PORTD = 0b__0_____)
		_delay_ms(1000); // time interval unit
	}
}
