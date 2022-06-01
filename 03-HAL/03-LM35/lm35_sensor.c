/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : lm35_sensor.c			     	************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: LM35 sensor driver source file ************/
/***********************************************************************/

#include "lm35_sensor.h"
#include "adc.h"

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

/*
 * Description:
 * Return the calculated temperature from ADC signal value.
 */
uint8 LM35_getTemperature(void)
{
	uint8  l_temperature;
	uint16 l_adcValue;
	
	/* Get ADC value */
	l_adcValue = ADC_readChannelSynch(LM35_CHANNEL_ID);
	
	/* Calculate temperature value using ADC value */
	l_temperature =  (uint8)(((uint32)l_adcValue*ADC_REF_VOLT_VALUE*LM35_MAX_TEMP) / (LM35_MAX_VOLT_VALUE*ADC_MAX_VALUE));
	
	/* Return temperature value */
	return l_temperature;
}
