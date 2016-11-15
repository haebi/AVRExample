#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <util/delay.h>

// Pin PD6 Function
void PPD6(int time, int interval)
{
	if ((time %  (2 * interval)) == 0)
	{
		// Set PD6 OFF
		//PORTD &= ~(1 << PORTD6);
		clrbit(PORTD, PORTD6);
	}
	else if ((time %  interval) == 0)
	{
		// Set PD6 ON
		//PORTD |= (1 << PORTD6);
		setbit(PORTD, PORTD6);
	}
}

// Pin PD7 Function
void PPD7(int time, int interval)
{
	if ((time %  (2 * interval)) == 0)
	{
		// Set PD7 OFF
		//PORTD &= ~(1 << PORTD7);
		clrbit(PORTD, PORTD7);
	}
	else if ((time %  interval) == 0)
	{
		// Set PD7 ON
		//PORTD |= (1 << PORTD7);
		setbit(PORTD, PORTD7);
	}
}

// Main Function
int main(void)
{
	int time = 0;	// init time count

	DDRD |= (1 << DDD6); // Set output PD6
	DDRD |= (1 << DDD7); // Set output PD7

	while(1)
	{
		PPD6(time, 125); // PD6
		PPD7(time, 500); // PD7

		time++; // time count

		_delay_ms(1); // time interval unit
	}
}
