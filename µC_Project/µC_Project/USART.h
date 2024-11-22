#ifndef _USART_H_
#define _USART_H_

//INCLUDE

//DEFINE

//PROTOTYPE FONCTIONS EXTERNES

// Fonction qui envoie un byte (char) sur le port USART0.
void Usart0_Tx(char data);
// Fonction qui envoie une ch�ine de carct�res sur le port Usart0.
void Usart0_Tx_String(char *String);
// Fonction qui initialise l'USART0 en mode �mission � 9600 baud.
void USART0_Init_9600(void);
// Fonction qui initialise l'USART0 en mode �mission � 9600 baud avec interruption en r�ception
void USART0_Init_9600_INT_ON_RX(void);

void Usart0_Flush(void);


#endif 