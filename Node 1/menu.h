#ifndef MENU_H_
#define MENU_H_

typedef enum {
	SPEED = 1, POSITION,					// regulatorControl
	P, PI, PID,								// regulatorType
	NORMAL, INVERS,							// inversController
	BORING, COMMUNIST, NAZI,				// solonoid
	EASY, MODERAT, HARD						// Levels
}settings_parameter;

struct menu {
	char* title;
 	struct menu* previous;
	struct menu* next;
	struct menu* parrent;
	struct menu* child;
	struct menu* (*function)(int* data);	int* functionData;
};

struct menu_options {
	char* title;
	int size;
	char* fields[3];
	settings_parameter values[3]
};

#define MENU_ITEM(varName, title, previous, next, parrent, child, function, functionData) \
struct menu previous, next, parrent, child; \
struct menu varName = { \
	title, \
	&previous, &next, &parrent, &child, \
	function, functionData \
}


void menu_print(struct menu* menu_parrent);
struct menu* menu_select(struct menu* menu_parrent);
struct menu* menu_Main(struct menu* menu);
void menu_editOptions(int* change, struct menu_options *options);

// Return menues
	extern struct menu m_Main;
	extern struct menu m_Settings;

#endif /* MENU_H_ */
