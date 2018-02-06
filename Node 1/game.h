#ifndef GAME_H_
#define GAME_H_
#include "menu.h"

typedef struct {
	settings_parameter level;
	settings_parameter regulatorRefrence;
	settings_parameter regulatorType;
	settings_parameter inversControllers; 
	settings_parameter solonoid;
	int regulatorKp;
	int regulatorKi;
	int regulatorKd;
	}settings_t;

settings_t GameSettings;

struct menu* playGame(int* data);

struct menu* game_controllSetting_regulatorRefrence(int* data);
struct menu* game_controllSetting_regulatorType(int* data);
struct menu* game_controllSetting_inversControllers(int* data);
struct menu* game_controllSetting_solonoid(int* data);

#endif /* GAME_H_ */