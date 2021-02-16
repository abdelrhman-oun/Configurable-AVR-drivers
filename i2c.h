/*--------------------------------------------------------------------------------------------------------------------------
 * file name  : i2c.h
 * Author     : OUN
 * Created on : Dec 12, 2020
 * description: I2C header file driver
 --------------------------------------------------------------------------------------------------------------------------*/


#ifndef I2C_H_
#define I2C_H_

/*-----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*----------------------------------------------------DFINATIONS-----------------------------------------------------------*/

/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave


/*-------------------------------------------------TYPES DECLARATION-------------------------------------------------------*/


typedef struct
{
	uint32 s_clockFreq;
	uint8 s_slaveAddress;
}TwiConfig;


/*-----------------------------------------------FUNCTION DECLARATIONS-----------------------------------------------------*/

void TWI_init(const TwiConfig *a_TwiConfig_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 a_data);
uint8 TWI_readWithACK(void); //read with send Ack
uint8 TWI_readWithNACK(void); //read without send Ack
uint8 TWI_getStatus(void);


#endif /* I2C_H_ */
