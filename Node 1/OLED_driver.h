#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#include <stdint.h>

void OLED_init();
void OLED_home();
void OLED_clearPage(uint8_t page);
void OLED_clear();
void OLED_pos(uint8_t page, uint8_t col);
void OLED_printf( const char* format, ... );
void print_figur();
void print_element_in_figur(int line);

#endif /* OLED_DRIVER_H_ */