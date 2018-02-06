#define F_OSC 16000000
#define F_CPU F_OSC

#include <avr/io.h>
#include <util/delay.h>
#include "solenoid.h"

void solenoid_init(){
	DDRB |= (1 << DDB6);
	PINB |= (1 << PB6);
}

void solenoid(){
	PINB |= (1 << PB6);
	_delay_ms(1);
}