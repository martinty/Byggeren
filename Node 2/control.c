#define F_OSC 16000000
#define F_CPU F_OSC

#include <avr/io.h>
#include <avr/interrupt.h>
#include "control.h"
#include "motor.h"

struct PID_controller{
	float Kp;
	float Kd;
	float Ki;
	float referance;
	};


void PID_actuation(PID_t* PID){ 
	float error			= PID->measured - PID->refrence;
	PID->integral		+= error;
	PID->actuation		= error * PID->Kp;
	PID->actuation		+= PID->integral * PID->Ki;
	PID->actuation		+= (error - PID->lastError)/ PID->dt * PID->Kd ;
	PID->lastError		= error;
	PID->flag = 1;
}

void PID_setRefrence(int refrence, PID_t* PID){
	PID->refrence = refrence;
}

void PID_setMeasurement(int measurement, PID_t* PID){
	PID->measured = measurement;
}

void controller_speed(int x, int KpSpeed){
	if(x > 140){
		motor_speed(5 * KpSpeed * (x-140)/115);
	}else if(x < 120){
		motor_speed(-5 * KpSpeed * (120-x)/120);
	}else{
		motor_stop();
	}
}

float joystick_servo(int x){
	float pos = 0.9 + 1.2 * (x)/255;
	return  pos;
}