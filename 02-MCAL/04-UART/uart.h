/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : uart.h			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 25-05-2022             		************/
/***********    Description: AVR UART driver header file    ************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef UART_H
#define UART_H

#include "std_types.h"

/***********************************************************************/
/***********				Constants Definitions			  **********/
/***********************************************************************/
#define UART_5BIT_DATA		(0b00)
#define UART_6BIT_DATA		(0b01)
#define UART_7BIT_DATA		(0b10)
#define UART_8BIT_DATA		(0b11)

#define UART_DISABLE_PARITY	(0b00)
#define UART_EVEN_PARITY	(0b10)
#define UART_ODD_PARITY		(0b11)

#define UART_1STOP_BIT		(0)
#define UART_2STOP_BIT		(1)

/***********************************************************************/
/***********				Types Deceleration				  **********/
/***********************************************************************/

typedef struct{
	
	uint8  UART_dataBits;	/* To select number of data bits */
	uint8  UART_parity;		/* To select parity type checker */
	uint8  UART_stopBits;	/* To select number of stop bits */
	uint32 UART_baudRate;	/* To select UART baud rate */
	
}UART_ConfigType;			/* Structure to hold UART configurations */

/***********************************************************************/
/***********				Functions Prototypes			  **********/
/***********************************************************************/

void UART_init(const UART_ConfigType *a_config_ptr);
void UART_sendByte(const uint8 a_sendByte);
uint8 UART_receiveByte(void);
void UART_sendString(const char *a_string_ptr);
void UART_receiveString(char *a_string_ptr);

#endif	/* UART_H */
