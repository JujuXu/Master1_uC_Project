//FONCTIONS TIMER


//INCLUDE
#include "TIMERS.h"
#include "Main.h"
#include <avr/io.h>


//DECLARATION DES VARIABLES GLOGALES


//PROTOTYPE FONCTIONS INTERNES


//CONTENU FONCTIONS EXTERNES


void TIMER1_Init_1ms(void)
{
	//En mode compteur le registre TCCR1A = 0x00
	//Si diviseur par 1 -> 1000000/1 = 1000 Khz
	// Une p�riode = 1�S
	// Si je compte jusque 1000 --> 1000 X 1 = 1 ms
	
	// MODE OVERFLOW
	// (TCCR1B) : WGM13 =0 |WGM12 = 0  (TCCR1A) : WGM11 = 0 | WGM10 =0
	CLR_BIT(TCCR1B, WGM13);
	CLR_BIT(TCCR1B, WGM12);
	CLR_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM10);
	
	//No prescaler
	// (TCCR1B) : CS12 = 0 | CS11 = 0 | CS10 = 0
	CLR_BIT(TCCR1B, CS12);
	CLR_BIT(TCCR1B, CS11);
	SET_BIT(TCCR1B, CS10);
	
	// Valeur initiale du compteur = 65535 - 1000 = 64535
	TCNT1 = 64535;
	/* Autre proc�d�, on �crit (en format hexad�cimal) dans le byte de poids plus �lev�, puis dans le byte de poids le moins �lev�.
	TCNT1H = 0xFC;
	TCNT1L = 0x17;
	*/
	
	// Autorisation de l'interruption en cas d'overflow
	SET_BIT(TIMSK1, TOIE1);
	//TIMSK1 |= (1<<TOIE1);
}


void TIMER0_Init_1ms(void)
{
	// fr�quence horloge = 1000000 hz
	// Utilisation du TIMER 0, comptage sur 8 bits
	// Si diviseur par 8 --> 1000000/8 = 125 Khz
	// Une p�riode = 8�S
	// Si je compte jusque 125 --> 125 X 8 = 1 ms
	//TCCR0A = 0x00; // |= (0<<CS02)|(1<<CS01)|(0<<CS00);
	CLR_BIT(TCCR0A,CS02);
	SET_BIT(TCCR0A,CS01);
	CLR_BIT(TCCR0A,CS00);
	//TCCR0B |= (0<<CS02)|(1<<CS01)|(0<<CS00);
	CLR_BIT(TCCR0B,CS02);
	SET_BIT(TCCR0B,CS01);
	CLR_BIT(TCCR0B,CS00);
	
	// Valeur initiale du compteur = 256 - 125 = 131
	TCNT0 = 131;
	// Autorisation de l'interruption en cas d'overflow
	//TIMSK0 = (1<<TOIE0);
	SET_BIT(TIMSK0,TOIE0);
}

//CONTENU FONCTIONS INTERNES

	
