/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : ultrasonic.c			     	************/
/***********	Version	   : V0.1							************/
/***********    Date       : 30-05-2022             		************/
/***********    Description: HC-SR04 driver source file 	************/
/***********************************************************************/

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>

static volatile uint8  g_echo_edge = 0;
static volatile uint16 g_ticks_us = 0;

static void ULTRASONIC_trigger(void);
static void ULTRASONIC_edgeProcessing(void);

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

void ULTRASONIC_init(void)
{
	ICU_ConfigType ICU_configuration = {ICU_F_CPU_8, ICU_RISING_EDGE};
	/* Configure ICU as F_CPU/8 and rising edge */
	ICU_init(&ICU_configuration);

	/* Set call back function to handle edge processing */
	ICU_setCallBack(ULTRASONIC_edgeProcessing);

	/* Configure trigger pin as output pin */
	GPIO_writePin(ULTRASONIC_TRIG_PORT_ID, ULTRASONIC_TRIG_PIN_ID, 0);
	GPIO_setupPinDirection(ULTRASONIC_TRIG_PORT_ID, ULTRASONIC_TRIG_PIN_ID, PIN_OUTPUT);

}

uint16 ULTRASONIC_readDistance(void)
{
	uint16 l_distance_cm;

	/* Clear edge flag to start new cycle */
	g_echo_edge = 0;

	/* Generate a pulse on trigger pin */
	ULTRASONIC_trigger();

	/* Wait for echo pin to be low */
	while(g_echo_edge != 2);
	
	/* Calculate distance in cm */
	l_distance_cm = g_ticks_us * 0.01775;
	
	/* Return distance */
	return l_distance_cm;
}

static void ULTRASONIC_trigger(void)
{
	/* Generate a pulse with 10us time ON */
	GPIO_writePin(ULTRASONIC_TRIG_PORT_ID, ULTRASONIC_TRIG_PIN_ID, 1);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIG_PORT_ID, ULTRASONIC_TRIG_PIN_ID, 0);
	
}

static void ULTRASONIC_edgeProcessing(void)
{
	switch(g_echo_edge)
	{
		case 0:
			/* Clear timer to get timer value later with reference to 0 */
			ICU_clearTimerValue();
			/* Change trigger edge detection to calculate ON time */
			ICU_setEdgeDetection(ICU_FALLING_EDGE);
			g_echo_edge = 1;
			break;
		
		case 1:
			/* Get ON time and store it in global variable */
			g_ticks_us = ICU_getInputCaptureValue();
			/* Change trigger edge detection to rising */
			ICU_setEdgeDetection(ICU_RISING_EDGE);
			g_echo_edge = 2;
			break;
	}
}


