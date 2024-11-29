#ifndef _ADC_H_
#define _ADC_H_

// DEFINE

// FONCTIONS VISIBLES
void ADC_init(void);
void ADC_ON(void);
void ADC_OFF(void);
void ADC_setGain(char gain);
unsigned int Conversion_ADC_10bits(void);

enum {X1, X10, X100};

#endif
