#include "common.h"
#include "OLED_driver.h"
#include "joystick_driver.h"
#include "menu.h"

struct menu m_NULL;

void menu_print(struct menu* menu_parrent){
	OLED_clear();

	OLED_printf("%s:",menu_parrent->title);
	struct menu* current = menu_parrent->child;
	int i = 1;
	while(current != &m_NULL){
		OLED_pos(i++,2);
		OLED_printf("%s",current->title);
		current = current->next;
	}
}

struct menu* menu_select(struct menu* menu_parrent){
	int currentPage = 1;
	struct menu* selected = &m_NULL;
	struct menu* current = menu_parrent->child;
	int JoyStickCenter = 0;
	while(selected == &m_NULL){
		OLED_pos(currentPage,0);
		OLED_printf(">");
		joystickPos joyStick = joystick_position();
		if(JoyStickCenter){
			if(joyStick.y > 200 && current->previous != &m_NULL){
					current = current->previous;
					OLED_pos(currentPage--,0);
					OLED_printf(" ");
					JoyStickCenter = 0;
				}else if (joyStick.y < 60 && current->next != &m_NULL){
					current = current->next;
					OLED_pos(currentPage++,0);
					OLED_printf(" ");
					JoyStickCenter = 0;
				}else if (joyStick.x > 200 && (current->child != &m_NULL || current->function)){
					selected = current;
				}else if (joyStick.x < 60 && current->parrent != &m_NULL){
					selected = menu_parrent->parrent;
				}
			}else{
				if((abs(JOYSTICK_CENTER - joyStick.y) < 5) && (abs(JOYSTICK_CENTER - joyStick.x) < 5)){
					JoyStickCenter = 1;
			}
		}

	}
	
	return selected;
}

struct menu* menu_Main(struct menu* menu){
	struct menu* selected = menu;
	while(!selected->function){
		menu_print(selected);
		selected = menu_select(selected);
	}
	return (*selected->function)(selected->functionData);
}


void menu_editOptions(int* change, struct menu_options *options){
	OLED_clear();
	OLED_printf("%s", options->title);
	for(int i = 1; i <= options->size; i++){
		OLED_pos(i,2);
		OLED_printf("%s", options->fields[i-1]);
	}
	int JoyStickCenter = 0;
	int currentPage = 1;
	int selected = 0;
	while(!selected){
		OLED_pos(currentPage,0);
		OLED_printf(">");
		joystickPos joyStick = joystick_position();
		if(JoyStickCenter){
			if(joyStick.y > 200 && currentPage > 1){
				OLED_pos(currentPage--,0);
				OLED_printf(" ");
				JoyStickCenter = 0;
				}else if (joyStick.y < 60 && currentPage < options->size){
				OLED_pos(currentPage++,0);
				OLED_printf(" ");
				JoyStickCenter = 0;
				}else if (joyStick.x > 200){
				selected = currentPage;
				}else if (joyStick.x < 60){
				selected = -1;
			}
			}else{
			if((abs(JOYSTICK_CENTER - joyStick.y) < 5) && (abs(JOYSTICK_CENTER - joyStick.x) < 5)){
				JoyStickCenter = 1;
			}
		}
	}
	*change = (selected > 0) ? options->values[--selected] : *change;
}