#include "common.h"
#include "slider_driver.h"
#include "ADC_driver.h"

#define SLIDEROFFSET 3

volatile int lastLeft = 0;
volatile int lastRight = 0;

int slider_position(SIDE_T side){
	int current = ADC_getData(side);
	if(side == LEFT){
		int dpos = current - lastLeft;
		if(abs(dpos) > SLIDEROFFSET){
			lastLeft = current;
			return current;
		}
		return lastLeft;
	}else if(side == RIGHT){
		int dpos = current - lastRight;
		if(abs(dpos) > SLIDEROFFSET){
			lastRight = current;
			return current;
		}
		return lastRight;
	}
	return -1;
}

int slider_button(SIDE_T side){
	if(side == LEFT){
		DDRB &= ~(1 << PB1);
		return read_bit(PINB, PB1)/2;
	}else if(side == RIGHT){
		DDRB &= ~(1 << PB0);
		return read_bit(PINB, PB0);
	}
	return -1;
}