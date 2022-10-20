/*
 * GccApplication2.cpp
 *
 * Created: 10/19/2022 2:23:55 PM
 * Author : sindr
 */ 
#define F_CPU 1000000UL
#include <avr/io.h> //Defines pins, ports, etc.
#include <util/delay.h>

static inline void initADC0(void) {
	ADMUX |= (1 << REFS0); //reference voltage on AVCC
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC clock prescaler /8
	ADCSRA |= (1 << ADEN); //enables the ADC
}

int main(void) {
	uint16_t potentiometerValue;
	uint16_t threshold_level;
	threshold_level= 0b10000000;
	DDRD |= (1 << PD6); //Data Direction Register B: writing a 1 to the bit enables output

	initADC0();

	while (1) {
		ADCSRA |= (1 << ADSC); //start ADC conversion
		while(!bit_is_set(ADCSRA,ADIF));    // Loop until conversion is complete
		ADCSRA |= _BV(ADIF); //wait until ADC conversion is done
		potentiometerValue= ADC; //read ADC value in
		
		if (potentiometerValue > threshold_level) {
			PORTD= 0b00000001; //turn on LED attached to port PB0
		}
		else {
			PORTD= 0b00000000; //turn off LED attached to port PB0
		}
	}
}

