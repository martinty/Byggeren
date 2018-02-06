#define F_OSC 16000000
#define F_CPU F_OSC

#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "game.h"
#include "CAN_driver.h"
#include "control.h"
#include "motor.h"
#include "solenoid.h"
#include "pwm.h"
#include "adc_driver.h"

#define IRMEAN			150
#define SOLONOIDSPEED	300

int buttonFlagLeft	= 0;
int solenoidFlag	= 0;
int KpSpeed = 0;
int burstCount = 0;

void playGame(){
	
	CAN_message gameSettings = CAN_getMessage();
	
	int controllerRef	= (gameSettings.data[1] == POSITION) ? 1 : 0;
	
	if(controllerRef){
		motor_calibrate();
		motor_PID.Kp = gameSettings.data[5]/1000.0;
		motor_PID.Ki = gameSettings.data[6]/1000.0;
		motor_PID.Kd = gameSettings.data[7]/1000.0;
		motor_PID.dt = 1;
		motor_PID.integral = 0;
	}
	else if(!controllerRef){
		KpSpeed = gameSettings.data[5];
	}
	
	int invert			= (gameSettings.data[3] == INVERS) ? 1 : 0;
	int solenoidMode	= (gameSettings.data[4] == BORING) ? BORING : (gameSettings.data[4] == COMMUNIST) ? COMMUNIST : (gameSettings.data[4] == NAZI) ? NAZI : -1;
	
	
	CAN_message gameSettingsRecived = {
		.ID = GAMESETTINGS,
	};

	while(!(CAN_hasMessage() == CONTROLLERS)){
		CAN_transmit(&gameSettingsRecived);
	}
	
	
	while(!game_IR_detector()){

		CAN_message playerControls = CAN_getMessage();
		
		if(playerControls.ID == CONTROLLERS){
			joystickPos joystick = {
				.x = (invert) ? 255 - playerControls.data[0] : playerControls.data[0],
				.y = (invert) ? 255 - playerControls.data[1] : playerControls.data[1]
			};
			sliderPos slider = {
				.left = (invert) ? 255 - playerControls.data[2] : playerControls.data[2],
				.right =(invert) ? 255 - playerControls.data[0] : playerControls.data[2]
			};
		
			buttonStatus button = {
				.left = playerControls.data[4],
				.right = playerControls.data[5]
			};
			
			
			if (solenoidMode == BORING){
				if(button.left && !buttonFlagLeft && !solenoidFlag){
					solenoid();
					buttonFlagLeft = 1;
					solenoidFlag	= 1;
				}else if(!button.left){
					buttonFlagLeft = 0;
				}
				if(solenoidFlag > 0 ){
					solenoidFlag++;
					if(solenoidFlag == SOLONOIDSPEED){
						solenoid();
					}else if(solenoidFlag == 2*SOLONOIDSPEED){
						solenoidFlag = 0;
					}
				}
			}
			
			else if (solenoidMode == COMMUNIST){
				if(button.left && !buttonFlagLeft && !solenoidFlag){
					solenoid();
					buttonFlagLeft = 1;
					solenoidFlag	= 1;
				}else if(!button.left){
					buttonFlagLeft = 0;
				}
				if(solenoidFlag > 0){
					solenoidFlag++;
					if(solenoidFlag == SOLONOIDSPEED){
						burstCount++;
						solenoidFlag = 1;
						solenoid();
					}else if(burstCount > 6){
						solenoidFlag = 0;
						burstCount = 0;
					}
				}
			}
			
			else if (solenoidMode == NAZI){
				solenoidFlag++;
				if(solenoidFlag == SOLONOIDSPEED){
					solenoid();
				}else if(solenoidFlag == 2*SOLONOIDSPEED){
					solenoid();
					solenoidFlag = 0;
				}				
			}
		
 			pwm_dutyCycle(joystick_servo(slider.left));
			if(controllerRef){
 				PID_setRefrence((255-joystick.x)*34, &motor_PID);
				PID_setMeasurement(motor_readEncoder(), &motor_PID);
			}
			else if(!controllerRef){
				controller_speed(joystick.x, KpSpeed);
			}
			if(motor_PID.flag == 1){
				motor_speed(motor_PID.actuation);
				motor_PID.flag = 0;
			}
		}
	}
	motor_stop();
	
	CAN_message gameStatus = {
		.ID			= IR,
	};
	CAN_transmit(&gameStatus);
}

volatile int adc_val = 0;
volatile int adc_samples = 0;

int game_IR_detector(){
	adc_val += adc_read();
	adc_samples++;
	
	if(adc_samples >= 5){
		int adc_mean = adc_val / adc_samples;
		if(adc_mean < IRMEAN){
			adc_val = 0;
			adc_samples = 0;
			return 1;
		}
		adc_val = 0;
		adc_samples = 0;
		return 0;
	}
	return 0;
}