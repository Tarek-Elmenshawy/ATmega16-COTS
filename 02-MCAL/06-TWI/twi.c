/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : twi.c			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 29-05-2022             		************/
/***********    Description: AVR TWI driver source file     ************/
/***********************************************************************/

#include "twi.h"
#include "bit_math.h"
#include <avr/io.h>

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

void TWI_init(const TWI_ConfigType * a_config_ptr)
{
	/* Calculate TWBR value depends on the required baud rate */
	/* with TWIPS 00 */
	TWBR = (uint8)(((F_CPU/a_config_ptr->TWI_baudRate)-16)/2);
	
	/* Clear TWI status register and select 1 pre-scaler */
	TWSR = 0x00;
	
	/* Set slave address */
	TWAR = a_config_ptr->TWI_slaveAddress;
	
	/* Enable TWI peripheral */
	TWCR = (1 << TWEN);
}

void TWI_start(void)
{
	/*
	 * The TWINT Flag must be cleared by software by writing
	 * a logic one to it. Note that this flag is not automatically
	 * cleared by hardware when executing the interrupt routine.
	 * Also note that clearing this flag starts the operation of the TWI,
	 * so all accesses to the TWI Address Register (TWAR),
	 * TWI Status Register (TWSR), and TWI Data Register (TWDR)
	 * must be complete before clearing this flag.
	 */
	 
	/* Send start condition on SDA line */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	/* Wait for flag is set, indicating that START has been transmitted */
	while(BIT_IS_CLEAR(TWCR, TWINT));
	
}

void TWI_stop(void)
{
	/*
	 * The TWINT Flag must be cleared by software by writing
	 * a logic one to it. Note that this flag is not automatically
	 * cleared by hardware when executing the interrupt routine.
	 * Also note that clearing this flag starts the operation of the TWI,
	 * so all accesses to the TWI Address Register (TWAR),
	 * TWI Status Register (TWSR), and TWI Data Register (TWDR)
	 * must be complete before clearing this flag.
	 */
	 
	/* Send stop condition on SDA line */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	
}

void TWI_writeByte(const uint8 a_sendbyte)
{
	/* Load data to be sent in data register */
	TWDR = a_sendbyte;
	
	/*
	 * The TWINT Flag must be cleared by software by writing
	 * a logic one to it. Note that this flag is not automatically
	 * cleared by hardware when executing the interrupt routine.
	 * Also note that clearing this flag starts the operation of the TWI,
	 * so all accesses to the TWI Address Register (TWAR),
	 * TWI Status Register (TWSR), and TWI Data Register (TWDR)
	 * must be complete before clearing this flag.
	 */
	 
	/* Clear interrupt flag and start transmitting */
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	/* Wait for flag is set */
	while(BIT_IS_CLEAR(TWCR, TWINT));
	
}

uint8 TWI_readByteWithACK(void)
{
	/*
	 * The TWINT Flag must be cleared by software by writing
	 * a logic one to it. Note that this flag is not automatically
	 * cleared by hardware when executing the interrupt routine.
	 * Also note that clearing this flag starts the operation of the TWI,
	 * so all accesses to the TWI Address Register (TWAR),
	 * TWI Status Register (TWSR), and TWI Data Register (TWDR)
	 * must be complete before clearing this flag.
	 */
	 
	/* Clear interrupt flag, start receiving then send ACK */
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	
	/* Wait for flag is set */
	while(BIT_IS_CLEAR(TWCR, TWINT));
	
	/* Return data */
	return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
	 * The TWINT Flag must be cleared by software by writing
	 * a logic one to it. Note that this flag is not automatically
	 * cleared by hardware when executing the interrupt routine.
	 * Also note that clearing this flag starts the operation of the TWI,
	 * so all accesses to the TWI Address Register (TWAR),
	 * TWI Status Register (TWSR), and TWI Data Register (TWDR)
	 * must be complete before clearing this flag.
	 */
	 
	/* Clear interrupt flag, start receiving then send NACK */
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	/* Wait for flag is set */
	while(BIT_IS_CLEAR(TWCR, TWINT));
	
	/* Return data */
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	/* Return the status bits in TWSR register */
	return (TWSR & 0xF8);
}

