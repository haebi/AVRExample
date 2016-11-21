#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int count0 = 0;
int tick0  = 0;

int count1 = 0;

int count2 = 0;
int tick2  = 0;

void setTimer0()
{
	// 1sec for 8-bit
	// 1 / 16000000 = 0.0000000625 * 256 (prescale) = 0.000016 (usec)
	// 0.000016 (usec) * 125 (multiplier) = 0.002 * 1000 = 2 (ms)
	// 2 (ms) * 500 (count) = 1 (sec)

	TCNT0   = 0;
	
	// Set CTC compare value with a prescaler of 256
	OCR0A   = 124; // 125 -1 

	// 0 1 0 - Configure timer 0 for CTC mode [p.106]
	clrbit(TCCR0B, WGM02); // 0
	setbit(TCCR0A, WGM01); // 1
	clrbit(TCCR0A, WGM00); // 0

	// 1 0 0 - Start timer at Fcpu/256 [p. 108]
	setbit(TCCR0B, CS02); // 1
	clrbit(TCCR0B, CS01); // 0
	clrbit(TCCR0B, CS00); // 0
	
	// Enable CTC interrupt
	setbit(TIMSK0, OCIE0A);
}

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

	TCNT2   = 0;
	
	// Set CTC compare value with a prescaler of 256 
	OCR2A   = 124; // 125 -1 

	// 0 1 0 - Configure timer 2 for CTC mode [p.155]
	clrbit(TCCR2B, WGM22); // 0
	setbit(TCCR2A, WGM21); // 1
	clrbit(TCCR2A, WGM20); // 0

	// 1 1 0 - Start timer at Fcpu/256 [p.156-157]
	setbit(TCCR2B, CS22); // 1
	setbit(TCCR2B, CS21); // 1
	clrbit(TCCR2B, CS20); // 0

	// Enable CTC interrupt
	TIMSK2 |= (1 << OCIE2A);
}

// Main Function
int main(void)
{
	setTimer0(); //  8 bit timer (TCNT0)
	setTimer1(); // 16 bit timer (TCNT1)
	setTimer2(); //  8 bit timer (TCNT2)

	sei(); // Enable global interrupts

	setbit(DDRD, DDD6); // Set output PD6
	setbit(DDRD, DDD7); // Set output PD7
	setbit(DDRB, DDB0); // Set output PB0

	while (1)
	{

	}
}

// Timer0 interrupt
ISR (TIMER0_COMPA_vect)
{
	tick0++;

//	if (!(tick0 == 500)) // 1 sec
	if (!(tick0 == 125)) // 1/4 sec
		return;

	tick0 = 0;

	if (count0 == 0)
	{
		count0++;
		clrbit(PORTB, PORTB0);
	}
	else
	{
		setbit(PORTB, PORTB0);
		count0 = 0;
	}
}

// Timer1 interrupt
ISR (TIMER1_COMPA_vect)
{
	// already 1 sec

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
ISR (TIMER2_COMPA_vect) 
{
	tick2++;

//	if (!(tick2 == 500)) // 1 sec
	if (!(tick2 == 250)) // 1/2 sec
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
