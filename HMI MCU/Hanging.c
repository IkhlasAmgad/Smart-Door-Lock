/*
 * Hanging.c
 *
 *  
 *      Author: Ikhlas Amgad
 */
#include"Haging.h"
#include"Password.h"


#define NUMBER_OF_OVERFLOWS_PER_SECOND  7

uint8 tick = 0;
void Hanging(void)
{
	tick++;
				if(tick== NUMBER_OF_OVERFLOWS_PER_SECOND)
				{
					 CLEAR_BIT(PORTC,PC2); //Buzzer OFF
					 LCD_clearScreen();
					 Show_Two_Options();
					 Timer_Stop(Timer1);
					 Show_Two_Options();
				}


}







void Timer_init_Hanging(void)
{

	Timer_Config Timer1Config={F_CPU_1024,Timer1,OC0_disconnected,CTC};
				        Timer_init(&Timer1Config);
				        Timer_Set_init_value(Timer1,0);
				        Timer_Set_OutPut_Compare_value(Timer1,62500); //overflow every 8 sec.
				        Timer_Enable_Interrupt(Timer1,CTC);
                          Timer_Start(Timer1);
                          UART_sendByte('=');

                     LCD_clearScreen();




                         Timer1_setCallBack(Hanging);



        	while(tick!= NUMBER_OF_OVERFLOWS_PER_SECOND)
        	{
        		LCD_goToRowColumn(0,2);

        		LCD_displayString(" E R O R R !! ");
        	};









}
/************************************************************/

