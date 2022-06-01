/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : spi.c			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 26-05-2022             		************/
/***********    Description: AVR SPI driver source file     ************/
/***********************************************************************/

#include "spi.h"
#include "bit_math.h"
#include <avr/io.h>

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

void SPI_initMaster(void)
{
	/* Configure SS, MOSI, SCK as output pins */
	DDRB |= (1 << PD4) | (1 << PD5) | (1 << PD7);
	
	/* Configure MISO as input pin */
	DDRB &= ~(1 << PD6);
	
	/* Enable SPI as master with MSB data order, CPOL = 0, CPHA = 0 */
	SPCR  = (1 << SPE) | (1 << MSTR);
	
	/* SPI frequency = fosc / 4 */
	SPSR &= ~(1 << SPI2X);
}

void SPI_initSlave(void)
{
	/* Configure SS, MOSI, SCK as input pins */
	DDRB &= ~((1 << PD4) | (1 << PD5) | (1 << PD7));
	
	/* Configure MISO as output pin */
	DDRB |= (1 << PD6);
	
	/* Enable SPI as s;ave with MSB data order, CPOL = 0, CPHA = 0 */
	SPCR  = (1 << SPE);
}

uint8 SPI_sendReceiveByte(uint8 a_sendByte)
{
	/* Write send byte in the data buffer to start transmitting */
	SPDR = a_sendByte;
	
	/* Wait for data sending and receving is done */
	while(BIT_IS_CLEAR(SPSR, SPIF));
	
	/* Get and return data from received buffer */
	return SPDR;
}

void SPI_sendString(const char *a_string_ptr)
{
	/* Loop through string, send it byte by byte */
	while(*a_string_ptr != '\0')
	{
		SPI_sendReceiveByte((uint8)(*a_string_ptr));
		a_string_ptr++;
	}
	
	/* Send terminator character to specify the end of string */
	SPI_sendReceiveByte('#');
}

void SPI_receiveString(char * a_string_ptr)
{
	uint8 l_counter = 0;
	
	/* Receive the first character */
	a_string_ptr[l_counter] = SPI_sendReceiveByte(SPI_DUMMY_BYTE);
	
	/* Receive characters up to '#' character */
	while(a_string_ptr[l_counter] != '#')
	{
		l_counter++;
		a_string_ptr[l_counter] = (char)SPI_sendReceiveByte(SPI_DUMMY_BYTE);
	}
	
	/* Replace '#' with '\0' to make it normal string */
	a_string_ptr[l_counter] = '\0';
}

