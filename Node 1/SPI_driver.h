#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

void SPI_init(void);
void SPI_transmit(uint8_t cData);
uint8_t SPI_receive(void);
void SPI_chipselect(uint8_t enable);

#endif /* SPI_DRIVER_H_ */