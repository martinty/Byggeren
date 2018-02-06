#ifndef GAME_H_
#define GAME_H_

typedef enum {
	SPEED = 1, POSITION,					// regulatorControl
	P, PI, PID,								// regulatorType
	NORMAL, INVERS,							// inversController
	BORING, COMMUNIST, NAZI,				// solonoid
	EASY, MODERAT, HARD						// Levels
}settings_parameter;

typedef struct{
	int x;
	int y;
} joystickPos;

typedef struct{
	int left;
	int right;
} sliderPos;

typedef struct{
	int left;
	int right;
} buttonStatus;

void playGame();
int game_IR_detector();

#endif /* GAME_H_ */