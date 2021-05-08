/*
 * Buzzer.c
 *
 
 *      Author: Ikhlas Amgad
 */

#include"Buzzer.h"
#define NUMBER_OF_OVERFLOWS_PER_SECOND  7

uint8 tick = 0;
void Hang(void)
{
	tick++;
				if(tick== NUMBER_OF_OVERFLOWS_PER_SECOND)   // One min. left
				{

					 Timer_Stop(Timer0);
					 Timer_Stop(Timer1);

				}


}



void Buzzer(void)
{
Timer_Config Timer0Config={F_CPU_1024 ,Timer0,Toggle_OC0,CTC};
                 Timer_init(&Timer0Config);  //Timer init
                 Timer_Set_init_value(Timer0,0);
                 Timer_Set_OutPut_Compare_value(Timer0,128);
                //Timer_Enable_Interrupt(Timer0,CTC);

                 Timer_Start(Timer0);
                 Timer_init_Alarm_time();
}


void Timer_init_Alarm_time(void)
{
	Timer_Config Timer1Config={F_CPU_1024,Timer1,OC0_disconnected,CTC};
					        Timer_init(&Timer1Config);
					        Timer_Set_init_value(Timer1,0);
					        Timer_Set_OutPut_Compare_value(Timer1,62500); //overflow every 8 sec.
					        Timer_Enable_Interrupt(Timer1,CTC);
	                          Timer_Start(Timer1);





	                         Timer1_setCallBack(Hang);
}
