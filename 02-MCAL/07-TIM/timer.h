/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : timer.h			     		************/
/***********	Version	   : V0.1							************/
/***********    Date       : 06-06-2022             		************/
/***********    Description: AVR TIMER driver header file   ************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include "std_types.h"

/***********************************************************************/
/***********				Constants Definitions			  **********/
/***********************************************************************/

#define TIMER0_ID				0
#define TIMER1_ID				1
#define TIMER2_ID				2

#define TIMER_OVF_MODE			0
#define TIMER_CTC_MODE			1

#define TIMER0_CLK_NO			(0b000)
#define TIMER0_CLK_FCPU			(0b001)
#define TIMER0_CLK_FCPU_BY_8	(0b010)
#define TIMER0_CLK_FCPU_BY_64	(0b011)
#define TIMER0_CLK_FCPU_BY_256	(0b100)
#define TIMER0_CLK_FCPU_BY_1024	(0b101)

#define TIMER1_CLK_NO			(0b000)
#define TIMER1_CLK_FCPU			(0b001)
#define TIMER1_CLK_FCPU_BY_8	(0b010)
#define TIMER1_CLK_FCPU_BY_64	(0b011)
#define TIMER1_CLK_FCPU_BY_256	(0b100)
#define TIMER1_CLK_FCPU_BY_1024	(0b101)

#define TIMER2_CLK_NO			(0b000)
#define TIMER2_CLK_FCPU			(0b001)
#define TIMER2_CLK_FCPU_BY_8	(0b010)
#define TIMER2_CLK_FCPU_BY_32	(0b011)
#define TIMER2_CLK_FCPU_BY_64	(0b100)
#define TIMER2_CLK_FCPU_BY_128	(0b101)
#define TIMER2_CLK_FCPU_BY_256	(0b110)
#define TIMER2_CLK_FCPU_BY_1024	(0b111)

/***********************************************************************/
/***********				Types Deceleration				  **********/
/***********************************************************************/

typedef struct{
	
	uint8  TIMER_ID;				/* To select which timer[0:2] */
	uint8  TIMER_mode;				/* To select timer mode [OVF, CTC] */
	uint8  TIMER_clock;				/* To select timer pre-scaler */
	uint16 TIMER_TCNTinitialValue;	/* To select timer counter initial value */
	uint16 TIMER_OCRvalue;			/* To select  */
	
}TIMER_ConfigType; 					/* Structure to hold UART configurations */


/***********************************************************************/
/***********				Functions Prototypes			  **********/
/***********************************************************************/

void TIMER_init(const TIMER_ConfigType *a_config_ptr);
void TIMER_setCallBack(const uint8 a_timerID, void (*a_callBack_ptr)(void));
void TIMER_deInit(const uint8 a_timerID);


#endif	/* TIMER_H */
