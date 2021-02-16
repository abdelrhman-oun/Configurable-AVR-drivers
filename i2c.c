/*--------------------------------------------------------------------------------------------------------------------------
 * file name  : i2c.c
 * Author     : OUN
 * Created on : Dec 12, 2020
 * description: I2C source file driver
 --------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include "i2c.h"


/*-----------------------------------------------FUNCTION DECLARATIONS-----------------------------------------------------*/

void TWI_init(const TwiConfig *a_TwiConfig_Ptr){

	uint8 prescaler = 1; /* = 1 to start with TWS0 = 0 TWPS1 = 0 */
	uint32 twbr = 0;
	uint8 twps = 0;   /*GETTING TWBR and TWSR value from clock freq entered by user*/
	while(prescaler<=64){
		twbr = (((F_CPU/(a_TwiConfig_Ptr->s_clockFreq))-16)/(2*(prescaler)));
		if(twbr > 255){
			prescaler *= 4;
			twps += 1;
		}
		else{
			break;
		}
	}
	TWBR = (uint8)twbr;
	TWSR = (TWSR & 0xFC) | ( twps & 0x03);



	/* Two Wire Bus address my address if any master device want to call me (used in case this MC is a slave device)
       General Call Recognition: Off */
	TWAR = ((a_TwiConfig_Ptr->s_slaveAddress)<<1);

	TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void){
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void){
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 a_data){
	/* Put data On TWI data Register */
	TWDR = a_data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void){
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_readWithNACK(void){
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_getStatus(void){
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}
