
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void PPD6(int time, int interval)
{
	if ((time %  (2 * interval)) == 0)
	{
		PORTD &= ~(1<<PORTD6);
	}
	else if ((time %  interval) == 0)
	{
		PORTD |= (1<<PORTD6);
	}
}

void PPD7(int time, int interval)
{
	if ((time %  (2 * interval)) == 0)
	{
		PORTD &= ~(1<<PORTD7);
	}
	else if ((time %  interval) == 0)
	{
		PORTD |= (1<<PORTD7);
	}
}

int main(void)
{
	int time = 0;

	DDRD |= (1<<DDD6); // PD6 Out
	DDRD |= (1<<DDD7); // PD7 Out
	while(1)
	{
		PPD6(time, 125);
		PPD7(time, 500);

		time++;
		_delay_ms(1);
	}
}
