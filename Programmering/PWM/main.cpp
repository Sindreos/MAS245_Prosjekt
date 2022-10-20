/*
 * LedPwm.cpp
 *
 * Created: 19.10.2022 10:12:58
 * Author : mikal
 */ 
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL
#include <math.h>

int main(void)
{
	DDRC |= (1 << PC0); // set as output 
	DDRD |= (1 << PD6);                           //set PD7 as PWM output
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
	TCCR0B = _BV(CS00);           //select Fast PWM mode by setting bits 
while(1)
{
for(int duty = 0; duty < 255; duty++)   // 0 to max duty cycle
{
	OCR0A = duty;     //slowly increase the LED brightness
	_delay_ms(10);
}

for(int duty = 255; duty > 0; duty--)   // max to 0 duty cycle
{
	OCR0A = duty;     //slowly decrease the LED brightness
	_delay_ms(10);
}
}
}