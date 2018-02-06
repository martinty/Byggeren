#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP_driver.h"

uint8_t rxFlag			= 1;
static int canFlag		= 0;

CAN_message canBuffer;

uint8_t CAN_init()
{
	MCP2515_init();
	
	// Set to loopback mode
	MCP2515_bitModify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

	// Activate interrupt Buffer 1 and ERROR
	MCP2515_bitModify(MCP_CANINTE, 0x21, MCP_RX0IF | MCP_ERRIE);
	
	
	uint8_t val = MCP2515_read(MCP_CANSTAT);
	if((val & MODE_MASK) != MODE_NORMAL) {
		printf("MCP2515 is NOT in normal mode after reset!\n");
		return 1;
	}
	
	/// her må vi legge inn interrup tog
	DDRD    &=	~(1 << DDD2);
	EICRA	|=	(1 << ISC21);	// interrupt on falling edge
	EIMSK   |=  (1<<INT2);		// Enable interrupt on INT1
	
	sei();
	return 0;
}

int CAN_transmitComplete(){
	volatile uint8_t txCtrl = MCP2515_read(MCP_TXB0CTRL);
	if(txCtrl & 0x08){
		return 0;
	}else{
		return 1;
	}
}

void CAN_transmit(CAN_message* message){
	if(CAN_transmitComplete()){
		MCP2515_write(MCP_TXB0SIDL, message->ID << 5);	// Sets first 3 bits in ID to register SIDL
		MCP2515_write(MCP_TXB0SIDH, message->ID >> 3);	// Sets last  5 bits in ID to register SIDHL
		MCP2515_write(MCP_TXB0DLC,	message->lenght);	// Sets lenght of message to register TXB0DLC
		for(uint8_t i = 0; i < message->lenght; i++){
			MCP2515_write(MCP_TXB0D0 + i,message->data[i]);
		}
		// TX0 to send
		MCP2515_requestToSend(MCP_RTS_TX0);
		_delay_ms(1);
		if(!CAN_transmitComplete()){
			printf("Transmit not completed");
		}
	}else{
		printf("Transmit buffer is full");
	}
	_delay_ms(10);
}

void CAN_error(){
	uint8_t error = MCP2515_read(MCP_EFLG);
	if(error & RXWAR){ 
		printf("CAN error: Receive Buffer 0 Overflow Flag bit - RXWAR \n");
	}else if( error & TXWAR){
		printf("CAN error: Receive Buffer 0 Overflow Flag bit - TXWAR \n");
	}
	
}

CAN_message CAN_receive(){
	CAN_message messange;
	if(rxFlag){
		messange.ID		= (MCP2515_read(MCP_RXB0SIDL) >> 5) | (MCP2515_read(MCP_RXB0SIDH) << 3);
		messange.lenght =  0x0F & MCP2515_read(0x65);
		for(uint8_t i = 0; i < messange.lenght; i++){
			messange.data[i] = MCP2515_read(MCP_RXB0D0 + i);
		}
		rxFlag = 0;
	}else{
		messange.ID = -1;
	}
	return messange;
}

void CAN_intVector(){
	uint8_t interrupt = MCP2515_read(MCP_CANINTF);
	if(interrupt & MCP_ERRIE){
		CAN_error();
		MCP2515_bitModify(MCP_CANINTF, 0x20, 0x00);
	}else if(interrupt & MCP_RX0IF){
		rxFlag = 1;
		MCP2515_bitModify(MCP_CANINTF, 0x01, 0x00);
	}
}


void CAN_handler(){
	if(canFlag == 0){
		canBuffer.ID		= (MCP2515_read(MCP_RXB0SIDL) >> 5) | (MCP2515_read(MCP_RXB0SIDH) << 3);
		canBuffer.lenght =  0x0F & MCP2515_read(0x65);
		for(uint8_t i = 0; i < canBuffer.lenght; i++){
			canBuffer.data[i] = MCP2515_read(MCP_RXB0D0 + i);
		}
		canFlag = canBuffer.ID;
		rxFlag	= 0;
	}
}

CAN_message CAN_getMessage(){
	canFlag = 0;
	return canBuffer;
}

int CAN_hasMessage(){
	if(canFlag == 0){
		return 0;
	}
	int temp	= canFlag;
	canFlag		= 0;
	return temp;
}
int i = 0;
ISR(INT2_vect){
	CAN_intVector();
	CAN_handler();
}