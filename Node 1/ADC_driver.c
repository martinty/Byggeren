#include "common.h"
#include "ADC_driver.h"

void ADC_init(void){
	MCUCR |= (1 << SRE); //Enable SRAM
	SFIOR |= (1 << XMM2); //Frigjør port PC4 - PC7
	DDRD &= ~(1 << PD2); //Innput
}

int ADC_getData(int channel){
	volatile char *ext_adc = (char *) 0x1400;
	*ext_adc = 3 + channel;
	while(read_bit(PIND, PD2));
	_delay_ms(2);
	return *ext_adc;
}