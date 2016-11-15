#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <avr/interrupt.h>

int count = 0;

// Main Function
int main(void)
{
	OCR1A = 0x3D08;

	setbit(TCCR1B, WGM12);
	setbit(TIMSK1, OCIE1A);
	setbit(TCCR1B, CS12);
	setbit(TCCR1B, CS10);

	sei();

	DDRD |= (1 << DDD6); // Set output PD6
	DDRD |= (1 << DDD7); // Set output PD7

	while (1)
	{

	}
}

ISR (TIMER1_COMPA_vect)
{
	if (count == 0)
	{
		count++;
		clrbit(PORTD, PORTD6);
	}
	else
	{
		setbit(PORTD, PORTD6);
		count = 0;
	}
}
