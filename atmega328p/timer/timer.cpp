#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <avr/interrupt.h>

int count = 0;

// Main Function
int main(void)
{
	// OCR1A =  OCR1AH + OCR1AL = (8 + 8 = 16 bit)
	// Dec 15624 : repeat 0 ~ 15624 (15625 = 0)
	OCR1A = 0x3D08; 

	// Page 171-172
	// Waveform Generation Mode : (TCCR1B:4,  TCCR1B:3, TCCR1A:1, TCCR1A:0)
	// 0 1 0 0 - Set to TOP OCR1A
	setbit(TCCR1B, WGM12); // Configure timer 1 for CTC mode

	// Page 135
	// TIMSK1 – Timer/Counter1 Interrupt Mask Register
	setbit(TIMSK1, OCIE1A); // Enable CTC interrupt

	// Page 173
	// Clock Select Bit ( CS12 CS11 CS10 )
	// 0 1 0 - clock I/O / 1024 (From prescaler)
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
