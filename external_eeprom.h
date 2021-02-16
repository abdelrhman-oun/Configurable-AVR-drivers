/*--------------------------------------------------------------------------------------------------------------------------
 * file name  : eeprom.h
 * Author     : OUN
 * Created on : Dec 12, 2020
 * description: EEPROM header file driver
 --------------------------------------------------------------------------------------------------------------------------*/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/*-----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
#include "i2c.h"

/*----------------------------------------------------DFINATIONS-----------------------------------------------------------*/

#define ERROR 0
#define SUCCESS 1

/*-----------------------------------------------FUNCTION DECLARATIONS-----------------------------------------------------*/

void EEPROM_init(TwiConfig *a_TwiConfig_Ptr);
uint8 EEPROM_writeOneByte(uint16 a_Address, uint8 a_Data);
uint8 EEPROM_readOneByte(uint16 a_Address, uint8 *a_Data_Ptr);
uint8 EEPROM_writeFourBytes(uint16 a_Address, uint32 a_Data);
uint8 EEPROM_readFourBytes(uint16 a_Address, uint32 *a_Data_Ptr);
uint8 EEPROM_writeSixBytes(uint16 a_Address, uint8 *a_Data_Ptr);
uint8 EEPROM_readSixBytes(uint16 a_Address, uint8 *a_Data_Ptr);
uint8 EEPROM_writeBytes(uint16 a_Address, uint8 *a_Data_Ptr, uint8 a_numBytes);
uint8 EEPROM_readBytes(uint16 a_Address, uint8 *a_Data_Ptr, uint8 a_numBytes);

#endif /* EXTERNAL_EEPROM_H_ */
