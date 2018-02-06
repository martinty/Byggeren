#define F_OSC 16000000
#define F_CPU F_OSC
#define BAUD 9600
#define MYUBRR F_OSC/16UL/BAUD-1

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART_driver.h"
#include "SPI_driver.h"
#include "MCP_driver.h"
#include "CAN_driver.h"
#include "adc_driver.h"
#include "pwm.h"
#include "DAC_driver.h"
#include "motor.h"
#include "control.h"
#include "solenoid.h"
#include "game.h"
#include "timer.h"


int main(void){
	
	USART_Init( MYUBRR );
	CAN_init();
	adc_init();
	solenoid_init();
	motor_init();
	pwm_init(20.0);
	timer_init(50);
	pwm_dutyCycle(1.5);
	
	while(1){
	
		switch ( CAN_hasMessage() ) {
			case GAMESETTINGS:
				playGame();
				break;
		}	
	}
}