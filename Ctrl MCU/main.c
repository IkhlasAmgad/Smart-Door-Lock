/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ikhlas Amgad
 */

#include "i2c.h"
#include "uart.h"
#include "external_eeprom.h"
#include "Motor.h"


volatile static uint8 i=0;
static uint8 data_red[4];
static uint8  data_rec[4];

 void  Rec_Password(void)
 {
	 uint8 data=UART_recieveByte();
	 if( data=='-')
	 {
		 Motor();
	 }
	 else
		 if( data=='=')
		 {
			 Buzzer();
		 }
	 else

	 {
    data_rec[i]=data;
  /********for testing eeprom********/
	if(i==3)
	{

		 uint8 j ,k=0;
		 for(j=0;j<4;j++)
      {
	EEPROM_writeByte((0x0311+j), data_rec[j]);
     _delay_ms(10);
      }
		 _delay_ms(10);
		 for(k=0;k<4;k++)
		 {
			 EEPROM_readByte((0x0311+k),&data_red[k]);
			 _delay_ms(10);

		 }
		 uint8 x;
		 /*Send Password Back */
	for(x=0;x<4;x++)
	{
		UART_sendByte(data_red[x]);

	}
/*************Check EEPROM READ********/
	for(x=0;x<4;x++)
		{
       PORTB=data_red[x];
       _delay_ms(1000);
       /*********************/
		  }
	i=0;
    return;
     }
  /*************************************/

     i++;
	 }
 }

int main(void)
{


	EEPROM_init();
	UART_init();
	RX_InterruptEnable();
	Timer_intit_for_motor();

	/***for testing eeprom********/
/*	DDRB=0xFF;
	PORTB=0;*/






   Rx_setCallBack(Rec_Password);

	while(1)
	{


	}

	return 0;
}
