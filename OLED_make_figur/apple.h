#include <avr/pgmspace.h>

#define FONTSIZE 8

const unsigned char PROGMEM fontFigur[64][8] = {
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b00111111},
	{0b01111111, 0b01111111, 0b11111111, 0b11111110, 0b11110000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00111110, 0b11111110, 0b11111110, 0b11111100, 0b11111100, 0b11111000, 0b11111000, 0b11110000},
	{0b11100000, 0b11000000, 0b10000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b00111111, 0b01111111},
	{0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b01111111, 0b01111111, 0b01111111, 0b00111111, 0b00111111, 0b00111111},
	{0b00111111, 0b00111111, 0b00111111, 0b00111111, 0b01111111, 0b01111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b01111111, 0b01111111, 0b01111111, 0b00111111, 0b00011111, 0b00001110, 0b00000100},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b00111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111000, 0b11100000, 0b10000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b10011111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11110000},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b01111111, 0b00011111, 0b00001111, 0b00000111, 0b00000011},
	{0b00000011, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b11000000, 0b11110000, 0b11111100, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111100, 0b11111000},
	{0b11100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b11000000, 0b11110000},
	{0b11111000, 0b11111100, 0b11111100, 0b11111110, 0b11111110, 0b11111111, 0b11111111, 0b11111111},
	{0b11111111, 0b11111110, 0b11111110, 0b11111110, 0b11111100, 0b11111100, 0b11111100, 0b11111100},
	{0b11111000, 0b11111000, 0b11111000, 0b11111100, 0b11111100, 0b11111100, 0b11111110, 0b11111110},
	{0b11111110, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111110, 0b11111110},
	{0b11111100, 0b11111000, 0b11110000, 0b11100000, 0b11000000, 0b00000000, 0b00000000, 0b00000000},
	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
};
