/***********************************************************************/
/***********    Author     : Tarek Elmenshawy       		************/
/***********    File Name  : eeprom.h			     		************/
/***********	Version	   : V0.1							************/
/***********    Date       : 30-05-2022             		************/
/***********    Description: EEPROM driver header file		************/
/***********************************************************************/

/***********************************************************************/
/***********	Guard of file will call one time in .c file    *********/
/***********************************************************************/

#ifndef EEPROM_H
#define EEPROM_H

#include "std_types.h"

/***********************************************************************/
/***********				Functions Prototypes			  **********/
/***********************************************************************/

uint8 EEPROM_wtiteByte(uint16 a_locationAddress, uint8 a_writeByte);
uint8 EEPROM_readByte(uint16 a_locationAddress, uint8 *a_readByte);

#endif