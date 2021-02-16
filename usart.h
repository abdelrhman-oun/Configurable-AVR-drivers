/*--------------------------------------------------------------------------------------------------------------------------
 * file name  : usart.h
 * Author     : OUN
 * Created on : Nov 13, 2020
 * description: USART header file driver
 --------------------------------------------------------------------------------------------------------------------------*/

#ifndef USART_H_
#define USART_H_

/*-----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/*-------------------------------------------------TYPES DECLARATION-------------------------------------------------------*/

typedef enum
{
	NO_PARITY,EVEN,ODD
}Usart_ParityType;

typedef enum
{
	SINGLE,DOUBLE
}Usart_StopBitNum;

typedef enum
{
	FIVE_BITS,SIX_BITS,SEVEN_BITS,EIGHT_BITS,NINE_BITS
}Usart_DataNum;

typedef struct
{
	Usart_ParityType s_parity;
	uint16 s_baudRate;
	Usart_StopBitNum s_stopBit;
	Usart_DataNum s_bitDataNum;
}Usart_ConfigType;


/*-----------------------------------------------FUNCTION DECLARATIONS-----------------------------------------------------*/

void UART_init(Usart_ConfigType *UsartConfig_Ptr);
void UART_sendByte(uint8 a_data);
uint8 UART_receiveByte(void);
void UART_sendString(const uint8 *string_Ptr);
void UART_receiveString(uint8 *string_Ptr); /* receive until $ */


#endif /* USART_H_ */
