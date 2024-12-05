#ifndef _menu_h_
#define _menu_h_

#include <avr/pgmspace.h>
#include "Main.h"

#ifndef PGM_P
#define PGM_P const rom char *  
#endif

typedef struct PROGMEM
{
    unsigned char state;
    unsigned char input;
    unsigned char nextstate;
} MENU_NEXTSTATE;

typedef struct PROGMEM
{
    unsigned char state;
	PGM_P pText;	
    char (*pFunc)(char input);
} MENU_STATE;

// Menu text
const char Txt_Temp[] PROGMEM 		=	"Temp Menu";
const char Txt_ADC[] PROGMEM 		=	"ADC";
const char Txt_ADC_G[] PROGMEM 		=	"Gain ADC";
const char Txt_DPOT[] PROGMEM 		=	"Digital POT";


const MENU_NEXTSTATE menu_nextstate[] PROGMEM = {
//  STATE                       INPUT       NEXT STATE
// MENUS

	{ST_TXT_Temp,	            DOWN,		ST_TXT_ADC},	
	{ST_TXT_Temp,				UP,			ST_TXT_DPOT},
	{ST_TXT_Temp,				ENTER,		ST_FCT_Temp},
	
	{ST_TXT_ADC,				DOWN,		ST_TXT_ADC_G},
	{ST_TXT_ADC,				UP,			ST_TXT_Temp},
	{ST_TXT_ADC,				ENTER,		ST_FCT_ADC},
	
	{ST_TXT_ADC_G,				DOWN, 		ST_TXT_DPOT},
	{ST_TXT_ADC_G,				UP, 		ST_TXT_ADC},
	{ST_TXT_ADC_G,				ENTER, 		ST_FCT_ADC_G},
	
	{ST_TXT_DPOT,				DOWN, 		ST_TXT_Temp},
	{ST_TXT_DPOT,				UP, 		ST_TXT_ADC_G},
	{ST_TXT_DPOT,				ENTER, 		ST_FCT_DPOT},
		
	{0,                         0,          0},
};


const MENU_STATE Menu_State[] PROGMEM = {
//  STATE                               STATE TEXT                  STATE_FUNC

    {ST_TXT_Temp,				        Txt_Temp,	  		        NULL},
	{ST_FCT_Temp,						NULL,						viewTemp},
	{ST_TXT_ADC,				        Txt_ADC,	  		        NULL},
	{ST_FCT_ADC,						NULL,						viewADC},
	{ST_TXT_ADC_G,				        Txt_ADC_G,	  		        NULL},
	{ST_FCT_ADC_G,						NULL,						setADC_G},
	{ST_TXT_DPOT,				        Txt_DPOT,	  		        NULL},
	{ST_FCT_DPOT,						NULL,						setDPOT},
	
    {0,                                 NULL,                       NULL},
		
};	
#endif