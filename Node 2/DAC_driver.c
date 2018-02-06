#define F_OSC 16000000
#define F_CPU F_OSC
#include <avr/io.h>
#include <util/delay.h>
#include "DAC_driver.h"
#include "TWI_Master.h"

#define SLAVEMODE 0x50

void DAC_init(){
	TWI_Master_Initialise();
	DDRD	|= (1 << DDD0);
	DDRD	|= (1 << DDD1);
}

void DAC_write(int value){
	
	uint8_t messageSize = 3;
	uint8_t message[3];
	
	message[0] = SLAVEMODE;
	message[1] = 0x00;	//ADDRESSING DAC0
	message[2] = value; //OUTPUT BYTE
	TWI_Start_Transceiver_With_Data(message,messageSize);
}