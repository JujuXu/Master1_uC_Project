#include <avr/io.h>
#include "MCP4151.h"
#include "SPI.h"

// Initialiser le MCP4151
void MCP4151_Init(void)
{
	// Configurer PD4 (CS) comme sortie
	DDRD |= (1 << MCP4151_CS_PIN);
	// Initialiser CS à HIGH (désactivé)
	PORTD |= (1 << MCP4151_CS_PIN);

	// Initialiser le SPI
	SPI_MasterInit_Only_MOSI();
}

// Régler la position du wiper
void MCP4151_SetWiper(uint8_t value)
{
	if (value > 255)
	{
		value = 255; // Limiter la valeur à 255 (max)
	}

	// Activer le MCP4151 (CS à LOW)
	PORTD &= ~(1 << MCP4151_CS_PIN);

	// Envoyer la commande pour régler le wiper
	SPI_MasterTransmit(0x00);  // MSB : Commande pour le registre Wiper
	SPI_MasterTransmit(value); // LSB : Position du wiper

	// Désactiver le MCP4151 (CS à HIGH)
	PORTD |= (1 << MCP4151_CS_PIN);
}

// Lire la position actuelle du wiper
uint8_t MCP4151_GetWiper(void)
{
	uint8_t position;

	// Activer le MCP4151 (CS à LOW)
	PORTD &= ~(1 << MCP4151_CS_PIN);

	// Envoyer la commande pour lire le wiper
	SPI_MasterTransmit(0x0C);      // MSB : Commande pour lire le registre Wiper
	position = SPI_MasterTransmit(0x00); // LSB : Lire la position actuelle

	// Désactiver le MCP4151 (CS à HIGH)
	PORTD |= (1 << MCP4151_CS_PIN);

	return position;
}
