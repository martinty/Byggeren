#include "common.h"
#include "OLED_driver.h"
#include "font8x8.h"

#define  DISPLAY_HEIGHT	64
#define  DISPLAY_WIDTH	128
#define  DISPLAY_PAGES	(DISPLAY_HEIGHT/8)

void writeCmd(uint8_t addr);
void writeData(uint8_t addr);
void print_char(char input);

static FILE OLED_stdout = FDEV_SETUP_STREAM(print_char, NULL, _FDEV_SETUP_WRITE);

volatile uint8_t currentPage, currentCol;

void OLED_init(){
	
	MCUCR |= (1 << SRE); //Enable SRAM
	SFIOR |= (1 << XMM2); //Frigjør port PC4 - PC7
		
	writeCmd(0xae); // display off
	writeCmd(0xa1); //segment remap
	writeCmd(0xda); //common pads hardware: alternative
	writeCmd(0x12);
	writeCmd(0xc8); //common output scan direction:com63~com0
	writeCmd(0xa8); //multiplex ration mode:63
	writeCmd(0x3f);
	writeCmd(0xd5); //display divide ratio/osc. freq. mode
	writeCmd(0x80);
	writeCmd(0x81); //contrast control
	writeCmd(0x50);
	writeCmd(0xd9); //set pre-charge period
	writeCmd(0x21);
	writeCmd(0x20); //Set Memory Addressing Mode
	writeCmd(0x02);
	writeCmd(0xdb); //VCOM deselect level mode
	writeCmd(0x30);
	writeCmd(0xad); //master configuration
	writeCmd(0x00);
	writeCmd(0xa4); //out follows RAM content
	writeCmd(0xa6); //set normal display
	writeCmd(0xaf); //display on
	OLED_home();
	

	OLED_clear();
}

void writeCmd(uint8_t addr){
	volatile uint8_t *addr_cmd = 0x1000;
	*addr_cmd = addr;
}

void writeData(uint8_t addr){
	volatile uint8_t *addr_data = 0x1200;
	*addr_data = addr;
}

void setPage(uint8_t page){
	currentPage = page;
	writeCmd(0xb0 + page);
}

void setCol(uint8_t col){
	currentCol = col;
	writeCmd(0x00 + col%(16/FONTSIZE));
	writeCmd(0x10 + col/(16/FONTSIZE));
}

void OLED_pos(uint8_t page, uint8_t col){
	setPage(page);
	setCol(col);
}

void OLED_home(){
	currentPage = 0;
	currentCol = 0;
	
	// Page
	setPage(0);
	
	// COL
	writeCmd(0x21);
	writeCmd(0x0);
	writeCmd(0x7f);
}

void OLED_clearPage(uint8_t page){
	uint8_t tempCol = currentCol;
	setPage(page);
	for(int i = 0; i < DISPLAY_WIDTH; i++){
		writeData(0);
		currentCol++;
	}
	setCol(tempCol);
}

void OLED_clear(){
	OLED_pos(0,0);
	for(int i = 0; i < DISPLAY_PAGES; i++)
		OLED_clearPage(i);
	OLED_pos(0,0);
}

void print_char(char input){
	for (int i = 0; i < FONTSIZE; i++){
		writeData(pgm_read_byte(&font[(int)input- 32][i]));
		currentCol ++;
	}
}

void OLED_printf( const char* format, ... ) {
	va_list args;
	va_start( args, format );
	vfprintf( &OLED_stdout, format, args );
	va_end( args );
}


void print_figur(){
	for (int line = 0; line < 64; line++){
		if (currentCol > 64 - FONTSIZE+1){
			setPage(currentPage+1);
			setCol(0);
			if (currentPage == 8){
				OLED_home();
				break;
			}
		}
		print_element_in_figur(line);
	}
}


void print_element_in_figur(line){
	for (int i = 0; i < FONTSIZE; i++){
		writeData(pgm_read_byte(&fontFigur[line][i]));
		currentCol ++;
	}
}