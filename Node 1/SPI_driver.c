#include "common.h"
#include "SPI_driver.h"
#include "USART_driver.h"

void SPI_init(void){
	DDRB    |=  (1<<DDB7)   // Slave Clock Input as output
			|   (1<<DDB5)   // Master Output/Slave Input as output
			|   (1<<DDB4);  // Slave Select as output
	PORTB	|=  (1 << PB4);

	//SPI Control Register
	SPCR    |=  (1<<SPE)    // SPI Enable
			|   (1<<SPR0)   // SCK frequency to F_OSC/16
			|   (1<<MSTR);  // Set SPI to master mode
}

void SPI_transmit(uint8_t c){
	SPDR = c;

	// Busy-wait until transmission complete (poll interrupt flag)
	while(!(SPSR & (1<<SPIF))){}
}

uint8_t SPI_receive(void){
	SPI_transmit(0xAA);    // Send dummy data to receive

	// Busy-wait until reception complete (poll interrupt flag)
	while(!(SPSR & (1<<SPIF))){}

	// Reading SPDR also clears the interrupt flag (SPIF)
	return SPDR;
}

void SPI_chipselect(uint8_t enable){
	if (enable == 1){
		PORTB &= ~(1 << PINB4);
	}
	else{
		PORTB |= (1 << PINB4);
	}
}

