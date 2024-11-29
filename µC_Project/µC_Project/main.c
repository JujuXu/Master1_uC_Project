#include <avr/io.h>

#include "OS.h"
#include "lcd.h"
#include "Main.h"
#include "TIMERS.h"
#include "TC74.h"
#include "I2C_Master.h"

extern unsigned char TWI_buf[TWI_BUFFER_SIZE];

int main(void)
{
	Init_Hardware();
	
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("LCD OK !");
	
	OS_Init();
	
	TWI_Master_Initialise();
	
	Callbacks_Record_Timer(TC74_Temp_Read,100);
	
	OS_Start();
	
	return 0;
}

char viewTemp(char input)
{
	char string[3];
	
	signed char value = TC74_BCDtoChar(TWI_buf[1]);
	static signed char last_value;
	
	static unsigned char FIF = TRUE; // first in function
	
	if (FIF)
	{
		TC74_Temp_Read();
		
		last_value = value +1;
		
		FIF = FALSE;
	}
	else 
	{
		if (value != last_value)
		{
			// -127 to -63 good
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