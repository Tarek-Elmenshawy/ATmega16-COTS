/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : uart.c			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 25-05-2022             		************/
/***********    Description: AVR UART driver source file    ************/
/***********************************************************************/

#include "uart.h"
#include "bit_math.h"
#include <avr/io.h>

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

void UART_init(const UART_ConfigType *a_config_ptr)
{
	/* Calculate UBRR value of required baud rate */
	uint16 l_UBRR = (uint16)((F_CPU / (8UL * a_config_ptr->UART_baudRate)) - 1);
	
	/* Reduce the divisor of the baud rate divider from 16 to 8 */
	UCSRA  = (1 << U2X);
	
	/******************	  UART Frame Configurations	  ******************/
	/* Select parity mode as required */
	UCSRC  = (1 << URSEL) | ((a_config_ptr->UART_parity) << UPM0);
	
	/* Select number of stop bits as required */
	UCSRC |= (1 << URSEL) | ((a_config_ptr->UART_stopBits) << USBS);
	
	/* Select number of frame data bits as required */
	UCSRC |= (1 << URSEL) | ((a_config_ptr->UART_dataBits) << UCSZ0);
	/*******************************************************************/
	
	/* Select UART baud rate as required */
	UBRRL  = (uint8)l_UBRR;
	UBRRH  = (uint8)(l_UBRR >> 8);
	
	/* Enable UART transmitter and receiver */
	UCSRB = (1 << RXEN) | (1 << TXEN);
}

void UART_sendByte(const uint8 a_sendByte)
{
	/* Wait for empty transmit buffer */
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	
	/* Put data into transmit buffer, send the data */
	UDR = a_sendByte;
}

uint8 UART_receiveByte(void)
{
	/* Wait for data to be received */
	while(BIT_IS_CLEAR(UCSRA,RXC));
	
	/* Get and return data from received buffer */
	return UDR;
}

void UART_sendString(const char *a_string_ptr)
{
	/* Loop through string, send it byte by byte */
	while(*a_string_ptr != '\0')
	{
		UART_sendByte((uint8)(*a_string_ptr));
		a_string_ptr++;
	}
	
	/* Send terminator character to specify the end of string */
	UART_sendByte('#');
}

void UART_receiveString(char *a_string_ptr)
{
	uint8 l_counter = 0;
	
	/* Receive the first character */
	a_string_ptr[l_counter] = UART_receiveByte();
	
	/* Receive characters up to '#' character */
	while(a_string_ptr[l_counter] != '#')
	{
		l_counter++;
		a_string_ptr[l_counter] = (char)UART_receiveByte();
	}
	
	/* Replace '#' with '\0' to make it normal string */
	a_string_ptr[l_counter] = '\0';
}

