
#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h"
#include "SPI.h"

void SPI_MasterInit_Only_MOSI(void)
{
	// Set MOSI and SCK output, 
	SET_BIT(DDRB,DDB7); // SCK
	SET_BIT(DDRB,DDB5); // MOSI
	CLR_BIT(DDRB,DDB4); // SS MASTER (sera fixé à 5V)
		
	// Enable SPI, Master, mode 0-0, set clock rate fck/8 
	SPCR |= (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR1)|(1<<SPR0);
	SET_BIT(SPSR, SPI2X);
}

uint8_t SPI_MasterTransmit(uint8_t Data)
{
    SPDR = Data;
    //Wait until transmission complete
    while(!(SPSR & (1<<SPIF) ));
    // Return received data
    return(SPDR);
}