/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : adc.h			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 18-05-2022             		************/
/***********    Description: AVR ADC driver header file    	************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef ADC_H
#define ADC_H

#include "std_types.h"

/**********************************************************************/
/***********				Constants Definitions			  *********/
/**********************************************************************/

#define ADC_2_PRESCALER			(0b001)
#define ADC_4_PRESCALER			(0b010)
#define ADC_8_PRESCALER			(0b011)
#define ADC_16_PRESCALER		(0b100)
#define ADC_32_PRESCALER		(0b101)
#define ADC_64_PRESCALER		(0b110)
#define ADC_128_PRESCALER		(0b111)

#define ADC_VREF_AREF			(0b00)
#define ADC_VREF_AVCC			(0b01)
#define ADC_VREF_2_56V_INT		(0b11)

#define ADC_LEFT_ADJUST			1
#define ADC_RIGHT_ADJUST		0

#define ADC_PRESCALER			ADC_8_PRESCALER
#define ADC_VREF				ADC_VREF_AREF
#define ADC_ADJUST				ADC_RIGHT_ADJUST

#define ADC_MAX_VALUE    		1023
#define ADC_REF_VOLT_VALUE   	2.56

/**********************************************************************/
/***********				Types Deceleration				  *********/
/**********************************************************************/

typedef struct{ 

	uint8 ADC_referenceVolt;	/* To select analog reference volt */
	uint8 ASC_prescaler;		/* To select ADC pre-scaler */
	
}ADC_ConfigType;				/* Structure deceleration for ADC configurations */

extern volatile uint16 g_ADC_data;

/**********************************************************************/
/***********				Functions Prototypes			  *********/
/**********************************************************************/

void ADC_init(const ADC_ConfigType * a_config_ptr);
uint16 ADC_readChannelSynch(uint8 pinID);
void ADC_readChannelAsynch(uint8 pinID);
void ADC_enableInterrupt(void);
void ADC_disableInterrupt(void);
void ADC_setCallBack(void (*l_callBack_ptr)(void));

#endif /* ADC_H */
