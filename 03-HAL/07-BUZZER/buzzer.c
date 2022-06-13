/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : buzzet.c			     		************/
/***********	Version	   : V0.1							************/
/***********    Date       : 07-06-2022             		************/
/***********    Description: Buzzer driver source file    	************/
/***********************************************************************/

#include "buzzer.h"
#include "gpio.h"

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

void BUZZER_init(void)
{
	/* Configure buzzer pin as output pin */
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	
	/* Set buzzer pin Low in the beginning */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, 0);
}

void BUZZER_on(void)
{
	/* Set buzzer pin High */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, 1);
}

void BUZZER_off(void)
{
	/* Set buzzer pin Low */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, 0);
}