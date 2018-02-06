
#ifndef COMMON_H_
#define COMMON_H_

#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define read_bit( reg, bit ) (reg & (1 << bit))

#define ENABLE 1
#define DISABLE 0
#define JOYSTICK_CENTER 127

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>



#endif /* COMMON_H_ */