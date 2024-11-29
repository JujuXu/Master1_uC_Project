#include "MCP4151.h"


int main(void)
{
	// Initialiser le MCP4151
	MCP4151_Init();


	while (1)
	{
		// Régler la position du wiper pour contrôler la résistance
		
		MCP4151_SetWiper(128);
		
	}

	return 0;
}
