/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : lcd.h			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: LCD driver header file    		************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef LCD_H
#define LCD_H

#include "std_types.h"

/**********************************************************************/
/***********				Constants Definitions			  *********/
/**********************************************************************/

#define LCD_8_BIT_2_LINE_MODE			0x38
#define LCD_4_BIT_2_LINE_MODE			0x28
#define LCD_DISPLAY_ON_CURSOR_OFF		0X0C
#define LCD_CLEAR						0x01
#define LCD_RETURN_HOME					0x02
#define LCD_ENTRY_MODE					0x06
#define LCD_CURSOR_LOCATION				0x80

#define LCD_DATA_MODE					LCD_8_BIT_2_LINE_MODE

#define LCD_RS_PORT_ID  				PORTD_ID
#define LCD_RS_PIN_ID   				PIN0_ID

#define LCD_RW_PORT_ID  				PORTD_ID
#define LCD_RW_PIN_ID   				PIN1_ID

#define LCD_EN_PORT_ID  				PORTD_ID
#define LCD_EN_PIN_ID   				PIN2_ID


#if		(LCD_DATA_MODE == LCD_8_BIT_2_LINE_MODE)
	
	#define LCD_DATA_PORT_ID			PORTC_ID
	
#elif	(LCD_DATA_MODE == LCD_4_BIT_2_LINE_MODE)
	
	#define LCD_D4_PIN					PORTC_ID,PIN4_ID
	#define LCD_D5_PIN					PORTC_ID,PIN5_ID
	#define LCD_D6_PIN					PORTC_ID,PIN6_ID
	#define LCD_D7_PIN					PORTC_ID,PIN7_ID
	
#else
	#error"LCD_DATA_MODE is not configured correctly"
#endif

/**********************************************************************/
/***********				Functions Prototypes			  *********/
/**********************************************************************/

void LCD_init(void);
void LCD_sendCommand(uint8 a_command);
void LCD_displayCharacter(uint8 a_data);
void LCD_displayString(const char *a_string_ptr);
void LCD_moveCursor(uint8 a_row, uint8 a_column);
void LCD_displayStringRowColumn(uint8 a_row, uint8 a_column, const char *a_string_ptr);
void LCD_clearScreen(void);
void LCD_integerToString(sint32 a_data);

#endif	/* LCD_H */
