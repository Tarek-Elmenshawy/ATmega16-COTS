/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : gpio.h			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: AVR GPIO driver header file    ************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef GPIO_H
#define GPIO_H

#include "std_types.h"

/***********************************************************************/
/***********				Constants Definitions			  **********/
/***********************************************************************/

#define NUM_OF_PORTS				4
#define NUM_OF_PINS_PER_PORT		8

/* Port IDs */
#define PORTA_ID					0
#define PORTB_ID					1
#define PORTC_ID					2
#define PORTD_ID					3

/* Pin IDs */
#define PIN0_ID						0
#define PIN1_ID						1
#define PIN2_ID						2
#define PIN3_ID						3
#define PIN4_ID						4
#define PIN5_ID						5
#define PIN6_ID						6
#define PIN7_ID						7

/* Pin direction states */
#define PIN_INPUT					0
#define PIN_OUTPUT					1

/* Port direction states */
#define PORT_INPUT					0x00
#define PORT_OUTPUT					0xFF

#define HIGH						1
#define LOW							0

/***********************************************************************/
/***********				Functions Prototypes			  **********/
/***********************************************************************/

void  GPIO_setupPinDirection(uint8 a_portID, uint8 a_pinID, uint8 a_direction);
void  GPIO_writePin(uint8 a_portID, uint8 a_pinID, uint8 a_value);
uint8 GPIO_readPin(uint8 a_portID, uint8 a_pinID);
void  GPIO_setupPortDirection(uint8 a_portID, uint8 a_direction);
void  GPIO_writePort(uint8 a_portID, uint8 a_value);
uint8 GPIO_readPort(uint8 a_portID);

#endif	/* GPIO_H */
