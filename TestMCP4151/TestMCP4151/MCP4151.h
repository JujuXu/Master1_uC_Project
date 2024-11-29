#ifndef MCP4151_H_
#define MCP4151_H_

#include <stdint.h>

// Définir le numéro de pin pour le CS
#define MCP4151_CS_PIN PORTD4

// Prototypes des fonctions
void MCP4151_Init(void);             // Initialisation du MCP4151
void MCP4151_SetWiper(uint8_t value); // Régler la position du wiper
uint8_t MCP4151_GetWiper(void);       // Lire la position actuelle du wiper

#endif /* MCP4151_H_ */
