#include <avr/io.h>
#include "SPI_driver.h"

void SPI_init(void){
    DDRB    |=  (1<<DDB1)   // Slave Clock Input as output
			|   (1<<DDB2)   // Master Output/Slave Input as output
			|   (1<<DDB0)  // Slave Select as output
			|   (1<<DDB7);  // Chip Select as output
    DDRB &= ~(1<<DDB3); // Master Input/Slave Output as input

	//SPI Control Register
    SPCR    |=  (1<<SPE)    // SPI Enable
			|   (1<<SPR0)   // SCK frequency to F_OSC/16
			|	(1<<MSTR); // Set SPI to master mode
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
		PORTB &= ~(1<<PB7);
	}
	else{
		PORTB |= (1<<PB7);
	}
}

