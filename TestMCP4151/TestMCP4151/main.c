#include "MCP4151.h"


int main(void)
{
	// Initialiser le MCP4151
	MCP4151_Init();


	while (1)
	{
		// R�gler la position du wiper pour contr�ler la r�sistance
		
		MCP4151_SetWiper(128);
		
	}

	return 0;
}
