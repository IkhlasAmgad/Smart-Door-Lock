/*
 * Motor.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ikhlas Amgad
 */
#include"Motor.h"


#define NUMBER_OF_OVERFLOWS_PER_SECOND_tm1  2

unsigned char g_tick = 0;





void Motor_Ctrl(void)
{



		g_tick++;
			if(g_tick == NUMBER_OF_OVERFLOWS_PER_SECOND_tm1)
			{

				PORTD &= (~(1<<PD4));
				PORTD|= (1<<PD3);
				 //clear the tick counter again to count a new 0.5 second
			}


			else
				if(g_tick == 4)
							{

					PORTD &= 0xE7;
					Timer_Stop(Timer1);
							}

	}




void Timer_intit_for_motor(void)
{
	    Timer_Config Timer1Config={F_CPU_1024,Timer1,OC0_disconnected,CTC};
		        Timer_init(&Timer1Config);
		        Timer_Set_init_value(Timer1,0);
		        Timer_Set_OutPut_Compare_value(Timer1,40000);
		        Timer_Enable_Interrupt(Timer1,CTC);
		        Timer_Enable_Interrupt(Timer1,CTC);

		         Timer1_setCallBack(Motor_Ctrl);


}
void Motor()
{

	Timer_Start(Timer1);

	/* configure pin PD3 and PD4 as output pins */
		DDRD |= 0x18;

		/* Motor is stop at the beginning */
		PORTD &= 0xE7;
		// Rotate the motor --> clock wise
					PORTD &= (~(1<<PD3));
					PORTD|= (1<<PD4);


}

