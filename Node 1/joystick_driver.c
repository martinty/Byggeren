#include "common.h"
#include "joystick_driver.h"
#include "CAN_driver.h"
#include "ADC_driver.h"

#define JOYSTICKOFFSET 5

volatile joystickPos offsetPosition;
volatile joystickPos lastPosition;

void joystick_setCenterPosition(){
	centerPosition.x = ADC_getData(2);
	centerPosition.y = ADC_getData(1);
	
	offsetPosition.x = centerPosition.x - JOYSTICK_CENTER;
	offsetPosition.y = centerPosition.y - JOYSTICK_CENTER;
}

joystickPos joystick_position(){
	joystickPos currentPosition = lastPosition;
	int x = ADC_getData(2) - offsetPosition.x;
	int y = ADC_getData(1) - offsetPosition.y;
	int dx = x - lastPosition.x;
	int dy = y - lastPosition.y;
	if(abs(dx) > JOYSTICKOFFSET){
		currentPosition.x =  x > 255 ? 255 : ( x < 0) ? 0 : x;
		lastPosition.x = currentPosition.x;
	}
	if(abs(dy) > JOYSTICKOFFSET){
		currentPosition.y =  y > 255 ? 255 : ( y < 0) ? 0 : y;
		lastPosition.y = currentPosition.y;
	}
	return currentPosition;
}
