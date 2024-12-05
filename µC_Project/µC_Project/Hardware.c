#include <avr/io.h>
#include "Main.h"

void Init_Hardware(void)
{
	//Input Mode
	CLR_BIT(DDRC,DDC2);
	CLR_BIT(DDRC,DDC3);
	CLR_BIT(DDRC,DDC4);
	CLR_BIT(DDRC,DDC5);
	CLR_BIT(DDRC,DDC6);
	
	//enable pull up
	SET_BIT(PORTC,PORTC2);
	SET_BIT(PORTC,PORTC3);
	SET_BIT(PORTC,PORTC4);
	SET_BIT(PORTC,PORTC5);
	SET_BIT(PORTC,PORTC6);
	
	// enable int
	SET_BIT(PCICR,PCIE2);
	
	// enable mask
	SET_BIT(PCMSK2,PCINT18);  // UP
	SET_BIT(PCMSK2,PCINT19); // DOWN
	SET_BIT(PCMSK2,PCINT20); // LEFT
	SET_BIT(PCMSK2,PCINT21); // RIGHT
	SET_BIT(PCMSK2,PCINT22); // ENTER
}