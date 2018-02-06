#define F_OSC 16000000
#define F_CPU F_OSC
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "DAC_driver.h"

#define MJ1		PORTH
#define MJ1DIR	PH1
#define MJ1EN	PH4
#define MJ1OE	PH5
#define MJ1SEL	PH3
#define MJ1RST	PH6

void motor_init(){
	DAC_init();
	DDRH	|=	(1 << MJ1DIR) 
			|	(1 << MJ1EN)
			|	(1 << MJ1OE)
			|	(1 << MJ1SEL)
			|	(1 << MJ1RST);
			
	MJ1		|=	(1 << MJ1DIR) 
			|	(1 << MJ1EN);
}

void motor_calibrate(){
	motor_setDir(RIGHT);
	motor_speed(100);
	_delay_ms(2000);
	motor_speed(0);
	_delay_ms(500);
	MJ1		&= ~(1 << MJ1RST);
}

void motor_speed(int speed){
	int output = speed;
	if (speed < 0){
		motor_setDir(LEFT);
		output -= 50;
	}
	else if(speed > 0){
		motor_setDir(RIGHT);
		output += 50;
	}
	DAC_write(abs(output));
}

void motor_stop(){
	motor_speed(0);
}

void motor_setDir(direction dir){
	if(dir == RIGHT){
		MJ1 |= (1 << MJ1DIR);
	}
	else{
		MJ1 &= ~(1 << MJ1DIR);
	}
}

int16_t motor_readEncoder(){
	int16_t val = 0;
	MJ1		|= (1 << MJ1RST);
	MJ1 &= ~(1 << MJ1OE);	// Enable output Encoder
	MJ1 &= ~(1 << MJ1SEL);	// Enable heigh bits
	_delay_us(20);
	val = (PINK << 8);		// GET MSB
	MJ1 |= (1 << MJ1SEL);	// Enable low bits
	_delay_us(20);
	val |= PINK;			// GET LSB
	MJ1 |= (1 << MJ1OE);	// Disable output Encoder
	return val;
}

