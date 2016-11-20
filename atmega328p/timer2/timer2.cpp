#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <avr/interrupt.h>

int count1 = 0;
int count2 = 0;
int tick2 = 0;

void setTimer1()
{
	// OCR1A =  OCR1AH + OCR1AL = (8 + 8 = 16 bit)
	// Dec 15624 : repeat 0 ~ 15624 (15625 = 0)
	OCR1A = 0x3D08; 

	// Page 171-172
	// Waveform Generation Mode : (TCCR1B:4,  TCCR1B:3, TCCR1A:1, TCCR1A:0)
	// 0 1 0 0 - Set to TOP OCR1A
	setbit(TCCR1B, WGM12); // Configure timer 1 for CTC mode

	// Page 173
	// Clock Select Bit ( CS12 CS11 CS10 )
	// 0 1 0 - clock I/O / 1024 (From prescaler)
	setbit(TCCR1B, CS12);
	setbit(TCCR1B, CS10);

	// Page 135
	// TIMSK1 – Timer/Counter1 Interrupt Mask Register
	setbit(TIMSK1, OCIE1A); // Enable CTC interrupt
}

void setTimer2()
{
	// 1sec for 8-bit
	// 1 / 16000000 = 0.0000000625 * 256 (prescale) = 0.000016 (usec)
	// 0.000016 (usec) * 125 (multiplier) = 0.002 * 1000 = 2 (ms)
	// 2 (ms) * 500 (count) = 1 (sec)

	// 130
	TCNT2   = 0x82; // 256 - 125 (multiplier) = 131 -1 = 130 (0x82)
//	TCNT2   = 0;

	// Dec 250
//	OCR2A   = 0xFA; // Set CTC compare value with a prescaler of 64 
	OCR2A   = 0xFF;

	TCCR2A |= (1 << WGM21); // Configure timer 2 for CTC mode [p.155]

	// 1 1 0 - Start timer at Fcpu/256
	TCCR2B |= (1 << CS22);  // Start timer at Fcpu/64 [p.156-157]
	TCCR2B |= (1 << CS21);
	//TCCR2B |= (1 << CS20);

	TIMSK2 |= (1 << OCIE2A); // Enable CTC interrupt
}

// Main Function
int main(void)
{
	setTimer1();
	setTimer2();

	sei(); // Enable global interrupts

	DDRD |= (1 << DDD6); // Set output PD6
	DDRD |= (1 << DDD7); // Set output PD7

	while (1)
	{

	}
}

// Timer1 interrupt
ISR (TIMER1_COMPA_vect)
{
	if (count1 == 0)
	{
		count1++;
		clrbit(PORTD, PORTD6);
	}
	else
	{
		setbit(PORTD, PORTD6);
		count1 = 0;
	}
}

// Timer2 interrupt
ISR(TIMER2_COMPA_vect) 
{
	tick2++;

	if (!(tick2 == 500))
		return;

	tick2 = 0;

	if (count2 == 0)
	{
		count2++;
		clrbit(PORTD, PORTD7);
	}
	else
	{
		setbit(PORTD, PORTD7);
		count2 = 0;
	}
}
