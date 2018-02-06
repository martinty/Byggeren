#include <avr/io.h>
#include "adc_driver.h"

void adc_init(){
	ADCSRA	|= (1 << ADEN);
	ADCSRA	|= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	// AVCC with external capacitor at AREF pi -  ADC Left Adjust Result 8 bit - Choosing channel 0
	ADMUX	 = (1 << REFS0) | (1 << ADLAR) | 0x00;
}

uint8_t adc_read(){
	ADCSRA	|= (1 << ADSC);
	while(!(ADCSRA & 0x10));
	return ADCH;
}