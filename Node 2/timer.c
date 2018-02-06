#define F_OSC 16000000
#define F_CPU F_OSC

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "control.h"

void timer_init(int ms){
	TCCR1B  = (1 << WGM12); // CTC, resets @ compare
	OCR1A   = F_CPU / 1024 * ms / 1000; //Number for ticks before interrupt
	TIMSK1  = (1 << OCIE1A); // Output compare match timer 1 reg A

	sei();

	TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to clk/1024
}

ISR(TIMER1_COMPA_vect)
{
	PID_actuation(&motor_PID);
}