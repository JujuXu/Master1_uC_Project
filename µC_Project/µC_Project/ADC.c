// x10 ADC1 ADC0
// x200 ADC1 ADC0
// x1 ADC1 ADC2

// ADC0 and ADC2 linked together

#include "ADC.h"
#include <avr/io.h>
#include "Main.h"

unsigned int ADC_val;

void ADC_INIT(void)
{
	//////////////////////////////////////////////////////////////////////////
	// ADMUX
	CLR_BIT(ADMUX, REFS1);
	SET_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, ADLAR);
	
	ADC_setGain(X1);
	
	//////////////////////////////////////////////////////////////////////////
	// ADSCRA
	CLR_BIT(ADCSRA,ADEN);
	SET_BIT(ADCSRA,ADPS2);
	CLR_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS0);
	//////////////////////////////////////////////////////////////////////////
}

void ADC_setGain(char gain)
{
	switch (gain)
	{
		case X1:
			// ADC1(+) ADC2(-)
			SET_BIT(ADMUX, MUX4);
			SET_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX0);
			break;
		case X10:
			// ADC1(+) ADC0(-)
			CLR_BIT(ADMUX, MUX4);
			SET_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX0);
			break;
		case X200:
			// ADC1(+) ADC0(-)
			CLR_BIT(ADMUX, MUX4);
			SET_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX2);
			SET_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX0);
			break;
	}
}

void ADC_ON(void)
{
	SET_BIT(ADCSRA,ADEN);
}

void ADC_OFF(void)
{
	CLR_BIT(ADCSRA,ADEN);
}


unsigned int ADC_CONVERT_10BITS(void)
{
	//Usart0_Tx_String("ADC_CONVERT begin");
	//Usart0_Tx('\r');
	
	ADC_ON();
	SET_BIT(ADCSRA,ADSC);
	while((ADCSRA & (1<<ADSC)));
	ADC_OFF();
	
	//char string[6];
	//Usart0_Tx_String("ADC_CONVERT end: ");
	//Usart0_Tx_String(itoa(ADC, string, 10));
	//Usart0_Tx('\r');
	
	ADC_val = ADC;
}