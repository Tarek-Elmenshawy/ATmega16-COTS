/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : keypad.h			     		************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: Keypad driver header file	    ************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef KEYPAD_H
#define KEYPAD_H

#include "std_types.h"

/***********************************************************************/
/***********				Constants Definitions			  **********/
/***********************************************************************/

/* Keypad size configuration */
#define KEYPAD_COLS_NUM				3
#define KEYPAD_ROWS_NUM				4

/* Keypad port configuration */
#define KEYPAD_PORT_ID				PORTA_ID
#define KEYPAD_FIRST_ROW_PIN_ID		PIN0_ID
#define KEYPAD_FIRST_COL_PIN_ID		PIN4_ID

/* Keypad button logic configuration */
#define KEYPAD_BUTTON_PRESSED		LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED		LOGIC_HIGH


/***********************************************************************/
/***********				Functions Prototypes    		   *********/
/***********************************************************************/
uint8 KEYPAD_getPressedKey(void);

#endif	/* KEYPAD_H */
