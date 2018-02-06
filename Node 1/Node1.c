#include "common.h"
#include "USART_driver.h"
#include "SRAM.h"
#include "ADC_driver.h"
#include "OLED_driver.h"
#include "MCP2515_driver.h"
#include "SPI_driver.h"
#include "menu.h"
#include "CAN_driver.h"
#include "joystick_driver.h"
#include "timer.h"
#include "slider_driver.h"
#include "game.h"


// SET MENU
struct menu m_NULL;
MENU_ITEM(m_Main,						"Main",				m_NULL,						m_NULL,						m_NULL,			m_Game,		NULL,										NULL);
// 			varName						title				previous					next						parrent			childe		function									functionData	
MENU_ITEM(m_Game,						"Game",				m_NULL,						m_Settings,					m_Main,			m_NULL,		playGame,									NULL);
MENU_ITEM(m_Settings,					"Settings",			m_Game,						m_NULL,						m_Main,			m_S_regulatorRefrence,		NULL,										NULL);

// 			varName						title				previous					next						parrent			childe		function									functionData	
MENU_ITEM(m_S_regulatorRefrence,		"Refrence",			m_NULL,						m_S_regulatorType,			m_Settings,		m_NULL,		game_controllSetting_regulatorRefrence,		&GameSettings.regulatorRefrence);
MENU_ITEM(m_S_regulatorType,			"Reg. type",		m_S_regulatorRefrence,		m_S_inversControllers,		m_Settings,		m_NULL,		game_controllSetting_regulatorType,			&GameSettings.regulatorType);
MENU_ITEM(m_S_inversControllers,		"Invers",			m_S_regulatorType,			m_S_solonoid,				m_Settings,		m_NULL,		game_controllSetting_inversControllers,		&GameSettings.inversControllers);
MENU_ITEM(m_S_solonoid,					"Solonoid",			m_S_inversControllers,		m_NULL,						m_Settings,		m_NULL,		game_controllSetting_solonoid,				&GameSettings.solonoid);

int main(void){
	USART_Init ( MYUBRR );
	SRAM_init();
	ADC_init();
	OLED_init();
	CAN_init();
	timer_init();
	joystick_setCenterPosition();
	
	struct menu* currentMenu = &m_Main;
	while(1){
		currentMenu = menu_Main(currentMenu);
	}
	return 0;
}