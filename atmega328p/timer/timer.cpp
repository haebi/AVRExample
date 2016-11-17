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
	// Dec 15624 (?) // 15624 x 1024 = 15998976
	// Reason for THE CPU CLOCK MUST DIVIDED BY 8 ( 8 means 8 bit ? )
	OCR1A = 0x3D08; 

	// Page 172
	// CTC Mode : Set to TOP OCR1A
	// 0 1 0 0 (TCCR1B:4,  TCCR1B:3, TCCR1A:1, TCCR1A:0)
	setbit(TCCR1B, WGM12);

	setbit(TIMSK1, OCIE1A);

	// Page 173
	// Clock Select Bit ( CS12 CS11 CS10 )
	// TCCR1B CS12, CS10 set to 1 means : clock I/O / 1024 (From prescaler)
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
