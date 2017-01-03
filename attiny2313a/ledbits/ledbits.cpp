#define F_CPU 16000000UL	// Set CPU Frequency 16 MHz

#define setbit(PORTX, BitX) PORTX |= (1 << BitX)	// set bit to 1
#define clrbit(PORTX, BitX) PORTX &= ~(1 << BitX)	// clear bit

#include <avr/io.h>
#include <util/delay.h>

void testLED();
void dispLED();

// Main Function
int main(void)
{
	// Pin Mode Setting
	// 0 - input
	// 1 - output
	DDRB = 0xFF; // 0b11111111

	int check = 1;

	while(1)	
	{
		// TEST LED
		if(check)
		{	
			check = 0;
			testLED();
		}

		dispLED();


		PORTB = 0x00; // set off all LEDs.
	}
}

void testLED()
{
	PORTB = 0b00000001;
	_delay_ms(500); // time interval unit
	PORTB = 0b00000011;
	_delay_ms(500); // time interval unit
	PORTB = 0b00000111;
	_delay_ms(500); // time interval unit
	PORTB = 0b00001111;
	_delay_ms(500); // time interval unit
	PORTB = 0b00011111;
	_delay_ms(500); // time interval unit
	PORTB = 0b00111111;
	_delay_ms(500); // time interval unit
	PORTB = 0b01111111;
	_delay_ms(500); // time interval unit
	PORTB = 0b11111111;
	_delay_ms(1000); // time interval unit
	PORTB = 0b11111110;
	_delay_ms(500); // time interval unit
	PORTB = 0b11111100;
	_delay_ms(500); // time interval unit
	PORTB = 0b11111000;
	_delay_ms(500); // time interval unit
	PORTB = 0b11110000;
	_delay_ms(500); // time interval unit
	PORTB = 0b11100000;
	_delay_ms(500); // time interval unit
	PORTB = 0b11000000;
	_delay_ms(500); // time interval unit
	PORTB = 0b10000000;
	_delay_ms(500); // time interval unit
	PORTB = 0b00000000;
	_delay_ms(500); // time interval unit
}

void dispLED()
{
	int cnt = 0;

	while(cnt < 256)
	{
		cnt++;

		PORTB = cnt; // show binary LED

		_delay_ms(500); // time interval unit
	}
}
