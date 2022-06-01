/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : icu.c			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 23-05-2022             		************/
/***********    Description: AVR ICU driver source file    	************/
/***********************************************************************/

#include "bit_math.h"
#include "icu.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static void (*g_ICU_callBack_ptr)(void) = NULL_PTR;

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

void ICU_init(const ICU_ConfigType *a_cofig_ptr)
{
	CLEAR_BIT(DDRD, PD6);		/* Configure ICP1(PD6) as input pin */
	TCNT1 = 0;					/* Reset timer1 counter register */
	ICR1  = 0;					/* Reset input capture register */
	
	/* Configure Timer1 on normal mode*/
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);
	
	/* Select input capture edge detection */
	TCCR1B = (TCCR1B & 0xBF) | ((a_cofig_ptr->ICU_Edge) << 6);
	
	/* Select timer1 clock pre-scaler */
	TCCR1B = (TCCR1B & 0xF8) | (a_cofig_ptr->ICU_TimerClock);
	
	SET_BIT(TIMSK, TICIE1);		/* Enable timer1 input capture interrupt */

}

void ICU_setCallBack(void (*a_callBack_ptr)(void))
{
	/* Set call back function pointer */
	g_ICU_callBack_ptr = a_callBack_ptr;
}

void ICU_setEdgeDetection(const uint8 a_edgeType)
{
	/* Select input capture edge detection */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType << 6);
}

void ICU_clearTimerValue(void)
{
	TCNT1 = 0;					/* Clear timer1 counter register */
}

void ICU_deInit(void)
{
	CLEAR_BIT(TIMSK, TICIE1);	/* Disable timer1 input capture interrupt */

	/* Reset All timer1 registers to their default values */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	ICR1   = 0;
	
}

uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;				/* Return input capture register value */
}


/************************************************************************/
/***********					ICU	ISR    					 ************/
/************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	/* Call the function if function call back pointer is set */
	if(g_ICU_callBack_ptr != NULL_PTR)
	{
		(*g_ICU_callBack_ptr)();
	}
}


