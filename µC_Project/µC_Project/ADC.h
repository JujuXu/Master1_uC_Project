#ifndef _ADC_H_
#define _ADC_H_

// DEFINE

// FONCTIONS VISIBLES
void ADC_INIT(void);
void ADC_ON(void);
void ADC_OFF(void);
void ADC_setGain(char gain);
unsigned int ADC_CONVERT_10BITS(void);

enum {X1, X10, X200};

#endif
