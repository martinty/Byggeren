#include "common.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "USART_driver.h"

uint8_t MCP2515_read(uint8_t addr){
	cli();
	SPI_chipselect(1);
	SPI_transmit(MCP_READ);
	SPI_transmit(addr);
	uint8_t data = SPI_receive();
	SPI_chipselect(0);
	sei();
	return data;
}

void MCP2515_write(uint8_t addr, uint8_t data){
	cli();
	SPI_chipselect(1);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(addr);
	SPI_transmit(data);
	SPI_chipselect(0);
	sei();
}

uint8_t MCP2515_init()
{
	uint8_t val;
	
	SPI_init();
	MCP2515_reset();
	
	// Self-test
	val = MCP2515_read(MCP_CANSTAT);
	if((val & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in configuration mode after reset!\n");
		return 1;
	}
	return 0;
}

void MCP2515_requestToSend(uint8_t reg){
	cli();
	SPI_chipselect(1);
	SPI_transmit(MCP_RTS + reg);
	SPI_chipselect(0);
	sei();
}

uint8_t MPC2515_readStatus(){
	cli();
	SPI_chipselect(1);
	
	SPI_transmit(MCP_READ_STATUS);
	uint8_t data = SPI_receive();
	
	SPI_chipselect(0);
	sei();
	return data;
}

void MCP2515_bitModify(uint8_t addr, uint8_t mask, uint8_t data){
	cli();
	SPI_chipselect(1);
	
	SPI_transmit(MCP_BITMOD);
	SPI_transmit(addr);
	SPI_transmit(mask);
	SPI_transmit(data);
	
	SPI_chipselect(0);
	sei();
}

void MCP2515_reset(){
	cli();
	SPI_chipselect(1);
	SPI_transmit(MCP_RESET);
	SPI_chipselect(0);
	sei();
}

