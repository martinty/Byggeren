#ifndef JOYSTICK_DRIVER_H_
#define JOYSTICK_DRIVER_H_

typedef struct{
	int x;
	int y;
} joystickPos;

void joystick_transmit();
void joystick_setCenterPosition();
joystickPos joystick_position();

volatile joystickPos centerPosition;

#endif /* JOYSTICK_DRIVER_H_ */