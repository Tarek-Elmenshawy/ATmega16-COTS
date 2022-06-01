/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : gpio.c			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: AVR GPIO driver source file    ************/
/***********************************************************************/

#include "gpio.h"
#include "bit_math.h"
#include <avr/io.h>

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port ID or pin ID are not correct,
 * The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 a_portID, uint8 a_pinID, uint8 a_direction)
{
	/* Check input validation */
	if(a_portID < NUM_OF_PORTS || a_pinID < NUM_OF_PINS_PER_PORT)
	{
		/* Set up the pin direction as required */
		switch(a_portID)
		{
			case PORTA_ID:
				if(a_direction == PIN_INPUT)
					CLEAR_BIT(DDRA, a_pinID);
				else
					SET_BIT(DDRA, a_pinID);
				break;
				
			case PORTB_ID:
				if(a_direction == PIN_INPUT)
					CLEAR_BIT(DDRB, a_pinID);
				else
					SET_BIT(DDRB, a_pinID);
				break;
				
			case PORTC_ID:
				if(a_direction == PIN_INPUT)
					CLEAR_BIT(DDRC, a_pinID);
				else
					SET_BIT(DDRC, a_pinID);
				break;
			
			case PORTD_ID:
				if(a_direction == PIN_INPUT)
					CLEAR_BIT(DDRD, a_pinID);
				else
					SET_BIT(DDRD, a_pinID);
				break;
		}
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port ID or pin ID are not correct, The function will not
 * handle the request. If the pin is input, this function will enable/disable
 * the internal pull-up resistor.
 */
void GPIO_writePin(uint8 a_portID, uint8 a_pinID, uint8 a_value)
{
	/* Check input validation */
	if(a_portID < NUM_OF_PORTS || a_pinID < NUM_OF_PINS_PER_PORT)
	{
		/* Set the pin value as required */
		switch(a_portID)
		{
			case PORTA_ID:
				if(a_value == LOW)
					CLEAR_BIT(PORTA, a_pinID);
				else
					SET_BIT(PORTA, a_pinID);
				break;
				
			case PORTB_ID:
				if(a_value == LOW)
					CLEAR_BIT(PORTB, a_pinID);
				else
					SET_BIT(PORTB, a_pinID);
				break;
				
			case PORTC_ID:
				if(a_value == LOW)
					CLEAR_BIT(PORTC, a_pinID);
				else
					SET_BIT(PORTC, a_pinID);
				break;
			
			case PORTD_ID:
				if(a_value == LOW)
					CLEAR_BIT(PORTD, a_pinID);
				else
					SET_BIT(PORTD, a_pinID);
				break;
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High
 * or Logic Low. If the input port ID or pin ID are not correct, The function
 * will return Logic Low.
 */
uint8 GPIO_readPin(uint8 a_portID, uint8 a_pinID)
{
	/* Local variable to hold pin value */
	uint8 l_pinValue = 0;
	
	/* Check input validation */
	if(a_portID < NUM_OF_PORTS || a_pinID < NUM_OF_PINS_PER_PORT)
	{
		/* Read the pin value as required */
		switch(a_portID)
		{
			case PORTA_ID:
				l_pinValue = GET_BIT(PINA, a_pinID);
				break;
				
			case PORTB_ID:
				l_pinValue = GET_BIT(PINB, a_pinID);
				break;
				
			case PORTC_ID:
				l_pinValue = GET_BIT(PINC, a_pinID);
				break;
			
			case PORTD_ID:
				l_pinValue = GET_BIT(PIND, a_pinID);
				break;
		}
	}
	
	/* Return the pin value */
	return l_pinValue;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be
 * input pins. If the direction value is PORT_OUTPUT all pins in this port
 * should be output pins. If the input port ID is not correct, The function
 * will not handle the request.
 */
void GPIO_setupPortDirection(uint8 a_portID, uint8 a_direction)
{
	/* Check input validation */
	if(a_portID < NUM_OF_PORTS)
	{
		/* Set up the port direction as required */
		switch(a_portID)
		{
			case PORTA_ID:			
				DDRA = a_direction;
				break;
				
			case PORTB_ID:
				DDRB = a_direction;
				break;
				
			case PORTC_ID:
				DDRC = a_direction;
				break;
			
			case PORTD_ID:
				DDRD = a_direction;
				break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the
 * internal pull-up resistor. If the input port ID is not correct, The function
 * will not handle the request.
 */
void GPIO_writePort(uint8 a_portID, uint8 a_value)
{
	/* Check input validation */
	if(a_portID < NUM_OF_PORTS)
	{
		/* Set the port value as required */
		switch(a_portID)
		{
			case PORTA_ID:			
				PORTA = a_value;
				break;
				
			case PORTB_ID:
				PORTB = a_value;
				break;
				
			case PORTC_ID:
				PORTC = a_value;
				break;
			
			case PORTD_ID:
				PORTD = a_value;
				break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port ID is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 a_portID)
{
	/* Local variable to hold port value */
	uint8 l_portValue = 0;
	
	/* Check input validation */
	if(a_portID < NUM_OF_PORTS)
	{
		/* Read the port value as required */
		switch(a_portID)
		{
			case PORTA_ID:			
				l_portValue =  PINA;
				break;
				
			case PORTB_ID:
				l_portValue = PINB;
				break;
				
			case PORTC_ID:
				l_portValue = PINC;
				break;
			
			case PORTD_ID:
				l_portValue = PIND;
				break;
		}
	}
	
	/* Return the port value */
	return l_portValue;
}
