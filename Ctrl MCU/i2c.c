 /******************************************************************************
 *
 * Module: I2C(TWI)
 *
 * File Name: i2c.c
 *
 * Author: Ikhlas Amgad
 *
 *******************************************************************************/
 
#include "i2c.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TWI_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}



void TWI_init(void)
{
    /* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */

	//TWSR = 0x00;
	TWBR = BITRATE(TWSR=No_Prescaler);
	
    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = 0b00000010; // my address = 0x01 :) 
	
    TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void)
{
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

uint8 TWI_readWithNACK(void)
{
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

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}


void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
void TWI_init_withInterrupt(void)
{
	/* Enable Global Interrupt I-Bit */
		SREG |= (1<<7);


	   TWBR = BITRATE(TWSR=No_Prescaler);

	    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
	       General Call Recognition: Off */
	    TWAR = 0b00000010; // my address = 0x01 :)
	    /* Enable TWI Interrupt  */
	    TWCR = (1<<TWEN)|(1<<TWIE); /* enable TWI */

	}

