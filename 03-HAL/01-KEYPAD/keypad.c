/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : keypad.c		     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: Keypad driver source file	    ************/
/***********************************************************************/

#include "keypad.h"
#include "bit_math.h"
#include "gpio.h"

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

#if	KEYPAD_COLS_NUM == 3
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_pressedButton)
{
	uint8 l_adjustedNumber;
	
	switch(a_pressedButton)
	{
		case 10: l_adjustedNumber = '*';				break;
		case 11: l_adjustedNumber = 0;					break;
		case 12: l_adjustedNumber = '*';				break;
		default: l_adjustedNumber = a_pressedButton;	break;
	}
	
	return l_adjustedNumber;
}
#endif

#if	KEYPAD_COLS_NUM == 4
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_pressedButton)
{
	uint8 l_adjustedNumber;
	
	switch(a_pressedButton)
	{
		case  1: l_adjustedNumber = 7;		break;
		case  2: l_adjustedNumber = 8;		break;
		case  3: l_adjustedNumber = 9;		break;
		case  4: l_adjustedNumber = '/';	break;
		case  5: l_adjustedNumber = 4;		break;
		case  6: l_adjustedNumber = 5;		break;
		case  7: l_adjustedNumber = 6;		break;
		case  8: l_adjustedNumber = '*';	break;
		case  9: l_adjustedNumber = 1;		break;
		case 10: l_adjustedNumber = 2;		break;
		case 11: l_adjustedNumber = 3;		break;
		case 12: l_adjustedNumber = '-';	break;
		case 13: l_adjustedNumber = 13;		break;
		case 14: l_adjustedNumber = 0;		break;
		case 15: l_adjustedNumber = '=';	break;
		case 16: l_adjustedNumber = '+';	break;
	}
	
	return l_adjustedNumber;
}
#endif

/*
 * Description:
 * Get the keypad pressed button.
 */
uint8 KEYPAD_getPressedKey(void)
{
	uint8 l_row, l_col;
	uint8 l_keypadPortValue;
	
	/* Scan the keypad till a pressed button is being found */
	while(1)
	{
		for(l_col = 0; l_col < KEYPAD_COLS_NUM; l_col++)
		{
			/* For each loop, set up keypad port as input except a target column */
			GPIO_setupPortDirection(KEYPAD_PORT_ID, PORT_INPUT);
			GPIO_setupPinDirection(KEYPAD_PORT_ID, l_col + KEYPAD_FIRST_COL_PIN_ID, PIN_OUTPUT);
			
			/* Set column value as required logic level */
			#if 	KEYPAD_BUTTON_PRESSED == LOGIC_LOW
				l_keypadPortValue = ~(1 << (l_col + KEYPAD_FIRST_COL_PIN_ID));
			#elif	KEYPAD_BUTTON_PRESSED == LOGIC_HIGH
				l_keypadPortValue =  (1 << (l_col + KEYPAD_FIRST_COL_PIN_ID));
			#else
				#error "KEYPAD_BUTTON_PRESSED is not configured correctly"
			#endif
			
			GPIO_writePort(KEYPAD_PORT_ID, l_keypadPortValue);
			
			/* Loop through rows and check its value */
			for(l_row = 0; l_row < KEYPAD_ROWS_NUM; l_row++)
			{
				if(GPIO_readPin(KEYPAD_PORT_ID, l_row + KEYPAD_FIRST_ROW_PIN_ID) == KEYPAD_BUTTON_PRESSED)
				{
					#if		KEYPAD_COLS_NUM == 3
						return KEYPAD_4x3_adjustKeyNumber((l_row * KEYPAD_COLS_NUM) + l_col + 1);
					#elif	KEYPAD_COLS_NUM == 4
						return KEYPAD_4x4_adjustKeyNumber((l_row * KEYPAD_COLS_NUM) + l_col + 1);
					#else
						#error "KEYPAD_COLS_NUM is not configured correctly"
					#endif
				}
			}
		}
	}
}
