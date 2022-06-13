/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : timer.c			     		************/
/***********	Version	   : V0.1							************/
/***********    Date       : 06-06-2022             		************/
/***********    Description: AVR TIMER driver source file   ************/
/***********************************************************************/

#include "timer.h"
#include "bit_math.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static void (*g_TIMER_callBack_ptr[3])(void) = {NULL_PTR};

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

void TIMER_init(const TIMER_ConfigType *a_config_ptr)
{
	switch(a_config_ptr->TIMER_ID)
	{
		case TIMER0_ID:
			/* Configure timer0 mode and pre-scaler as required */
			switch(a_config_ptr->TIMER_mode)
			{
				case TIMER_OVF_MODE:
					/* Configure timer0 mode as overflow mode */
					TCNT0 = (uint8)a_config_ptr-> TIMER_TCNTinitialValue;
					TCCR0 = (1 << FOC0) | (a_config_ptr->TIMER_clock);
					SET_BIT(TIMSK, TOIE0);
					break;
				
				case TIMER_CTC_MODE:
					/* Configure timer0 mode as CTC mode */
					TCNT0 = (uint8)a_config_ptr-> TIMER_TCNTinitialValue;
					OCR0  = (uint8)a_config_ptr-> TIMER_OCRvalue;
					TCCR0 = (1 << FOC0) | (1 << WGM01) | (a_config_ptr->TIMER_clock);
					SET_BIT(TIMSK, OCIE0);
					break;
			}
			break;
		
		case TIMER1_ID:
			/* Configure timer1 mode and pre-scaler as required */
			switch(a_config_ptr->TIMER_mode)
			{
				case TIMER_OVF_MODE:
					/* Configure timer1 mode as overflow mode */
					TCNT1  = a_config_ptr-> TIMER_TCNTinitialValue;
					TCCR1A = (1 << FOC1A) | (1 << FOC1B);
					TCCR1B = (a_config_ptr->TIMER_clock);
					SET_BIT(TIMSK, TOIE1);
					break;
				
				case TIMER_CTC_MODE:
					/* Configure timer1 mode as CTC mode */
					TCNT1  = a_config_ptr-> TIMER_TCNTinitialValue;
					OCR1A  = a_config_ptr-> TIMER_OCRvalue;
					TCCR1A = (1 << FOC1A) | (1 << FOC1B);
					TCCR1B = (1 << WGM12) | (a_config_ptr->TIMER_clock);
					SET_BIT(TIMSK, OCIE1A);
					break;
			}
			break;
		
		case TIMER2_ID:
			/* Configure timer2 mode and pre-scaler as required */
			switch(a_config_ptr->TIMER_mode)
			{
				case TIMER_OVF_MODE:
					/* Configure timer2 mode as overflow mode */
					TCNT2 = (uint8)a_config_ptr-> TIMER_TCNTinitialValue;
					TCCR2 = (1 << FOC2) | (a_config_ptr->TIMER_clock);
					SET_BIT(TIMSK, TOIE2);
					break;
				
				case TIMER_CTC_MODE:
					/* Configure timer2 mode as CTC mode */
					TCNT2 = (uint8)a_config_ptr-> TIMER_TCNTinitialValue;
					OCR2  = (uint8)a_config_ptr-> TIMER_OCRvalue;
					TCCR2 = (1 << FOC2) | (1 << WGM21) | (a_config_ptr->TIMER_clock);
					SET_BIT(TIMSK, OCIE2);
					break;
			}
			break;
	}
}

void TIMER_setCallBack(const uint8 a_timerID, void (*a_callBack_ptr)(void))
{
	/* Set the corresponding call back function pointer */
	g_TIMER_callBack_ptr[a_timerID] = a_callBack_ptr;
}

void TIMER_deInit(const uint8 a_timerID)
{
	/* Stop the required timer */
	switch(a_timerID)
	{
		case TIMER0_ID:
			TCNT0  = 0;
			OCR0   = 0;
			TCCR0  = 0;
			TIMSK &= ~((1 << TOIE0) | (1 << OCIE0));
			break;
		
		case TIMER1_ID:
			TCNT1  = 0;
			OCR1A  = 0;
			TCCR1A = 0;
			TCCR1B = 0;
			TIMSK &= ~((1 << TOIE1) | (1 << OCIE1A));
			break;
		
		case TIMER2_ID:
			TCNT2  = 0;
			OCR2   = 0;
			TCCR2  = 0;
			TIMSK &= ~((1 << TOIE2) | (1 << OCIE2));
			break;
	}
}

/************************************************************************/
/***********				TIMER0 ISRs    					 ************/
/************************************************************************/
ISR(TIMER0_OVF_vect)
{
	/* Call the function if function call back pointer is set */
	if(g_TIMER_callBack_ptr[0] != NULL_PTR)
	{
		(*g_TIMER_callBack_ptr[0])();
	}
}

ISR(TIMER0_COMP_vect)
{
	/* Call the function if function call back pointer is set */
	if(g_TIMER_callBack_ptr[0] != NULL_PTR)
	{
		(*g_TIMER_callBack_ptr[0])();
	}
}

/************************************************************************/
/***********				TIMER1 ISRs    					 ************/
/************************************************************************/
ISR(TIMER1_OVF_vect)
{
	/* Call the function if function call back pointer is set */
	if(g_TIMER_callBack_ptr[1] != NULL_PTR)
	{
		(*g_TIMER_callBack_ptr[1])();
	}
}

ISR(TIMER1_COMPA_vect)
{
	/* Call the function if function call back pointer is set */
	if(g_TIMER_callBack_ptr[1] != NULL_PTR)
	{
		(*g_TIMER_callBack_ptr[1])();
	}
}

/************************************************************************/
/***********				TIMER2 ISRs    					 ************/
/************************************************************************/
ISR(TIMER2_OVF_vect)
{
	/* Call the function if function call back pointer is set */
	if(g_TIMER_callBack_ptr[2] != NULL_PTR)
	{
		(*g_TIMER_callBack_ptr[2])();
	}
}

ISR(TIMER2_COMP_vect)
{
	/* Call the function if function call back pointer is set */
	if(g_TIMER_callBack_ptr[2] != NULL_PTR)
	{
		(*g_TIMER_callBack_ptr[2])();
	}
}

