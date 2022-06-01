/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : dc_motor.h			     		************/
/***********	Version	   : V0.1							************/
/***********    Date       : 24-05-2022             		************/
/***********    Description: DC Motor driver header file    ************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef DC_NOTOR_H
#define DC_NOTOR_H

#include "std_types.h"

/***********************************************************************/
/***********				Constants Definitions			  **********/
/***********************************************************************/

#define DC_INT1_PORT	PORTB_ID
#define DC_INT1_PIN		PIN0_ID

#define DC_INT2_PORT	PORTB_ID
#define DC_INT2_PIN		PIN1_ID

#define DC_EN_PORT		PORTB_ID
#define DC_EN_PIN		PIN3_ID

#define DC_MOTOR_STOP	0
#define DC_MOTOR_CW		1
#define DC_MOTOR_CCW	2

/***********************************************************************/
/***********				Functions Prototypes			  **********/
/***********************************************************************/

void DC_MOTOR_init(void);
void DC_MOTOR_rotate(uint8 a_state,uint8 a_speed);

#endif
