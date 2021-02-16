/*--------------------------------------------------------------------------------------------------------------------------
 * file name  : usart.c
 * Author     : OUN
 * Created on : Nov 13, 2020
 * description: USART source file driver
 --------------------------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include "usart.h"

/*----------------------------------------------------DFINATIONS-----------------------------------------------------------*/


/*-----------------------------------------------FUNCTION DECLARATIONS-----------------------------------------------------*/

void UART_init(Usart_ConfigType *UsartConfig_Ptr){

	UCSRA = (1<<U2X);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<URSEL);
	switch (UsartConfig_Ptr->s_parity)
	{
	case NO_PARITY:

		break;
	case EVEN:

		SET_BIT(UCSRC,UPM1);
		break;
	case ODD:

		UCSRC |= (1<<UPM1) | (1<<UPM0);
		break;
	}

	if (UsartConfig_Ptr->s_stopBit == DOUBLE)
	{
		SET_BIT(UCSRC,USBS);
	}
	switch (UsartConfig_Ptr->s_bitDataNum)
	{
	case FIVE_BITS:

		break;
	case SIX_BITS:

		SET_BIT(UCSRC,UCSZ0);
		break;
	case SEVEN_BITS:

		SET_BIT(UCSRC,UCSZ1);
		break;
	case EIGHT_BITS:

		UCSRC |= (1<<UCSZ0) | (1<<UCSZ1);
		break;
	case NINE_BITS:

		SET_BIT(UCSRB,UCSZ2);
		UCSRC |= (1<<UCSZ0) | (1<<UCSZ1);
		break;
	}

	/*Baud Rate*/
	uint16 baudScale = (F_CPU/(8*(UsartConfig_Ptr->s_baudRate)))-1 ;
	UBRRL = (baudScale & 0x00FF);
	UBRRH = (baudScale >> 8);

}
void UART_sendByte(uint8 a_data){
	while (BIT_IS_CLEAR(UCSRA, UDRE));
	UDR = a_data;
	/*
	 * another method
	 * UDR = a_data;
	 * while (BIT_IS_CLEAR(UCSRA, TXC));
	 * SET_BIT(UCSRA, TXC);
	 */
}

uint8 UART_receiveByte(void){
	while (BIT_IS_CLEAR(UCSRA, RXC));
	return UDR;  /* After reading the data it will clear the flag automatically */
}

void UART_sendString(const uint8 *string_Ptr){
	while(*string_Ptr != '\0'){
		UART_sendByte(*string_Ptr);
		string_Ptr++;
	}
}
void UART_receiveString(uint8 *string_Ptr){ /* receive until $ */
	uint8 i=0;
	while ((string_Ptr[i]) != '#')
	{
		string_Ptr[i] = UART_receiveByte();
		i++;
	}
	string_Ptr[i]='\0';
}
