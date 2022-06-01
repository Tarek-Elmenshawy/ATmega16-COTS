/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : adc.c			     			************/
/***********	Version	   : V0.2							************/
/***********    Date       : 18-05-2022             		************/
/***********    Description: AVR ADC driver source file    	************/
/***********************************************************************/

#include "adc.h"
#include "bit_math.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static void (*g_ADC_callBack_ptr)(void) = NULL_PTR;
volatile uint16 g_ADC_data;

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

/*
 * Description:
 * Initialize ADC peripheral depends on the configuration structure.
 */
void ADC_init(const ADC_ConfigType * a_config_ptr)
{
	/* Select voltage reference */
	ADMUX = (ADMUX & 0x3F) | ((a_config_ptr->ADC_referenceVolt) << 6);
	
	#if (ADC_ADJUST == ADC_LEFT_ADJUST)
		SET_BIT(ADMUX, ADLAR);			/* Set ADLAR to ADC left adjust result */
	#endif
	
	/* Set ADC pre-scaler, disable interrupt and enable ADC */
	ADCSRA = (a_config_ptr->ASC_prescaler) | (1 << ADEN);
}

/*
 * Description:
 * Return the ADC value of required channel.
 */
uint16 ADC_readChannelSynch(uint8 pinID)
{
	ADMUX = (ADMUX & 0xE0) | (pinID);	/* Select ADC channel */
	SET_BIT(ADCSRA, ADSC);				/* Start ADC conversion */
	while(BIT_IS_CLEAR(ADCSRA, ADIF));	/* Wait for conversion complete */
	SET_BIT(ADCSRA, ADIF);				/* Clear ADC flag */
	return ADC;							/* Return data value */
}

/*
 * Description:
 * Select ADC channel and start conversion.
 */
void ADC_readChannelAsynch(uint8 pinID)
{
	ADMUX = (ADMUX & 0xE0) | (pinID);	/* Select ADC channel */
	SET_BIT(ADCSRA, ADSC);				/* Start ADC conversion */
}

/*
 * Description:
 * Enable ADC interrupt.
 */
void ADC_enableInterrupt(void)
{
	SET_BIT(ADCSRA, ADIE);				/* Enable ADC interrupt */
}

/*
 * Description:
 * Disable ADC interrupt.
 */
void ADC_disableInterrupt(void)
{
	CLEAR_BIT(ADCSRA, ADIE);			/* Disable ADC interrupt */
}

/*
 * Description:
 * Set function call back pointer as required.
 */
void ADC_setCallBack(void (*l_callBack_ptr)(void))
{
	/* Set function call back pointer */
	g_ADC_callBack_ptr = l_callBack_ptr;
}

/***********************************************************************/
/***********					ADC	ISR    					   *********/
/***********************************************************************/

ISR(ADC_vect)
{
	g_ADC_data = ADC;					/* Get conversion value */
	/* Call the function if function call back pointer is set */
	if(g_ADC_callBack_ptr != NULL_PTR)
	{
		(*g_ADC_callBack_ptr)();
	}
}
