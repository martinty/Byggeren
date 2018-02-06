#include "common.h"
#include "USART_driver.h"
#include "game.h"
#include "CAN_driver.h"
#include "OLED_driver.h"
#include "joystick_driver.h"
#include "slider_driver.h"
#include "timer.h"
#include "menu.h"


struct menu* playGame(int * data){
	printf("GAME STARTED \n");
	
	struct menu_options level = {
		.title		= "Level",
		.size 		= 3,
		.fields[0]	= "Easy",			.fields[1]	= "Moderat",		.fields[2]	= "Hard",
		.values[0]	= EASY,				.values[1]	= MODERAT,			.values[2]	= HARD,
	};
	settings_parameter currentLevel = -1;
	menu_editOptions(&currentLevel, &level);
	
	
	int Kp = (currentLevel == EASY) ?	15	: (currentLevel == MODERAT) ? 20	: (currentLevel == HARD) ? 30 : 0;
	int Ki = (currentLevel == EASY) ?	1	: (currentLevel == MODERAT) ? 5		: (currentLevel == HARD) ? 10 : 0;
	int Kd = (currentLevel == EASY) ?	1	: (currentLevel == MODERAT) ? 5		: (currentLevel == HARD) ? 10 : 0;
	
	GameSettings.level					= currentLevel;
	GameSettings.regulatorRefrence		= (!GameSettings.regulatorRefrence)	? POSITION	: GameSettings.regulatorRefrence;
	GameSettings.regulatorType			= (!GameSettings.regulatorType)		? PID		: GameSettings.regulatorType;
	GameSettings.inversControllers		= (!GameSettings.inversControllers)	? NORMAL	: GameSettings.inversControllers;
	GameSettings.solonoid				= (!GameSettings.solonoid)			? BORING	: GameSettings.solonoid;
	
	GameSettings.regulatorKp			= Kp;
	GameSettings.regulatorKi			= (GameSettings.regulatorType == PI || GameSettings.regulatorType == PID) ? Ki : 0;
	GameSettings.regulatorKd			= (GameSettings.regulatorType == PID) ? Kd : 0;
	
	CAN_message setGameSettings = {
		.ID = GAMESETTINGS,
		.lenght = 8,
		.data[0] = GameSettings.level, .data[1] = GameSettings.regulatorRefrence, .data[2] = GameSettings.regulatorType, .data[3] = GameSettings.inversControllers, .data[4] = GameSettings.solonoid, .data[5] = GameSettings.regulatorKp, .data[6] = GameSettings.regulatorKi, .data[7] = GameSettings.regulatorKd
	};
	
	OLED_clear();
	OLED_printf("Initializing");
	
	while(!(CAN_hasMessage() == GAMESETTINGS)){
		CAN_transmit(&setGameSettings);
	}
	
	
	OLED_clear();
	OLED_printf(">>> WELCOME <<<");
	OLED_pos(2,0);
	OLED_printf("Start:");
	OLED_pos(3,1);
	OLED_printf("-> Right Button");
		
	while(!slider_button(RIGHT)){}
	CAN_hasMessage(); // Clear IR can buffer
	OLED_clear();
	print_figur();
	OLED_pos(1,9);
	OLED_printf("Score");
	OLED_pos(4,14);
	OLED_printf("$");
		
	timer_start();
	while(!(CAN_hasMessage() == IR)){
		CAN_message playerControls = {
			.ID = CONTROLLERS,
			.lenght = 6,
			.data[0] = joystick_position().x,
			.data[1] = joystick_position().y,
			.data[2] = slider_position(LEFT),
			.data[3] = slider_position(RIGHT),
			.data[4] = slider_button(LEFT),
			.data[5] = slider_button(RIGHT)
		};
		CAN_transmit(&playerControls);
			

		OLED_pos(4,11);
		OLED_printf("%d", timer_read());
		_delay_ms(30);
	}

	int score = timer_stop();
	
	OLED_clear();
	OLED_printf("!! GAME OVER !!");
	OLED_pos(3,0);
	OLED_printf("Score: %d", score);
	
	OLED_pos(6,0);
	OLED_printf("Menu:");
	OLED_pos(7,1);
	OLED_printf("-> Right Button");
	
	
	while(!slider_button(RIGHT)){}
	
	OLED_clear();
	printf("GAME STOPPED \n");
	
	return &m_Main;
}


	struct menu_options regulatorRefrence = {
		.title		= "Controll refrence",
		.size 		= 2,
		.fields[0]	= "Speed",			.fields[1]	= "Position",
		.values[0]	= SPEED,			.values[1]	= POSITION,
	};
	
	struct menu_options regulatorType = {
		.title		= "Regulator type",
		.size 		= 3,
		.fields[0]	= "P",				.fields[1]	= "PI",			.fields[2]	= "PID", 
		.values[0]	= P,				.values[1]	= PI,			.values[2]	= PID,	
	};
	
	struct menu_options inversControllers = {
		.title		= "Invers",
		.size 		= 2,
		.fields[0]	= "Normal",			.fields[1]	= "Invers",
		.values[0]	= NORMAL,			.values[1]	= INVERS,
	};
	
	struct menu_options solonoid = {
		.title		= "Solonoid",
		.size 		= 3,
		.fields[0]	= "Boring",			.fields[1]	= "COMMUNIST",		.fields[2]	= "Nazi", 
		.values[0]	= BORING,			.values[1]	= COMMUNIST,		.values[2]	= NAZI,
	};
	
struct menu* game_controllSetting_regulatorRefrence(int* data){
	menu_editOptions(data, &regulatorRefrence);
	return &m_Settings;
}

struct menu* game_controllSetting_regulatorType(int* data){
	menu_editOptions(data, &regulatorType);
	return &m_Settings;
}

struct menu* game_controllSetting_inversControllers(int* data){
	menu_editOptions(data, &inversControllers);
	return &m_Settings;
}

struct menu* game_controllSetting_solonoid(int* data){
	menu_editOptions(data, &solonoid);
	return &m_Settings;
}