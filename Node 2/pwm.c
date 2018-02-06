#define F_OSC 16000000
#define F_CPU F_OSC

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pwm.h"

void pwm_init(double periode_ms){
	// Set PB5 as outout, 11 on shield
	DDRB	|= (1 << DDB5);
	
	// Compere output mode, clear Clear OC1A on Compare Match, set OC1A at BOTTOM
	TCCR1A	|= (1 << COM1A1);
	
	// Fast PWM
	TCCR1A	|= (1 << WGM11);
	
	// Waveform Generation Mode
	TCCR1B	|= (1 << WGM12) | (1 << WGM13);
	
	
	// Time/Conter iterrput, Overflow interrupt enable
	//TIMSK1	|= (1 << TOIE1);
	
	// Starts clock
	TCCR1B	|= (1 << CS10)  | (1 << CS12);
	
	// Set periode
	ICR1	=	(uint32_t)F_CPU/1024/1000 * periode_ms;
	
	
	//sei();
}

void pwm_dutyCycle(float dutyCycle){
	if (dutyCycle <= 0.9){
		OCR1A	= (uint32_t)F_CPU/1024/1000 * 0.9;
	}
	else if (dutyCycle >= 2.1){
		OCR1A	= (uint32_t)F_CPU/1024/1000 * 2,1;
	}
	else{
		OCR1A	= (uint32_t)F_CPU/1024/1000 * dutyCycle;
	}
}