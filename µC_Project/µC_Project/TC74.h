//	0b1001000		0
//	0b1001001		1
//	0b1001010		2
//	0b1001011		3
//	0b1001100		4
//	0b1001101		5	askip default address
//	0b1001110		6
//	0b1001111		7

#define TC74_ADDRESS		0b1001101
#define TC74_BUFFER_SIZE	3

void TC74_Temp_Read(void);
signed char TC74_BCDtoChar(signed char RegData);