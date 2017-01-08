// LED bits example
// Auth : Haebi
// Date : 2017-01-08
//
// Vcc - LED - AVR Pin(output LOW, as GND) = PIN OUTPUT 0 = LED ON

#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <util/delay.h>

void testLED();
void dispLED(int);
void delay_ms(int);

// Main Function
int main(void)
{
	// Pin Mode Setting
	// 0 - input
	// 1 - output
	DDRB = 0xFF; // 0b11111111

	int check = 1;
	int delay = 500;

	while(1)	
	{
		PORTB = 0xFF; // set off all LEDs.

		// TEST LED
		if(check)
		{	
			testLED();

			check--;
		}

		dispLED(delay);
	}
}

// TEST LEDs
void testLED()
{
	int num;
	int i;

	i   = 1;
	num = 255;

	PORTB = 0xFF;
	delay_ms(500);

	while(num >= 0)
	{
		num -= i;

		i   *= 2;

		PORTB = num;

		delay_ms(500);
	}

	i = 1;

	PORTB = 0x00;
	delay_ms(500);

	while(num <= 255)
	{
		num += i;

		i *= 2;

		PORTB = num;

		if(num < 255)
			delay_ms(500);
	}
}

// Display LEDbits
void dispLED(int delay)
{
	PORTB = 0xFF;

	int cnt = 255;

	while(cnt >= 0)
	{
		PORTB = cnt; // show binary LED

		delay_ms(delay);

		cnt--;
	}
}

// Miliseconds delay function
void delay_ms(int delay)
{
	int i;

	i = 0;

	while(i < delay)
	{
		_delay_ms(1);

		i++;
	}
}
