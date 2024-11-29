// x10 ADC1 ADC0
// x200 ADC1 ADC0
// x1 ADC1 ADC2

// ADC0 and ADC2 linked together

#include "ADC.h"
#include <avr/io.h>
#include "Main.h"

void ADC_init(void)
{
	SET_BIT(ADMUX, REFS1);
	CLR_BIT(ADMUX, REFS0);
	
}

void ADC_setGain(char gain)
{
	switch (gain)
	{
		case X1:
			// ADC1(+) ADC2(-)
			break;
		case X10:
			// ADC1(+) ADC0(-)
			break;
		case X100:
			// ADC1(+) ADC0(-)
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


unsigned int Conversion_ADC_10bits(void)
{
	// *** CONVERSION ADC *** (DS p207)
	//ADCSRA |= (1<<ADSC);
	SET_BIT(ADCSRA,ADSC);
	// attendre fin de conversion (DS p 205)
	while((ADCSRA & (1<<ADSC)));
	return ADC;
}