/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : eeprom.c			     		************/
/***********	Version	   : V0.1							************/
/***********    Date       : 230-05-2022             		************/
/***********    Description: EEPROM driver source file      ************/
/***********************************************************************/

#include "eeprom.h"
#include "bit_math.h"
#include "twi.h"
#include <avr/io.h>

/***********************************************************************/
/***********				Functions Definitions			  **********/
/***********************************************************************/

uint8 EEPROM_writeByte(uint16 a_locationAddress, uint8 a_writeByte)
{
	/* Send start condition bit to start communication */
	TWI_start();
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_START)
		return TWI_ERROR;
	
	/* Send device address with write request */
	TWI_writeByte((uint8)(0xA0 | ((a_locationAddress >> 7) & 0x000E)));
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return TWI_ERROR;
	
	/* Send location address to be written into it */
	TWI_writeByte((uint8)(a_locationAddress & 0x00FF));
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_ERROR;
	
	/* Send data to be written */
	TWI_writeByte(a_writeByte);
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_ERROR;
	
	/* Send stop condition bit to end communication */
	TWI_stop();
	
	/* Return success if everything goes correctly */
	return TWI_SUCCESS;
}

uint8 EEPROM_readByte(uint16 a_locationAddress, uint8 * a_readByte)
{
	/* Send start condition bit to start communication */
	TWI_start();
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_START)
		return TWI_ERROR;
	
	/* Send device address with write request */
	TWI_writeByte((uint8)(0xA0 | ((a_locationAddress >> 7) & 0x000E)));
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return TWI_ERROR;
	
	/* Send location address to be read */
	TWI_writeByte((uint8)(a_locationAddress & 0x00FF));
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_ERROR;
	
	/* Send repeated start condition to change data transfer direction */
	TWI_start();
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_REP_START)
		return TWI_ERROR;
	
	/* Send device address with read request */
	TWI_writeByte((uint8)(0xA1 | ((a_locationAddress >> 7) & 0x000E)));
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_MT_SLA_R_ACK)
		return TWI_ERROR;
	
	/* Read data from required location */
	*a_readByte = TWI_readByteWithNACK();
	/* Return error if an error happened */
	if(TWI_getStatus() != TWI_MR_DATA_NACK)
		return TWI_ERROR;
	
	/* Send stop condition bit to end communication */
	TWI_stop();
	
	/* Return success if everything goes correctly */
	return TWI_SUCCESS;
}
