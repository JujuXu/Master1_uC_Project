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
#define ST_TXT_RED		1
#define ST_FCT_RED		2
#define ST_TXT_GREEN	3
#define ST_FCT_GREEN	4
#define ST_TXT_BLUE		5
#define ST_FCT_BLUE		6
#define ST_TXT_POT		7
#define ST_FCT_POT		8
#define ST_TXT_DATE		9
#define ST_FCT_DATE		10
#define ST_TXT_HRS		11
#define ST_FCT_HRS		12

//#define _10BITS


//DECLARATION DES FONCTIONS

//CALLBACK
void Switch_LED(void);	// callback timer --> cligotement de la LED
void Check_PORTE(void);	// callback timer --> check se demande d'ouverture de porte
void Stop_GACHE(void);	// callback timer --> désactivation de la gache électrique
void Stop_LED(void);	// callback timer --> arrêt du clignotement de la LED
//void Choose_Color(void); // callback timer --> Lancement conversion AD + commande PWM pour lr choix de la couleur
void USART0_RX(volatile char *Trame_USART0);	// callback USART0 --> gestion de la commande reçue via le port série.


void getState(void);

//STATE MACHINE
char Set_Pwm_Red(char input);
char Set_Pwm_Green(char input);
char Set_Pwm_Blue(char input);
char Set_Voltage(char input);
char Display_Date(char input);
char Display_Hrs(char input);


//AUTRES
int EDIT_VALUE_0_99(int Initial_Value, char input);


#endif
