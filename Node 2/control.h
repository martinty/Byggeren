
#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

typedef struct PID_t {
	float Kp;
	float Ki;
	float Kd;
	
	int refrence;
	int measured;
	
	int lastError;
	float dt;
	
	int integral;
	
	int actuation;
	
	int flag;
} PID_t;

void PID_actuation(PID_t* PID);
void PID_setRefrence(int refrence, PID_t* PID);
void PID_setMeasurement(int measurement, PID_t* PID);
void controller_speed(int x, int KpSpeed);
float joystick_servo(int x);

PID_t motor_PID;

#endif /* MOTOR_CONTROL_H_ */