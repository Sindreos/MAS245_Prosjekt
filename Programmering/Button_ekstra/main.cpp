/*
 * GccApplication3.cpp
 *
 * Created: 10/19/2022 4:06:13 PM
 * Author : sindr
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL

int main(void)
{
	DDRC |= (0 << PC5);
	DDRB |= (1 << PB0);
    /* Replace with your application code */
    while (1) 
    {
		PORTC |= (0 << PC5);
		if(PC5 ==1){
		PORTB |= (1 << PB0);
		}
		else {
		PORTB &= ~(1 << PB0);
		}
    }
}

