#ifndef _main_h_
#define _main_h_

// INCLUDE (si applicable)

// DEFINE 

// Gestion registre par bit unique
#define SET_BIT(port,bit)  (port |= (1<<bit))   //set bit in port
#define CLR_BIT(port,bit)  (port &= ~(1<<bit))  //clear bit in port
#define TOGGLE_IO(port,bit) (port ^= (1<<bit))  //toggle

#define TRUE				1
#define FALSE				0

#ifndef NULL
#define NULL	0
#endif

enum {NONE,UP, DOWN, LEFT, ENTER, RIGHT};	// Used with the button variable
	
// STATE MACHINE
#define ST_TXT_Temp		1
#define ST_FCT_Temp		2
#define ST_TXT_ADC		3
#define ST_FCT_ADC		4
#define ST_TXT_ADC_G	5
#define ST_FCT_ADC_G	6
#define ST_TXT_DPOT		7
#define ST_FCT_DPOT		8


//DECLARATION DES FONCTIONS

//CALLBACK
void USART0_RX(volatile char *Trame_USART0);	// callback USART0 --> gestion de la commande reçue via le port série.

//STATE MACHINE FUNCTIONS
char viewTemp(char input);
char viewADC(char input);
char setADC_G(char input);
char setDPOT(char input);

#endif
