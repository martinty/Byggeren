#ifndef MOTOR_H_
#define MOTOR_H_
#include <stdint.h>

typedef enum direction {RIGHT, LEFT} direction;

void motor_init();
void motor_calibrate();
void motor_stop();
void motor_setDir(direction dir);
void motor_speed(int speed);
int16_t motor_readEncoder();

#endif /* MOTOR_H_ */