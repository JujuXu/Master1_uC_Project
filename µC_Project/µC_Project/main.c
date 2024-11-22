#include <avr/io.h>

#include "OS.h"
#include "lcd.h"
#include "Main.h"
#include "TIMERS.h"


int main(void)
{
	Init_Hardware();
	
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("LCD OK !");
	
	OS_Init();
	
	OS_Start();
	
	return 0;
}

char viewTemp(char input)
{
	static unsigned char FIF = TRUE; // first in function
	
	if (FIF)
	{
		FIF = FALSE;
	}
	else
	{
		if (input != ENTER)
		{
			
		}
		else
		{
			FIF = TRUE;
			return ST_TXT_Temp;
		}
	}
	
	return ST_FCT_Temp;
}

char viewADC(char input)
{
	static unsigned char FIF = TRUE; // first in function
	
	if (FIF)
	{
		FIF = FALSE;
	}
	else
	{
		if (input != ENTER)
		{
			
		}
		else
		{
			FIF = TRUE;
			return ST_TXT_ADC;
		}
	}
	
	return ST_FCT_ADC;
}

char setADC_G(char input)
{
	static unsigned char FIF = TRUE; // first in function
	
	if (FIF)
	{
		FIF = FALSE;
	}
	else
	{
		if (input != ENTER)
		{
			
		}
		else
		{
			FIF = TRUE;
			return ST_TXT_ADC_G;
		}
	}
	
	return ST_FCT_ADC_G;
}

char setDPOT(char input)
{
	static unsigned char FIF = TRUE; // first in function
	
	if (FIF)
	{
		FIF = FALSE;
	}
	else
	{
		if (input != ENTER)
		{
			
		}
		else
		{
			FIF = TRUE;
			return ST_TXT_DPOT;
		}
	}
	
	return ST_FCT_DPOT;
}