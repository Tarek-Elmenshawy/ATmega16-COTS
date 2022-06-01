/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : Llcd.c			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: LCD driver source file    		************/
/***********************************************************************/

#include "bit_math.h"
#include "gpio.h"
#include "lcd.h"
#include <util/delay.h>

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

/*
 * Description:
 * Initialize the LCD.
 */
void LCD_init(void)
{
	/* Set up RS pin as output pin */
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	/* Set up RW pin as output pin */
	GPIO_setupPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, PIN_OUTPUT);
	/* Set up EN pin as output pin */
	GPIO_setupPinDirection(LCD_EN_PORT_ID, LCD_EN_PIN_ID, PIN_OUTPUT);

	#if 	(LCD_DATA_MODE == LCD_8_BIT_2_LINE_MODE)
		/* Set up DATA pins as output pins */
		GPIO_setupPortDirection(LCD_DATA_PORT_ID, PIN_OUTPUT);
		/* delay for some time after power on (mentioned in datasheet) */
		_delay_ms(20);
		/* Send command to select function set: 8-Bit, 2 Line, 5x7 Dots */
		LCD_sendCommand(LCD_8_BIT_2_LINE_MODE);
	#elif	(LCD_DATA_MODE == LCD_4_BIT_2_LINE_MODE)
		/* Set up DATA pins as output pins */
		GPIO_setupPinDirection(LCD_D4_PIN, PIN_OUTPUT);
		GPIO_setupPinDirection(LCD_D5_PIN, PIN_OUTPUT);
		GPIO_setupPinDirection(LCD_D6_PIN, PIN_OUTPUT);
		GPIO_setupPinDirection(LCD_D7_PIN, PIN_OUTPUT);
		/* delay for some time after power on (mentioned in data sheet) */
		_delay_ms(20);
		LCD_sendCommand(LCD_RETURN_HOME);
		/* Send command to select function set: 4-Bit, 2 Line, 5x7 Dots */
		LCD_sendCommand(LCD_4_BIT_2_LINE_MODE);
	#else
		#error"LCD_DATA_MODE is not configured correctly"
	#endif
	
	/* Send command to set Display on Cursor off */
	LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_OFF);
	/* Send command to clear display */
	LCD_sendCommand(LCD_CLEAR);
	/* Send command to set entry mode */
	LCD_sendCommand(LCD_ENTRY_MODE);
}

/*
 * Description:
 * Send the required command to the LCD.
 */
void LCD_sendCommand(uint8 a_command)
{
	/* Set RS pin Low to send command */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOW);
	/* Set RW pin Low to write on LCD */
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOW);
	/* For address setup time tas = 50ns */
	_delay_ms(1);
	
	#if 	(LCD_DATA_MODE == LCD_8_BIT_2_LINE_MODE)
		/* Set Enable pin High to start writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 1);
		/* For enable setup time tpw - tdsw = 290 - 100ns */
		_delay_ms(1);
		
		/* Write command on data pins */
		GPIO_writePort(LCD_DATA_PORT_ID, a_command);
		/* For data setup time tdsw = 100ns*/
		_delay_ms(1);
		
		/* Set Enable pin Low to end writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 0);
		/* For data hold time th = 13ns*/
		_delay_ms(1);
	#elif	(LCD_DATA_MODE == LCD_4_BIT_2_LINE_MODE)
		/* Set Enable pin High to start writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 1);
		/* For enable setup time tpw - tdsw = 290 - 100ns */
		_delay_ms(1);
		
		/* Write highest command bits on data pins */
		GPIO_writePin(LCD_D4_PIN, GET_BIT(a_command, 4));
		GPIO_writePin(LCD_D5_PIN, GET_BIT(a_command, 5));
		GPIO_writePin(LCD_D6_PIN, GET_BIT(a_command, 6));
		GPIO_writePin(LCD_D7_PIN, GET_BIT(a_command, 7));
		/* For data setup time tdsw = 100ns*/
		_delay_ms(1);
		
		/* Set Enable pin Low to end writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 0);
		/* For data hold time th = 13ns*/
		_delay_ms(1);
		
		/* Set Enable pin High to start writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 1);
		/* For enable setup time tpw - tdsw = 290 - 100ns */
		_delay_ms(1);
		
		/* Write highest command bits on data pins */
		GPIO_writePin(LCD_D4_PIN, GET_BIT(a_command, 0));
		GPIO_writePin(LCD_D5_PIN, GET_BIT(a_command, 1));
		GPIO_writePin(LCD_D6_PIN, GET_BIT(a_command, 2));
		GPIO_writePin(LCD_D7_PIN, GET_BIT(a_command, 3));
		/* For data setup time tdsw = 100ns*/
		_delay_ms(1);
		
		/* Set Enable pin Low to end writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 0);
		/* For data hold time th = 13ns*/
		_delay_ms(1);
	#else
		#error"LCD_DATA_MODE is not configured correctly"
	#endif

}

/*
 * Description:
 * Display the required character on the LCD.
 */
void LCD_displayCharacter(uint8 a_data)
{
	/* Set RS pin High to send data */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, HIGH);
	/* Set RW pin Low to write on LCD */
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOW);
	/* For address setup time tas = 50ns */
	_delay_ms(1);
	
	#if 	(LCD_DATA_MODE == LCD_8_BIT_2_LINE_MODE)
		/* Set Enable pin High to start writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 1);
		/* For enable setup time tpw - tdsw = 290 - 100ns */
		_delay_ms(1);
		
		/* Write data on data pins */
		GPIO_writePort(LCD_DATA_PORT_ID, a_data);
		/* For data setup time tdsw = 100ns*/
		_delay_ms(1);
		
		/* Set Enable pin Low to end writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 0);
		/* For data hold time th = 13ns*/
		_delay_ms(1);
	#elif	(LCD_DATA_MODE == LCD_4_BIT_2_LINE_MODE)
		/* Set Enable pin High to start writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 1);
		/* For enable setup time tpw - tdsw = 290 - 100ns */
		_delay_ms(1);
		
		/* Write highest data bits on data pins */
		GPIO_writePin(LCD_D4_PIN, GET_BIT(a_data, 4));
		GPIO_writePin(LCD_D5_PIN, GET_BIT(a_data, 5));
		GPIO_writePin(LCD_D6_PIN, GET_BIT(a_data, 6));
		GPIO_writePin(LCD_D7_PIN, GET_BIT(a_data, 7));
		/* For data setup time tdsw = 100ns*/
		_delay_ms(1);
		
		/* Set Enable pin Low to end writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 0);
		/* For data hold time th = 13ns*/
		_delay_ms(1);
		
		/* Set Enable pin High to start writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 1);
		/* For enable setup time tpw - tdsw = 290 - 100ns */
		_delay_ms(1);
		
		/* Write highest data bits on data pins */
		GPIO_writePin(LCD_D4_PIN, GET_BIT(a_data, 0));
		GPIO_writePin(LCD_D5_PIN, GET_BIT(a_data, 1));
		GPIO_writePin(LCD_D6_PIN, GET_BIT(a_data, 2));
		GPIO_writePin(LCD_D7_PIN, GET_BIT(a_data, 3));
		/* For data setup time tdsw = 100ns*/
		_delay_ms(1);
		
		/* Set Enable pin Low to end writing sequence */
		GPIO_writePin(LCD_EN_PORT_ID, LCD_EN_PIN_ID, 0);
		/* For data hold time th = 13ns*/
		_delay_ms(1);
	#else
		#error"LCD_DATA_MODE is not configured correctly"
	#endif
}

/*
 * Description:
 * Display the required string on the LCD.
 */
void LCD_displayString(const char *a_string_ptr)
{
	/* Loop through string and send it character by character */
	while(*a_string_ptr != '\0')
	{
		LCD_displayCharacter((uint8)*a_string_ptr++);
	}
}

/*
 * Description:
 * Move the cursor to a specified row and column index on the LCD.
 */
void LCD_moveCursor(uint8 a_row, uint8 a_column)
{
	uint8 l_address = 0;
	
	/* Calculate address depends on row and column */
	switch(a_row)
	{
		case 0: l_address = a_column;			break;
		case 1: l_address = a_column + 0x40;	break;
		case 2: l_address = a_column + 0x10;	break;
		case 3: l_address = a_column + 0x50;	break;
	}
	
	/* /send command to set cursor as required */
	LCD_sendCommand(LCD_CURSOR_LOCATION | l_address);
	
}

/*
 * Description:
 * Display the required string in a specified row and column index on the LCD.
 */
void LCD_displayStringRowColumn(uint8 a_row, uint8 a_column, const char *a_string_ptr)
{
	/* Set cursor as required */
	LCD_moveCursor(a_row, a_column);
	
	/* Display string in required position */
	LCD_displayString(a_string_ptr);
}

/*
 * Description:
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	/* Send command to clear display */
	LCD_sendCommand(LCD_CLEAR);
}

/*
 * Description:
 * Display the required decimal value on the LCD.
 */
void LCD_integerToString(sint32 a_data)
{
	char l_buffer[16] = {0};
	uint8 l_length = 0;
	sint32 l_temp = a_data;
	
	if(a_data == 0)
	{
		LCD_displayCharacter('0');
		return;
	}

	/* Get the integer digits number */
	while(l_temp != 0)
	{
		l_length++;
		l_temp /= 10;
	}
	
	/* Insert digits into buffer */
	for(l_temp = 0; l_temp < l_length; l_temp++)
	{
		l_buffer[l_length - 1 - l_temp] = '0' + (a_data % 10);
		a_data /= 10;
	}
	
	/* Display string on LCD */
	LCD_displayString(l_buffer);
}
