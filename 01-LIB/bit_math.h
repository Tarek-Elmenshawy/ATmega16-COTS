/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : bit_math.h			     		************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: Bit math macros header file    ************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

/***********************************************************************/
/***********				Macros Definitions			      **********/
/***********************************************************************/

#define SET_BIT(VAR, BIT)		(VAR |=  (1 << (BIT)))
#define CLEAR_BIT(VAR, BIT)		(VAR &= ~(1 << (BIT)))
#define GET_BIT(VAR, BIT)		(((VAR) >> (BIT)) & 1)
#define TOGGLE_BIT(VAR, BIT)	(VAR ^=  (1 << (BIT)))

#define BIT_IS_SET(VAR, BIT) 	(VAR & (1 << (BIT)))
#define BIT_IS_CLEAR(VAR, BIT) 	(!(VAR & (1 << (BIT))))

#define ROR(VAR, NUM)			(VAR = (VAR << (NUM)) | (VAR >> ((sizeof(VAR) * 8) - (NUM))))
#define ROL(VAR, NUM)			(VAR = (VAR >> (NUM)) | (VAR << ((sizeof(VAR) * 8) - (NUM))))

#endif
