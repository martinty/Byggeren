#include "common.h"
#define TIMER_MS 5
#define PRESCALER 1024

static int playerTime;

void timer_init(){
    TCCR1B  |=  (1 << WGM12);					// CTC, resets @ compare
    TCCR1B  |=  (1 << CS12) | (1 << CS10);		// set prescaler to clk/1024
    TIMSK   |=  (1 << OCIE1A);					// Output compare match OCR1A and  TCNT1
    OCR1A	= (F_CPU/1024);	
	sei();
}

void timer_start(){
	playerTime = 0;
}

int timer_stop(){
	return playerTime;
}

int timer_read(){
	return playerTime;
}

ISR(TIMER1_COMPA_vect){
	playerTime++;
}