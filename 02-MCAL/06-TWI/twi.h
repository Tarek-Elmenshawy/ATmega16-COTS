/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : twi.h			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 29-05-2022             		************/
/***********    Description: AVR TWI driver header file     ************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef TWI_H
#define TWI_H

#include "std_types.h"

/***********************************************************************/
/***********				Constants Definitions			  **********/
/***********************************************************************/
#define TWI_START         0x08	/* Start has been sent */
#define TWI_REP_START     0x10	/* Repeated start has been sent */
#define TWI_MT_SLA_W_ACK  0x18	/* Master transmit (slave address + Write request) with received ACK */
#define TWI_MT_SLA_R_ACK  0x40	/* Master transmit (slave address + Read request) with received ACK */
#define TWI_MT_DATA_ACK   0x28	/* Master transmit data and ACK has been received from Slave */
#define TWI_MR_DATA_ACK   0x50	/* Master received data with ACK */
#define TWI_MR_DATA_NACK  0x58	/* Master received data with NACK */

#define TWI_ERROR		(0)
#define TWI_SUCCESS		(1)

/***********************************************************************/
/***********				Types Deceleration				  **********/
/***********************************************************************/

typedef struct{
	
	uint8 TWI_slaveAddress;		/* To select device address */
	uint32 TWI_baudRate;		/* To select TWI baud rate */
	
}TWI_ConfigType;				/* Structure to select TWI configurations */

/***********************************************************************/
/***********				Functions Prototypes			  **********/
/***********************************************************************/

void TWI_init(const TWI_ConfigType * a_config_ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(const uint8 a_sendbyte);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);

#endif	/* TWI_H */
