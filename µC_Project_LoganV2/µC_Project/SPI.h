
#ifndef SPI_H_
#define SPI_H_

void SPI_MasterInit_Only_MOSI(void);
uint8_t SPI_MasterTransmit(uint8_t Data);

// void SPI_SlaveInit(void);
// uint8_t SPI_SlaveTransmit(uint8_t Data);


#endif /* SPI_H_ */