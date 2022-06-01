/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : icu.h			     			************/
/***********	Version	   : V0.1							************/
/***********    Date       : 23-05-2022             		************/
/***********    Description: AVR ICU driver header file    	************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef ICU_H
#define ICU_H

#include "std_types.h"

/***********************************************************************/
/***********				Constants Definitions			  **********/
/***********************************************************************/
#define ICU_NO_CLOCK		(0b000)
#define ICU_F_CPU_CLOCK 	(0b001)
#define ICU_F_CPU_8 		(0b010)
#define ICU_F_CPU_64 		(0b011)
#define ICU_F_CPU_256 		(0b100)
#define ICU_F_CPU_1024 		(0b101)

#define ICU_RISING_EDGE		1
#define ICU_FALLING_EDGE	0

/***********************************************************************/
/***********				Types Deceleration				  **********/
/***********************************************************************/

typedef struct{
	
	uint8 ICU_TimerClock;		/* To select timer pre-scaler */
	uint8 ICU_Edge;				/* To select edge detection */
	
}ICU_ConfigType;				/* Structure deceleration for select ICU configurations*/


/***********************************************************************/
/***********				Functions Prototypes			  **********/
/***********************************************************************/

void ICU_init(const ICU_ConfigType *a_cofig_ptr);
void ICU_setCallBack(void (*a_callBack_ptr)(void));
void ICU_setEdgeDetection(const uint8 a_edgeType);
void ICU_clearTimerValue(void);
void ICU_deInit(void);
uint16 ICU_getInputCaptureValue(void);


#endif	/* ICU_H */




