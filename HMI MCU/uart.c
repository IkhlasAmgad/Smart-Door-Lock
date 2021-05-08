 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Ikhlas Amgad
 *
 *******************************************************************************/

#include "uart.h"
#define BAUD_PRESCALE_DoubleSpeed (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)  //Double Speed Mode
#define BAUD_PRESCALE_NormalMode (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)  //Normal Speed Mode

static volatile void (*Tx_callBackPtr)(void) = NULL_PTR;
static volatile void (*Rx_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void UART_init(void)
{
	/*Zeros for the Module Registers*/
	UCSRA=0;
	UCSRC=0;
	UCSRB=0;

#if (SPEED_MODE==NORMAL_SPEED)
	CLEAR_BIT(UCSRA,U2X);
	UBRRH = BAUD_PRESCALE_NormalMode>>8;
    UBRRL = BAUD_PRESCALE_NormalMode;
	#elif (SPEED_MODE==DOUBLE_SPEED)
	SET_BIT(UCSRA,U2X);
	 UBRRH = BAUD_PRESCALE_DoubleSpeed>>8;
     UBRRL = BAUD_PRESCALE_DoubleSpeed;
	#endif

	  /*URSEL   = 1 The URSEL must be one when writing the UCSRC*/
	SET_BIT(UCSRC,URSEL);

	//********************************A/Synchronous***********************************/
		 #if (SYNCH_MODE==SYNCH)
		 SET_BIT(UCSRC_var,UMSEL)
		 #elif (SYNCH_MODE==ASYNCH)
	 	 CLEAR_BIT(UCSRC,UMSEL);
		 #endif
	 //*****************************Parity mode*******************************/

		#if (PARITY_MODE==NO_PARITY)
		CLEAR_BIT(UCSRC,UPM0);
		CLEAR_BIT(UCSRC,UPM1);
		#elif (PARITY_MODE==EVEN_PARITY)
		CLEAR_BIT(UCSRC_var,UPM0);
		SET_BIT(UCSRC_var,UPM1);
		#elif (PARITY_MODE==ODD_PARITY)
		SET_BIT(UCSRC_var,UPM0);
		SET_BIT(UCSRC_var,UPM1);
		#endif
	//************************Data bits*******************************/
		#if (N_DATA_BITS==_5_DATA_BITS)
		CLEAR_BIT(UCSRC_var,UCSZ0);
		CLEAR_BIT(UCSRC_var,UCSZ1);
		CLEAR_BIT(UCSRC_var,UCSZ2);
		#elif (N_DATA_BITS==_6_DATA_BITS)
		SET_BIT(UCSRC_var,UCSZ0);
		CLEAR_BIT(UCSRC_var,UCSZ1);
		CLEAR_BIT(UCSRC_var,UCSZ2);
	    #elif (N_DATA_BITS==_7_DATA_BITS)
	    CLEAR_BIT(UCSRC_var,UCSZ0);
	    SET_BIT(UCSRC_var,UCSZ1);
	    CLEAR_BIT(UCSRB,UCSZ2);
		#elif (N_DATA_BITS==_8_DATA_BITS)
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		#elif (N_DATA_BITS==_9_DATA_BITS)
		SET_BIT(UCSRC_var,UCSZ0);
		SET_BIT(UCSRC_var,UCSZ1);
		SET_BIT(UCSRB,UCSZ2);
		#endif
	//************************Stop bits*******************************/
		#if (N_STOP_BITS==ONE_STOP_BIT)
		CLEAR_BIT(UCSRC,USBS);
		#elif (N_STOP_BITS==TWO_STOP_BIT)
		SET_BIT(UCSRC_var,USBS);
		#endif
		//************************Enable  *******************************/
		//enable UART  receiver.
		SET_BIT(UCSRB,RXEN);
		//enable UART  transmitter .
		SET_BIT(UCSRB,TXEN);
}
	
void UART_sendByte(const uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */	 
	UDR = data;
	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/	
}

uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	   will be cleared after read this data */	 
    return UDR;		
}

void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}  //note ana kda mab3tsh el NULL
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	*******************************************************************/
}

void UART_receiveString(uint8 *Str)

{
	uint8 i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';    //put NULL manually
}
/**************************************************************/
void RX_InterruptEnable(void)
{
	Enable_Global_Interrupt;
	SET_BIT(UCSRB,RXCIE);
}
void RX_InterruptDisable(void)
{

	CLEAR_BIT(UCSRB,RXCIE);
}

/*************************************************************/
void TX_InterruptEnable(void)
{   Enable_Global_Interrupt;
	SET_BIT(UCSRB,TXCIE);
}
void Tx_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,TXCIE);
}
/*****************************ISR*****************************************/

ISR(USART_TXC_vect)
{
	if(Tx_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*Tx_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/******************************************/
ISR(USART_RXC_vect)
{
	if(Rx_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*Rx_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/**********************************SET CALL BACK FUNCTIONS************************************************/
void Tx_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	Tx_callBackPtr = a_ptr;
}
/*******************************/
void Rx_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	Rx_callBackPtr = a_ptr;
}
