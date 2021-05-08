/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ikhlas Amgad
 */

#include"password.h"


void Get_Password_from_EEPROM(void)
{
	uint8 static c=0;
	/*Global Array get_password_from_EEPROM[]*/
   get_password_from_EEPROM[c]=UART_recieveByte();

	if(c==3)
	{
		c=0;
	return ;
	}
	c++;
}




int main()
{

	LCD_init();
	_delay_ms(20);
	UART_init();

	RX_InterruptEnable();
	Rx_setCallBack(Get_Password_from_EEPROM);


	LCD_clearScreen();
    Enter_Password();
    Renter_Password();
    Show_Two_Options(); /*Show two 	Options '+' for Changes Password ,'-' Open Door*/





while(1)
{

}

return 0;
}



