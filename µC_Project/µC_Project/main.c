#include <avr/io.h>

#include "OS.h"
#include "lcd.h"
#include "Main.h"
#include "TIMERS.h"
#include "TC74.h"
#include "I2C_Master.h"
#include "ADC.h"
#include "MCP4151.h"

extern unsigned char TWI_buf[TWI_BUFFER_SIZE];
extern unsigned int ADC_val;

int main(void)
{
	Init_Hardware(); // setup I/O for buttons
	
	// setup LCD
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("LCD OK !");
	
	OS_Init(); // setup callbacks

	TWI_Master_Initialise(); // setup I2C comm
	
	ADC_INIT(); // setup ADC
	
	MCP4151_Init(); // setup digital pot
	
	//////////////////////////////////////////////////////////////////////////
	
	Callbacks_Record_Timer(TC74_Temp_Read, 100); // lecture périodique de la température sur le TC74, à stocker dans TWI_buf
	Callbacks_Record_Timer(ADC_CONVERT_10BITS, 100); // lecture périodique de l'ADC, à stocker dans ADC_val
	
	//////////////////////////////////////////////////////////////////////////
	
	OS_Start(); // start callbacks
	
	return 0;
}

char viewTemp(char input)
{
	char string[3]; // string d'affichage lcd
	
	signed char value = TC74_BCDtoChar(TWI_buf[1]); // récupération de la valeur du buffer TWI, puis convertir BCD vers char
	static signed char last_value; // stocker dernière valeur pour comparer pour affichage stable
	
	static unsigned char FIF = TRUE; // first in function, exécution de code au lancement de la fonction
	
	if (FIF)
	{
		// affichage première ligne du lcd
		lcd_gotoxy(0,0);
		lcd_puts("                ");
		lcd_gotoxy(0,0);
		lcd_puts("Temperature:");
		
		last_value = value +1; // pour afficher dès le lancement
		
		FIF = FALSE;
	}
	else 
	{
		if (value != last_value)
		{
			if (value < -65)
			{
				Usart0_Tx_String("viewTemp overflow: ");
				Usart0_Tx_String(itoa(value, string, 10));
				Usart0_Tx('\r');
				
				lcd_gotoxy(0,1);
				lcd_puts("                ");
				lcd_gotoxy(0,1);
				
				lcd_puts("Overflow !");
			}
			else
			{
				lcd_gotoxy(0,1);
				lcd_puts("                ");
				lcd_gotoxy(0,1);
				
				lcd_puts(itoa(value, string, 10));
				lcd_putc((char)(223));
				lcd_puts("C");
				
				last_value = value;
				
				Usart0_Tx_String(itoa(value, string, 10));
				Usart0_Tx('\r');
			}
		}
		
		if (input == ENTER)
		{
			FIF = TRUE;
			return ST_TXT_Temp;
		}
	}
	
	return ST_FCT_Temp;
}

char viewADC(char input)
{
	static unsigned int old_adc;
	unsigned int new_adc = ADC_val;
	char string[16];
	float adc_float;
	static unsigned char FIF = TRUE;
	
	if (FIF)
	{
		lcd_gotoxy(0,0);
		lcd_puts("                ");
		lcd_gotoxy(0,0);
		lcd_puts("DIFF Voltage:");
		
		FIF = FALSE;
	}
	
	if (new_adc != old_adc)
	{
		lcd_gotoxy(0,1);
		lcd_puts("                ");
		lcd_gotoxy(0,1);
		
		adc_float = (float) new_adc*5/1024;
		
		My_ftoa(adc_float, string, 2, 'f');
		lcd_puts(string);
		lcd_puts("V");
		
		old_adc = new_adc;
	}
	
	if (input == ENTER)
	{
		FIF = TRUE;
		return ST_TXT_ADC;	
	}
	
	return ST_FCT_ADC;
}

char setADC_G(char input)
{
	static unsigned char FIF = TRUE; // first in function
	static char iGain = X1;
	
	char string[3][4] = {
		"X1",
		"X10",
		"X200"
	};
	
	if (FIF)
	{
		FIF = FALSE;
		
		lcd_gotoxy(0,0);
		lcd_puts("                ");
		lcd_gotoxy(0,0);
		lcd_puts("Select Gain:");
		
		lcd_gotoxy(0,1);
		lcd_puts("                ");
		lcd_gotoxy(0,1);
		
		lcd_puts(string[iGain]);
	}
	else
	{
		if (input != ENTER)
		{
			if (input == RIGHT)
			{
				iGain++;
				
				if (iGain > 2)
				{
					iGain = 0;
				}
				
				lcd_gotoxy(0,1);
				lcd_puts("                ");
				lcd_gotoxy(0,1);
				
				lcd_puts(string[iGain]);
			}
			else if (input == LEFT)
			{				
				if (iGain == 0)
				{
					iGain = 2;
				}
				else
				{
					iGain--;
				}
				
				lcd_gotoxy(0,1);
				lcd_puts("                ");
				lcd_gotoxy(0,1);
				
				lcd_puts(string[iGain]);
			}
		}
		else
		{
			FIF = TRUE;
			ADC_setGain(iGain);
			return ST_TXT_ADC_G;
		}
	}
	
	return ST_FCT_ADC_G;
}

char setDPOT(char input)
{
	static unsigned char FIF = TRUE; // first in function
	static int WiperValue = 128;
	float displayWiper;
	
	char string[16];
	
	if (FIF)
	{
		MCP4151_SetWiper(WiperValue);
		
		displayWiper = 10000*((float)WiperValue/255);
		lcd_gotoxy(0,1);
		lcd_puts("                ");
		lcd_gotoxy(0,1);
		My_ftoa(displayWiper, string,2,'f');
		lcd_puts(string);
		
		FIF = FALSE;
	}
	else
	{
		if (input != ENTER)
		{
			
			if(input == UP){
				if(WiperValue < 255){
					WiperValue++;
					MCP4151_SetWiper(WiperValue);
				}
				displayWiper = 10000*((float)WiperValue/255);
				lcd_gotoxy(0,1);
				lcd_puts("                ");
				lcd_gotoxy(0,1);
				My_ftoa(displayWiper, string,2,'f');
				lcd_puts(string);
			}
			else if (input == DOWN){
				if(WiperValue > 0){
					WiperValue--;
					MCP4151_SetWiper(WiperValue);
				}
				displayWiper = 10000*((float)WiperValue/255);
				lcd_gotoxy(0,1);
				lcd_puts("                ");
				lcd_gotoxy(0,1);
				My_ftoa(displayWiper, string,2,'f');
				lcd_puts(string);
			}
			else if (input == LEFT)
			{
				WiperValue = WiperValue-10;
				if(WiperValue < 0)
				{
					WiperValue = 0;
				}
				MCP4151_SetWiper(WiperValue);
				displayWiper = 10000*((float)WiperValue/255);
				lcd_gotoxy(0,1);
				lcd_puts("                ");
				lcd_gotoxy(0,1);
				My_ftoa(displayWiper, string,2,'f');
				lcd_puts(string);
			}
			else if (input == RIGHT)
			{
				WiperValue = WiperValue + 10;
				if(WiperValue > 255){
					WiperValue = 255;
				}
				MCP4151_SetWiper(WiperValue);
				displayWiper = 10000*((float)WiperValue/255);
				lcd_gotoxy(0,1);
				lcd_puts("                ");
				lcd_gotoxy(0,1);
				My_ftoa(displayWiper, string,2,'f');
				lcd_puts(string);
			}
		}
		else
		{
			FIF = TRUE;
			return ST_TXT_DPOT;
		}
	}
	
	return ST_FCT_DPOT;
}