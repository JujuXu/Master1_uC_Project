#include "TC74.h"
#include "I2C_Master.h"
#include "USART.h"

unsigned char TC74_BUFF[TC74_BUFFER_SIZE];

void TC74_Temp_Read(void)
{
	TC74_BUFF[0] = ((TC74_ADDRESS<<1)|0);
	TC74_BUFF[1] = 0x00;
	TWI_Start_Transceiver_With_Data(TC74_BUFF, 2);
	
	TC74_BUFF[0] = ((TC74_ADDRESS<<1)|1);
	TWI_Start_Transceiver_With_Data(TC74_BUFF, 2);
	
	while (TWI_Transceiver_Busy());
}

signed char TC74_BCDtoChar(signed char RegData)
{
	char string[4];
	
	// En n'accédant pas à Regdata avec la ligne avec itoa(), le programme plante. Pourquoi ?
	
	Usart0_Tx_String("TC74 VALUE: ");
	Usart0_Tx_String(itoa(RegData, string, 10));
	Usart0_Tx('\r');
	
	return RegData;
}